#include "slavelist.h"

uint8_t get_address ( struct slavelistitem item )
{
        return item.address;
}

uint8_t init ( struct slavelistitem *item, enum slave_priority priority, uint8_t address )
{
        item->previous = 0;
        item->next=0;
        item->priority = priority;
        item->address = address;
}

uint8_t get_priority ( struct slavelistitem *item )
{
        return item->priority;
}

uint8_t insert ( struct slavelistitem *newitem,struct slavelistitem *previous, struct slavelistitem *next )
{
        newitem->previous = previous;
        previous->next = newitem;
        newitem->next = 0;
        if ( next > 0 ) {
                next->previous = newitem;
                newitem->next = next;
        }
}

void swap ( struct slavelistitem *si1, struct slavelistitem *si2 )
{
        struct slavelistitem *temp;

        temp = si1->next;
        si1->next = si2->next;
        si2->next = temp;

        temp = si1->previous;
        si1->previous = si2->previous;
        si2->previous = temp;
}

uint8_t reorder ( struct slavelistitem *item )
{
        struct slavelistitem *traverse = item;
        do {
                if ( traverse->next->priority < traverse->priority ) {
                        swap ( traverse, traverse->next );
                }
                else if ( traverse->priority == traverse->next->priority ) {
                        if ( traverse->intcount < traverse->next->intcount ) {
                                swap ( traverse, traverse->next );
                        }
                        traverse = traverse->next;
                }
        } while ( traverse->next > 0 );
}
