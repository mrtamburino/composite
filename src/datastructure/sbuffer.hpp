/*
 * sbuffer.hpp
 *
 *  Created on: Apr 26, 2015
 *      Author: ale
 */

#ifndef SRC_DATASTRUCTURE_SBUFFER_HPP_
#define SRC_DATASTRUCTURE_SBUFFER_HPP_

#include "lslink.hpp"
#include "../exceptions/excps.hpp"

namespace composite
{

  namespace dts
  {

    template <class T>
    class Segment
    {
    public:
      Buffer<T,large_buffer_t> dataBuffer;
      Segment* ptrNext;
    };

    template <class T>
    class SBuffer: BaseBuffer<T>
    {
    public:
      SBuffer(unsigned int uiSize_IN):_uiSize(uiSize_IN),_ptrFirst(NULL),_ptrLast(NULL){}
      virtual ~SBuffer(){}

      T* append(void);
      T* append(const T& ptrItem);

    protected:
      unsigned int _uiSize;
      Segment<T>* _ptrFirst;
      Segment<T>* _ptrLast;

      void allocateSegment();

    };

    template <class T>
    void SBuffer<T>::allocateSegment()
    {
      void* p = NULL;

      if( !( p=malloc( sizeof(T)*_uiSize + sizeof(Segment<T>)) ) )
      {

      }

      if(_ptrLast)
      {
	  _ptrLast->ptrNext = (Segment<T>*)p;
	  _ptrLast = _ptrLast->ptrNext;
      }
      else
      {
	  _ptrLast = (Segment<T>*)p;
	  _ptrFirst = _ptrLast;
	  _ptrLast->ptrNext = NULL;
      }

      _ptrLast->dataBuffer.useExistingBuffer( (T*)(p + sizeof(Segment<T>)) );


    }


  }

}


#endif /* SRC_DATASTRUCTURE_SBUFFER_HPP_ */
