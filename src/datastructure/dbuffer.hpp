/*
 * dbuffer.hpp
 *
 *  Created on: Jan 17, 2014
 *      Author: ale
 */

#ifndef DBUFFER_HPP_
#define DBUFFER_HPP_


#include "buffer.hpp"
#include "../logs/log.h"

namespace composite
{

  namespace dts
  {

    DEFINE_APP_EXCEPTION(BufferMaxSizeReachedException, "Try to create a too large buffer!");

    template <class T>
    class DynamicBuffer: public Buffer<T>
    {
    public:

      buffer_size_t _uiMaxSize;

      DynamicBuffer():Buffer<T>()
      {
        TLOG("DynamicBuffer::DynamicBuffer():Buffer<T>()\n");
        setMaxSize();
      }
      
      DynamicBuffer(buffer_size_t uiSize_IN): Buffer<T>(uiSize_IN)
      {
        TLOG("DynamicBuffer::DynamicBuffer(S uiSize_IN): Buffer<T>(uiSize_IN): %d\n", uiSize_IN);
        setMaxSize();
        Buffer<T>::allocate(uiSize_IN);
      }

      ~DynamicBuffer()
      {
        TLOG("DynamicBuffer::~DynamicBuffer()\n");
      }

      T* append(const T& ptrItem);
      T* append(void);

    private:
      void setMaxSize(void)
      {
        // calculate max size
        buffer_size_t* tmp = NULL;
        if(!(tmp=(buffer_size_t*)malloc(sizeof(buffer_size_t))))
        {
          THROW_EXCEPTION(composite::excps::OutOfMemoryException);
        }
        memset(tmp, 0xff, sizeof(buffer_size_t));
        _uiMaxSize = *tmp;
        free(tmp);

        DLOG("Max size for DynamicBuffer: %d items\n", _uiMaxSize);
      }

    };

    template <class T>
    T* DynamicBuffer<T>::append(void)
    {
      if(!Buffer<T>::_uiBufferSize)
	  {
		  THROW_EXCEPTION(EmptyBufferException);
	  }

	  if( Buffer<T>::_uiBufferSize == Buffer<T>::_uiLength)
	  {

		  if(Buffer<T>::_uiBufferSize==_uiMaxSize)
		  {
			DLOG("buffer size: %d, max size: %d\n", Buffer<T>::_uiBufferSize,_uiMaxSize);
			THROW_EXCEPTION(BufferMaxSizeReachedException);
		  }

		  buffer_size_t uiIncrement = Buffer<T>::_uiBufferSize > 1 ? Buffer<T>::_uiBufferSize >> 1 : 2;
		  buffer_size_t uiNewSize = ((_uiMaxSize - Buffer<T>::_uiBufferSize) < uiIncrement) ? _uiMaxSize : Buffer<T>::_uiBufferSize+uiIncrement;

		  DLOG( "Resize buffer: %lu -> %lu (item size: %u bytes, DynamicBuffer size: %lu bytes)\n", Buffer<T>::_uiBufferSize, uiNewSize, sizeof(T), sizeof(T)*uiNewSize);

		  T* ptrNewBuffer = NULL;
		  if(!(ptrNewBuffer = (T*)realloc(Buffer<T>::_ptrBuffer, (uiNewSize)*sizeof(T))))
			{
			  THROW_EXCEPTION(composite::excps::OutOfMemoryException);
			}

		  DLOG( "Resized\n");

		  Buffer<T>::_uiBufferSize=uiNewSize;
		  Buffer<T>::_ptrBuffer=ptrNewBuffer;

		  //memset( (Buffer<T,S>::_ptrBuffer+Buffer<T,S>::_uiFilled), 0, sizeof(T)*uiIncrement);
	  }

	  return Buffer<T>::append();

    }

    template <class T>
    T* DynamicBuffer<T>::append(const T& ptrItem)
    {

      return new (append()) T(ptrItem);


    }

  }

}


#endif /* DARRAY_HPP_ */
