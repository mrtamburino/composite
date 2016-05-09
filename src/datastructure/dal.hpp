/*
 * index.hpp
 *
 *  Created on: Jan 25, 2014
 *      Author: ale
 */

#ifndef DATA_ALGORITHM_HPP_
#define DATA_ALGORITHM_HPP_

#include "buffer.hpp"
#include "../types/types.h"

namespace composite
{

  namespace dts
  {

    template <class T>
    class BaseAl
    {
    public:
      BaseAl():_ptrBuffer_(NULL){}
      BaseAl(Buffer<T>* ptrBuffer_IN):_ptrBuffer_(ptrBuffer_IN){}

      void setBuffer(Buffer<T>* ptrBuffer_IN){ _ptrBuffer_ = ptrBuffer_IN; }
    protected:
          Buffer<T>* _ptrBuffer_;

          inline void swap(const typename DataSet<T>::buffer_size_t uiIndxA_IN, const typename DataSet<T>::buffer_size_t uiIndxB_IN);
    };

    template <class T, class K=T>
    class Sorter: public BaseAl<T>
    {
    public:
      Sorter():BaseAl<T>(){}
      Sorter(Buffer<T>* ptrBuffer_IN):BaseAl<T>(ptrBuffer_IN){}
      virtual ~Sorter(){}
      //virtual void sort(void) = 0;
      virtual T* insert(const K& item_IN, BOOLEAN bUniue_IN) = 0;
      virtual T* search(const K& item_IN) = 0;
    };

    template <class T, class K=T>
    class QSorter: public Sorter<T,K>
    {
    public:
      QSorter<T,K>():Sorter<T,K>(){}
      QSorter<T,K>(Buffer<T>* ptrBuffer_IN):Sorter<T>(ptrBuffer_IN){}
      ~QSorter<T,K>(){}


      //void sort(void);
      T* insert(const K& item_IN, BOOLEAN bUniue_IN);
      T* search(const K& item_IN);

    };

    // ------------------------------------------------------------------------
    // ---                        BufferIndex<T,S>                           ---
    // ------------------------------------------------------------------------

    template <class T>
    void BaseAl<T>::swap(const typename DataSet<T>::buffer_size_t uiIndxA_IN, typename DataSet<T>::buffer_size_t uiIndxB_IN)
    {

      if(uiIndxA_IN == uiIndxB_IN)
    	return;

      UINT8* pA = (UINT8*)(_ptrBuffer_->_ptrBuffer+uiIndxA_IN);
      UINT8* pB = (UINT8*)(_ptrBuffer_->_ptrBuffer+uiIndxB_IN);

      for(unsigned int indx = 0; indx < sizeof(T) ; indx++)
      {

    	pA[indx] = pA[indx] ^ pB[indx];
    	pB[indx] = pA[indx] ^ pB[indx];
    	pA[indx] = pA[indx] ^ pB[indx];
      }

    }

    template <class T, class K>
    T* QSorter<T,K>::insert(const K& item_IN, BOOLEAN bUniue_IN)
    {

      if(!BaseAl<T>::_ptrBuffer_->_uiLength)
      {
        return BaseAl<T>::_ptrBuffer_->append();
      }

      T* bottom = BaseAl<T>::_ptrBuffer_->_ptrBuffer;
      typename DataSet<T>::buffer_size_t top = BaseAl<T>::_ptrBuffer_->_uiLength - 1;
      typename DataSet<T>::buffer_size_t middle;

      while( top )
      {
        middle = ( top >> 1);

        if (bottom[middle] == item_IN)
        {
          bottom += middle;
          break;
        }


        if( bottom[middle] > item_IN )
        {
          top = middle ? middle -1 : 0;
        }
        else
        {
          bottom += middle + 1;
          top -= (middle + 1);
        }

      }

      if( bottom[0] == item_IN )
      {
          if ( bUniue_IN) return bottom;
      }
      else
      {
        if( bottom[0] < item_IN   )
        {
          bottom++;
          if(bottom == (BaseAl<T>::_ptrBuffer_->_ptrBuffer + BaseAl<T>::_ptrBuffer_->_uiLength))
          return BaseAl<T>::_ptrBuffer_->append();

        }
      }

      BaseAl<T>::_ptrBuffer_->append();
      memmove( (bottom + 1), (bottom), sizeof(T)*( ((BaseAl<T>::_ptrBuffer_->_ptrBuffer + BaseAl<T>::_ptrBuffer_->_uiLength-1) - bottom)));
      //new (bottom) T(item_IN);

      return bottom;

    }

    template <class T, class K>
    T* QSorter<T,K>::search(const K& item_IN)
    {

      if(!BaseAl<T>::_ptrBuffer_->_uiLength)
      {
        return NULL;
      }

      T* bottom = BaseAl<T>::_ptrBuffer_->_ptrBuffer;
      typename DataSet<T>::buffer_size_t top = BaseAl<T>::_ptrBuffer_->_uiLength - 1;
      typename DataSet<T>::buffer_size_t middle;

      while( top )
      {
        middle = ( top >> 1);

        if( bottom[middle] == item_IN )
          return bottom + middle;

        if( bottom[middle] > item_IN )
        {
          top = middle ? middle -1 : 0;
        }
        else
        {
          bottom += middle + 1;
          top -= (middle + 1);
        }

      }

      if( bottom[0] == item_IN )
      {
        return bottom;
      }

      return NULL;

    }

  }
}

#endif /* INDEX_HPP_ */
