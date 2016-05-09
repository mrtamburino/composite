/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   listitem.hpp
 * Author: ale
 *
 * Created on November 27, 2015, 8:02 PM
 */

#include <stdlib.h>
#include "../logs/log.h"
#include "../types/types.h"

#ifndef EVENT_HPP
#define EVENT_HPP

namespace composite
{

    /** /brief Base class for subscriber
     * Implement an self refere class used to build a linkd list of subscriber
     */
    template <class P>
    class Subscription
    {
    public:
      Subscription():_ptrNext(NULL){TLOG("Subscription<T>::Subscription()\n");}
      virtual ~Subscription(){TLOG("Subscription<T>::~Subscription()\n");_ptrNext=NULL;}
      virtual UINT8 delivery(const P* ptrData_IN)=0;
      Subscription* _ptrNext;
    };
    
    /** /brief Base class for subscriber
     * Implement an self refere class used to build a linkd list of subscriber
     */
    template <>
    class Subscription<void>
    {
    public:
      Subscription():_ptrNext(NULL){TLOG("Subscription<T>::Subscription()\n");}
      virtual ~Subscription(){TLOG("Subscription<T>::~Subscription()\n");_ptrNext=NULL;}
      virtual UINT8 delivery(void)=0;
      Subscription* _ptrNext;
    };
    
    /** /brief Class for subscriber
     * Contains a pointer to class and a function member pointer.
     */
    template <class T, class P>
    class Subscriber: public Subscription<P>
    {

    public:
        
        
        typedef UINT8 (T::*FNC)(const P*);

        Subscriber(T* ptrOwner_IN, UINT8 (T::*ptrfHandler_IN)(const P*)):Subscription<P>()
        {
          TLOG("Subscriber<T>::Subscriber(T* ptrOwner_IN, Callback<T,P>::FNC ptrfHandler_IN)\n");
          _owner=ptrOwner_IN;
          _handler=ptrfHandler_IN;
        }

        ~Subscriber()
        {
          TLOG("Subscriber<T>::~Subscriber()\n");
        }

        UINT8 delivery(const P* ptrData_IN)
        {
            return (_owner->*_handler)(ptrData_IN);
        }

      
    private:
        T* _owner;
        FNC _handler;

    };
    
    /** /brief Class for subscriber
     * Contains a pointer to class and a function member pointer.
     */
    template <class T>
    class Subscriber<T,void>: public Subscription<void>
    {

    public:
        
        
        typedef UINT8 (T::*FNC)(void);

        Subscriber(T* ptrOwner_IN, UINT8 (T::*ptrfHandler_IN)(void)):Subscription<void>()
        {
          TLOG("Subscriber<T>::Subscriber(T* ptrOwner_IN, UINT8 (T::*ptrfHandler_IN)(void))\n");
          _owner=ptrOwner_IN;
          _handler=ptrfHandler_IN;
        }

        ~Subscriber()
        {
          TLOG("Subscriber<T>::~Subscriber()\n");
        }

        UINT8 delivery(void)
        {
            return (_owner->*_handler)();
        }

      
    private:
        T* _owner;
        FNC _handler;

    };
    
    
    
    template <class P>
    class Event
    {

    public:


      Event():_ptrFirstItem(NULL), _ptrLastItem(NULL), _uiLength(0)
      {
    	TLOG("Event<T>::Event()\n");
      }
      ~Event()
      {

        TLOG("Event<T>::~Event()\n");

        Subscription<P>* curentItem = _ptrFirstItem;
        Subscription<P>* tmp = NULL;
        while(curentItem)
        {
          tmp = curentItem;
          curentItem = curentItem->_ptrNext;
          delete tmp;
        }
      }
      
      template <class T>
      void subscribe(T* ptrOwner_IN, UINT8 (T::*ptrfHandler_IN)(const P*) )
      {
          Subscription<P>* newSubscription = new Subscriber<T,P>(ptrOwner_IN, ptrfHandler_IN);
          
          if(_ptrFirstItem)
          {
              _ptrLastItem->_ptrNext = newSubscription;
          }
          else
          {
              _ptrFirstItem = newSubscription;
          }
          
          _ptrLastItem = newSubscription;
      }
      
      void dispatch(const P* ptrData_IN)
      {
          
          Subscription<P>* curentItem = _ptrFirstItem;
          
          while(curentItem && curentItem->delivery(ptrData_IN))
          {
              curentItem = curentItem->_ptrNext;
          }
      }

      //! \brief First item of the list
      Subscription<P>* _ptrFirstItem;
      //! \brief Last item of the list
      Subscription<P>* _ptrLastItem;

      UINT32 _uiLength;
    };
    
    template <>
    class Event<void>
    {

    public:


      Event():_ptrFirstItem(NULL), _ptrLastItem(NULL), _uiLength(0)
      {
    	TLOG("Event<T>::Event()\n");
      }
      ~Event()
      {

        TLOG("Event<T>::~Event()\n");

        Subscription<void>* curentItem = _ptrFirstItem;
        Subscription<void>* tmp = NULL;
        while(curentItem)
        {
          tmp = curentItem;
          curentItem = curentItem->_ptrNext;
          delete tmp;
        }
      }
      
      template <class T>
      void subscribe(T* ptrOwner_IN, UINT8 (T::*ptrfHandler_IN)(void) )
      {
          Subscription<void>* newSubscription = new Subscriber<T,void>(ptrOwner_IN, ptrfHandler_IN);
          
          if(_ptrFirstItem)
          {
              _ptrLastItem->_ptrNext = newSubscription;
          }
          else
          {
              _ptrFirstItem = newSubscription;
          }
          
          _ptrLastItem = newSubscription;
      }
      
      void dispatch(void)
      {
          
          Subscription<void>* curentItem = _ptrFirstItem;
          
          while(curentItem && curentItem->delivery())
          {
              curentItem = curentItem->_ptrNext;
          }
      }

      //! \brief First item of the list
      Subscription<void>* _ptrFirstItem;
      //! \brief Last item of the list
      Subscription<void>* _ptrLastItem;

      UINT32 _uiLength;
    };

  
}

#endif /* EVENT_HPP */

