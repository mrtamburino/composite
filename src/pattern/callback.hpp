/*
 * callback.hpp
 *
 *  Created on: Jan 18, 2014
 *      Author: ale
 */

#ifndef CALLBACK_HPP_
#define CALLBACK_HPP_

#include "../types/types.h"
#include <stdlib.h>


namespace composite
{

  template <class P>
  class CallbackBase
  {
  public:
    CallbackBase(){}
    virtual ~CallbackBase(){}
    virtual UINT8 call(const P* data) = 0;
  };

  template <>
  class CallbackBase<void>
    {
    public:
      CallbackBase(){}
      virtual ~CallbackBase(){}
      //virtual UINT8 call(void*) = 0;
      virtual UINT8 call(void) = 0;
    };



  template <class T, class P>
  class Callback: public CallbackBase<P>
  {
    public:
    typedef UINT8 (T::*FNC)(const P*);

    Callback(void):_owner(NULL),_funcToCall(NULL) {}
    Callback(T* owner, FNC funcToCal):_owner(owner),_funcToCall(funcToCal) {}

    void bind(T* owner, FNC funcToCal)
    {
      _owner = owner;
      _funcToCall = funcToCal;
    }

    UINT8 call(const P* data)
    {
      return (_owner->*_funcToCall)(data);
    }

    private:
      T* _owner;
      FNC _funcToCall;

  };

  template <class T>
  class Callback<T,void>: public CallbackBase<void>
  {
    public:
    typedef UINT8 (T::*FNC)();

    Callback(void):_owner(NULL),_funcToCall(NULL) {}
    Callback(T* owner, FNC funcToCal):_owner(owner),_funcToCall(funcToCal) {}

    void bind(T* owner, FNC funcToCal)
    {
      _owner = owner;
      _funcToCall = funcToCal;
    }

    UINT8 call(void)
    {
      return (_owner->*_funcToCall)();
    }

    private:
      T* _owner;
      FNC _funcToCall;

  };


}

#endif /* CALLBACK_HPP_ */
