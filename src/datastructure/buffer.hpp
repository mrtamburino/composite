/*
 * buffer.hpp
 *
 *  Created on: Jan 17, 2014
 *      Author: ale
 */

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include "../logs/log.h"
#include "../exceptions/excps.hpp"
#include "../types/types.h"
#include <stdlib.h>
#include <new>

#define BUFFER_LOOP_ITEMS(BUFFER,INDEX) for(composite::dts::buffer_size_t INDEX=0; indx=BUFFER._uiLength;INDEX++)

namespace composite
{

  namespace dts
  {

    /*! \brief Try to use an empty buffer
     *
     * Exception raised to access an empty buffer.
     * You have to allocate the buffer with "allocate" method before use it
     */
    DEFINE_APP_EXCEPTION(EmptyBufferException, "Try to use an empty buffer!");

    
    typedef UINT8  small_buffer_t;
    typedef UINT16 large_buffer_t;
    typedef UINT32 huge_buffer_t;
    
    typedef huge_buffer_t buffer_size_t;

    //
    // -------------------------------------------------------------------------
    // 			Class definition
    // -------------------------------------------------------------------------
    //

    template <class T>
    class DataSet
    {
    public:
      //typedef UINT32 buffer_size_t;

      DataSet(){}
      virtual ~DataSet(){}

      virtual T* append(void)=0;
      virtual T* append(const T& ptrItem)=0;
      virtual buffer_size_t getSize(void)=0;
      virtual void clear(void)=0;


    };


    /*!
     * \brief Class for static buffer
     * This class use two template parameters:
     *  - T: data type.
     *  - S: type for buffer index.
     */
    template <class T>
    class Buffer: public DataSet<T>
    {

    public:

      //typedef UINT32 buffer_size_t;

      //! \brief Pointer to the data buffer
      T* _ptrBuffer;

      //! \brief Size of allocate memory
      buffer_size_t _uiBufferSize;

      //! \brief Amount of items into buffer
      buffer_size_t _uiLength;


      /*! \brief Buffer constructor
       * Constructor for empty Buffer
       * No allocation memory
       */
      Buffer(): _ptrBuffer(NULL), _uiBufferSize(0), _uiLength(0)
      {
        TLOG("Buffer<T>::Buffer()\n");
      }
      /*! \brief Buffer constructor
       * Create the buffer and alloc memory for uiSize_IN items
       */
      Buffer(buffer_size_t uiSize_IN): _ptrBuffer(NULL), _uiBufferSize(uiSize_IN), _uiLength(0)
      {
        TLOG("Buffer<T>::Buffer(S uiSize_IN): %d\n", uiSize_IN);
        allocate(uiSize_IN);
      }

      /*! \brief Buffer destroy
       * Destroy the buffer and calls "free" for each item
       */
      virtual ~Buffer()
      {
        TLOG("Buffer<T>::~Buffer()\n");

        if(_ptrBuffer)
	{
	  // destroy each item
            if(_uiLength)
            {
                WLOG( "Called Destroy method, but it is not empty! Delete items\n");
	        deleteItems();
            }
            
	    free( _ptrBuffer);
	    _ptrBuffer=NULL;

	}
        _uiBufferSize = 0;
        _uiLength = 0;

      }

      /*! \brief Use an existent allocated buffer
      */
      void useExistingBuffer(const T* ptrBuffer_IN);

      virtual buffer_size_t getSize(void)
      {
          return _uiLength;
      }

      /*! \brief Allocate memory for uiInitSize bytes
       * If the buffer is not empty the method free the memory and allocate a new block
       */
      void allocate(const buffer_size_t uiInitSize);

      /*! \brief Overload operator []
       * Return a reference the the uiIndx_IN item.
       * Exception raised:
       *     EmptyBufferException: try to access an empty buffer. ("allocate" is not called)
       *     OutOfBoundException: index overflow
       */
      T& operator[](const buffer_size_t uiIndx_IN)
      {

        if(!_uiBufferSize)
        {
          THROW_EXCEPTION(EmptyBufferException);
        }

        if(uiIndx_IN >= _uiLength)
        {
          THROW_EXCEPTION(composite::excps::OutOfBoundException);
        }

        return _ptrBuffer[uiIndx_IN];
      }


      /*! \brief Add an item to the buffer
       * Add an item to the buffer
       * Exception raised:
       *     EmptyBufferException: try to access an empty buffer. ("allocate" is not called)
       *     OutOfBoundException: index overflow (reach the maximum buffer size)
       */
      virtual T* append(void)
      {
        if(!_uiBufferSize)
        {
          THROW_EXCEPTION(EmptyBufferException);
        }

        if(_uiLength ==_uiBufferSize)
        {
          THROW_EXCEPTION(composite::excps::OutOfBoundException);
        }

        return _ptrBuffer +_uiLength++;

      }

      /*! \brief Add the item "ptrItem" to the buffer
       * Add the item "ptrItem" to the buffer
       * ATTENTION: ptrItem has to implement copy constructor!
       * Exception raised:
       *     EmptyBufferException: try to access an empty buffer. ("allocate" is not called)
       *     OutOfBoundException: index overflow (reach the maximum buffer size)
       */
      virtual T* append(const T& ptrItem)
      {
	if(!_uiBufferSize)
	{
	  THROW_EXCEPTION(EmptyBufferException);
	}

	if(_uiLength ==_uiBufferSize)
	{
	  THROW_EXCEPTION(composite::excps::OutOfBoundException);
	}

	return new ( append() ) T(ptrItem);
      }
      
      virtual void clear(void);

    protected:

      /*! \brief Add the item ptrItem to the buffer
       * Calls "free" for each item and reset the memory
       */
      void deleteItems(void)
      {
	TLOG("Buffer<T,S>::deleteItems(void)\n");
        
        if(!_uiLength)
            return;

	//T* item;

	for( buffer_size_t indx=0; indx < _uiLength; indx++)
	{
	    ((T*)(_ptrBuffer + indx))->~T();
	}

	// reset all memory
        memset(_ptrBuffer, 0,_uiLength*sizeof(T) );

	_uiLength=0;

      }

    }; // end Class definition


    //
    // -------------------------------------------------------------------------
    // 			Method implement
    // -------------------------------------------------------------------------
    //

    template <class T>
    void Buffer<T>::useExistingBuffer(const T* ptrBuffer_IN)
    {
      _ptrBuffer = ptrBuffer_IN;
    }


    template <class T>
    void Buffer<T>::clear(void)
    {
        if(!_ptrBuffer || !_uiLength)
            return;
        
        deleteItems();
        
        _uiLength = 0;

    }
    
    /*! \brief Allocate buffer
     * Allocate the memory for uiInitSize_in items
     * Exception raised:
           OutOfMemoryException
     */
    template <class T>
    void Buffer<T>::allocate(const buffer_size_t uiInitSize_in)
    {
      TLOG( "void Buffer<T,S>::allocate(const buffer_size_t uiInitSize_in): %d\n",uiInitSize_in);

      // Se il buffer è già stato creato lo svuoto
      if(_ptrBuffer)
      {
	  // Elimino tutti gli item presenti nell'buffer
	  deleteItems();
      }


      if(!uiInitSize_in)
        return;


      // Controllo che la dimensione desiderata non sia già quella attuale
      if( uiInitSize_in != _uiBufferSize)
      {

          // Se il buffer non è vuoto chiamo realloc
          if(_ptrBuffer)
	  {
              DLOG(  "Realloc Buffer with %u items (item size %lu bytes, buffer size: %lu bytes)\n",uiInitSize_in, sizeof(T), sizeof(T)*uiInitSize_in);

	      T* ptrNewBuffer = NULL;
	      if(!(ptrNewBuffer = (T*)realloc(_ptrBuffer, (uiInitSize_in)*sizeof(T))))
	      {
		 THROW_EXCEPTION(composite::excps::OutOfMemoryException);
	      }
	      _ptrBuffer=ptrNewBuffer;

	  }
          // Se il buffer esiste già chiamo malloc
          else
          {

	    DLOG(  "Create Buffer with %u items (item size %u bytes, buffer size: %lu bytes)\n",uiInitSize_in, sizeof(T), sizeof(T)*uiInitSize_in);

	    if(!(_ptrBuffer = (T*)calloc(uiInitSize_in, sizeof(T))))
	    {
		_ptrBuffer = NULL;
		THROW_EXCEPTION(composite::excps::OutOfMemoryException);
	    }

         }

          _uiBufferSize = uiInitSize_in;

      }


    }


  }

}


#endif /* ARRAY_HPP_ */
