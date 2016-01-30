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

#pragma once

#include <memory>
#include <stdexcept>
#include <map>
#include <deque>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "i2cpacket.h"
#include "i2cendpointbroker.h"


namespace i3c {
namespace sys {
namespace i2c {

class I2CDispatchResponseHandler {
public:
  virtual ~I2CDispatchResponseHandler();

  //! Handle an I2C response
  virtual void processI2CResponse(const I2CPacket packet) throw () = 0;
};

//! I2C dispatcher with priority handling.
class I2CDispatcher
{
public:
  //! The packet priority
  enum class Priority {
    //! Send immediate, without queue
    IMMEDIATE = 0,
    //! Highest queued priority
    REALTIME,
    //! Normal priority
    NORMAL,
    //! Send after all normal packets
    DEFERRED
  };

  I2CDispatcher(std::weak_ptr<I2CEndpointBroker> broker) throw(std::invalid_argument);

  ~I2CDispatcher();

  I2CDispatcher(const I2CDispatcher&) = delete;
  I2CDispatcher& operator= (const I2CDispatcher&) = delete;

  //! Dispatch an I2C request and register a response handler
  /**
   * @return true if the request could be placed, otherwise false (e.g. if the dispatcher has been closed)
   */
  bool dispatch(const I2CPacket packet,
	        const Priority prio,
	        std::weak_ptr<I2CDispatchResponseHandler> hnd) throw (std::invalid_argument);

  //! Close the dispatcher, maybe process remaining packets
  void close(const bool process = true) throw();

  const bool isClosed() const throw ();

  //! Start accepting packets, sending all I2C requests that come via the queue
  void accept() throw();

private:
  //! process a request from the prio's queue
  /**
   * @return true if an element was processed, false if the queue was empty before processing
   */
  bool processQueueElement(const Priority prio) throw (std::exception);

  bool processHighestPriority();

  I2CPacket&& processI2CPacket(const I2CPacket packet) throw (std::bad_weak_ptr,
							      std::invalid_argument,
							      I2CEndpointException);

private:
  class DispatchRequest {
  public:
    DispatchRequest(const I2CPacket packet,
		    std::weak_ptr<I2CDispatchResponseHandler> hnd)
    : m_packet(packet), m_hnd(hnd)
    {}

    I2CPacket m_packet;
    std::weak_ptr<I2CDispatchResponseHandler> m_hnd;
  };

  std::weak_ptr<I2CEndpointBroker> m_broker;
  std::map<Priority, std::deque<DispatchRequest> > m_queue;
  std::map<Priority, std::unique_ptr<std::mutex> > m_queue_mutex;
  //! set to close the queues when shutting down the dispatcher
  std::atomic<bool> m_closed;
  //! set by dispatching a request to an event
  std::condition_variable m_dispatched;
};

} // namespace i2c
} // namespace sys
} // namespace i3c
