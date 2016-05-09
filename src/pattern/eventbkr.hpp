/*
 * eventbkr.hpp
 *
 *  Created on: Apr 27, 2015
 *      Author: ale
 */

#ifndef SRC_PATTERN_EVENTBKR_HPP_
#define SRC_PATTERN_EVENTBKR_HPP_

#include "../types/types.h"
#include "../pattern/callback.hpp"
#include "../datastructure/lslink.hpp"
#include "../exceptions/excps.hpp"
#include "../datastructure/dbuffer.hpp"
#include "../datastructure/dal.hpp"

#define BROKER_INITIAL_SIZE 10

namespace composite
{

  template <class K, class P>
  class EventListeners
  {
  public:
    EventListeners(K& ptrEventID);
    EventListeners(K& ptrEventID, CallbackBase<P>* ptrHandler_IN);
    ~EventListeners(){}

    void subscribe(CallbackBase<P>* ptrHandler_IN);
    void notify(P* ptrData_IN);

    inline bool operator==(const K& rhs){ return this->eventID==rhs; }
    inline bool operator> (const K& rhs){return this->eventID>rhs ;}
    inline bool operator< (const K& rhs){return this->eventID<rhs ;}

    K eventID;
    dts::List<CallbackBase<P>* > consumers;

  };

  template <class K, class P>
  class EventBroker
  {
  public:
    EventBroker();

    void subscribe(K& ptrEventID, CallbackBase<P>* ptrHandler_IN);
    void notify(K& ptrEventID, P* ptrData_IN);

    dts::DynamicBuffer<EventListeners<K,P>, dts::large_buffer_t> listeners;
    dts::QSorter<EventListeners<K,P>, dts::large_buffer_t, K> listenerSorter;

  };

  template <class K, class P>
  EventListeners<K,P>::EventListeners(K& ptrEventID)
  {
    if(!ptrEventID )
      THROW_EXCEPTION(excps::IllegalPrameterException);

    eventID = ptrEventID;

  }

  template <class K, class P>
  EventListeners<K,P>::EventListeners(K& ptrEventID, CallbackBase<P>* ptrHandler_IN)
  {
    if(!ptrEventID || !ptrHandler_IN)
      THROW_EXCEPTION(excps::IllegalPrameterException);

    eventID = ptrEventID;
    consumers.append(ptrHandler_IN);

  }

  template <class K, class P>
  void EventListeners<K,P>::subscribe(CallbackBase<P>* ptrHandler_IN)
  {
    if(!ptrHandler_IN)
       THROW_EXCEPTION(excps::IllegalPrameterException);

    consumers.append(ptrHandler_IN);
  }

  template <class K, class P>
  void EventListeners<K,P>::notify(P* ptrData_IN)
  {
    dts::ListItem<CallbackBase<P>* >* current = consumers._ptrFirstItem;

    while( current && current->_ptrData_->call(ptrData_IN) )
      current = current->_ptrNext;
  }

  template <class K, class P>
  EventBroker<K,P>::EventBroker()
  {
    listeners.allocate(BROKER_INITIAL_SIZE);
    listenerSorter.setBuffer(&listeners);
  }

  template <class K, class P>
  void EventBroker<K,P>::subscribe(K& ptrEventID, CallbackBase<P>* ptrHandler_IN)
  {

    if(!ptrEventID || !ptrHandler_IN)
       THROW_EXCEPTION(excps::IllegalPrameterException);

    // find event ID
    EventListeners<K,P>* event = listenerSorter.search(ptrEventID);

    if(event)
    {
       event->subscribe(ptrHandler_IN);
    }
    else
    {
       new (listenerSorter.insert(ptrEventID, TRUE)) EventListeners<K,P>(ptrEventID, ptrHandler_IN);
    }

  }

  template <class K, class P>
  void EventBroker<K,P>::notify(K& ptrEventID, P* ptrData_IN)
  {
      // ptrEventID is a reference
    //if(!ptrEventID)
    //   THROW_EXCEPTION(excps::IllegalPrameterException);

    // find event ID
    EventListeners<K,P>* event = listenerSorter.search(ptrEventID);
    if(event)
    {
	event->notify(ptrData_IN);
    }

  }

}


#endif /* SRC_PATTERN_EVENTBKR_HPP_ */
