/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "i2cdispatcher.h"

#include <cstdint>
#include <chrono>

namespace i3c {
namespace sys {
namespace i2c {

I2CDispatcher::I2CDispatcher(std::weak_ptr<I2CEndpointBroker> broker) throw(std::invalid_argument)
: m_broker(broker),
  m_queue({
    // initialize the queues
    /* TODO We do not need a queue for immediate requests */
    {Priority::IMMEDIATE, std::deque<DispatchRequest>()},
    {Priority::REALTIME, std::deque<DispatchRequest>()},
    {Priority::NORMAL, std::deque<DispatchRequest>()},
    {Priority::DEFERRED, std::deque<DispatchRequest>()},
  }),
  m_closed(false)
{
  if (broker.expired())
    throw std::invalid_argument("Broker is expired!");

  // fill the mutex map
  m_queue_mutex.emplace(Priority::IMMEDIATE, std::make_unique<std::mutex>());
  m_queue_mutex.emplace(Priority::REALTIME, std::make_unique<std::mutex>());
  m_queue_mutex.emplace(Priority::NORMAL, std::make_unique<std::mutex>());
  m_queue_mutex.emplace(Priority::DEFERRED, std::make_unique<std::mutex>());
}

I2CDispatcher::~I2CDispatcher() {}

bool I2CDispatcher::dispatch(const I2CPacket packet,
			     const I2CDispatcher::Priority prio,
			     std::weak_ptr< I2CDispatchResponseHandler > hnd) throw (std::invalid_argument)
{
  // check for closed dispatcher
  if (m_closed.load())
    return false;

  // Check the handler
  if (hnd.expired())
    throw std::invalid_argument("Handler is expired!");

  // get a lock for the priority's queue
  std::lock_guard<std::mutex> lock(*(m_queue_mutex[prio]));

  // Push the request into the respective queue
  m_queue[prio].push_back(DispatchRequest(packet, hnd));

  // notify waiting comsumer threads
  m_dispatched.notify_all();

  return true;
}

void I2CDispatcher::close(const bool process) throw()
{
  // only if not already closing
  if (!m_closed.load()) {
    m_closed.store(true);

    // break a dispatch lock, should there be a dispatcher thread
    m_dispatched.notify_all();

    if (process) {
      // process remaining requests
      while (processHighestPriority());
    }
  }
}

const bool I2CDispatcher::isClosed() const throw ()
{
  return m_closed.load();
}

void I2CDispatcher::accept() throw()
{
  // this is the mutex for dispatch waiting
  std::mutex dispatch_mutex;
  std::unique_lock<std::mutex> dispatch_lock(dispatch_mutex);

  // run until the dispatcher is closed
  while (!m_closed.load()) {
    // process all requests
    while (processHighestPriority());

    /*
     * Wait for new requests.
     * We use the timeout to ensure that there is no dead-lock.
     */
    m_dispatched.wait_for(dispatch_lock,
			  std::chrono::milliseconds(1000));
  }
}

bool I2CDispatcher::processQueueElement(const I2CDispatcher::Priority prio) throw (std::exception)
{
  // get a lock for the priority's queue
  std::lock_guard<std::mutex> lock(*(m_queue_mutex[prio]));

  if (m_queue[prio].empty())
    // no event in the queue, nothing to process
    return false;

  // get the first request
  const DispatchRequest dr(
    m_queue[prio].front()
  );

  //actually process the request
  const I2CPacket response(
    processI2CPacket(dr.m_packet)
  );

  // get and call the handler
  if (auto hnd = dr.m_hnd.lock())
    hnd->processI2CResponse(response);

  // remove from queue
  m_queue[prio].pop_front();

  return true;
}

bool I2CDispatcher::processHighestPriority()
{
  bool done;

  /* The following scheme relies on shortcut evaluation of boolean expressions. */

  // process IMMEDIATE
  done = processQueueElement(Priority::IMMEDIATE);

  // process REALTIME
  done |= processQueueElement(Priority::REALTIME);

  // process NORMAL
  done |= processQueueElement(Priority::NORMAL);

    // process DEFERRED
  done |= processQueueElement(Priority::DEFERRED);

  return done;
}


I2CPacket&& I2CDispatcher::processI2CPacket(const I2CPacket packet) throw (std::bad_weak_ptr,
									   std::invalid_argument,
									   I2CEndpointException)
{
  // get the endpoint broker
  // this may throw std::bad_weak_ptr
  std::shared_ptr<I2CEndpointBroker> broker(m_broker);

  // try to get the i2c endpoint
  std::shared_ptr<I2CEndpoint> endpoint(broker->endpoint(packet.peer()));
  if (endpoint == nullptr)
    throw std::invalid_argument("Could not retrieve endpoint!");

  //make the actual call
  const uint16_t response(endpoint->write(packet.data()));

  // construct and move-return the response packet
  return std::move(I2CPacket(packet.seqNo(), packet.peer(), response));
}

} // namespace i2c
} // namespace sys
} // namespace i3c
