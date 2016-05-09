/*
 * index.hpp
 *
 *  Created on: Apr 26, 2015
 *      Author: ale
 */

#ifndef SRC_DATASTRUCTURE_INDEX_HPP_
#define SRC_DATASTRUCTURE_INDEX_HPP_

#include "dbuffer.hpp"
#include "dal.hpp"

namespace composite
{
  namespace indexes
  {

    template <class T, class S>
    class Index
    {

    public:
      //Index():_dataBuffer(NULL){}
      Index(composite::dts::BaseBuffer<T,S>* ptrDataBuffer_IN):_dataBuffer(ptrDataBuffer_IN){}

      //void setDataBuffer(composite::dts::Buffer<T,S>* ptrBuffer_IN);

    protected:
      composite::dts::DynamicBuffer<T,S> _indexBuffer;
      composite::dts::BaseBuffer<T,S>* _dataBuffer;

    };


    template <class T, class K, class S, class A=composite::dts::QSorter<T,S,K> >
    class SIndex: public Index<T,S>
    {
    public:
      SIndex(composite::dts::BaseBuffer<T,S>* ptrDataBuffer_IN ):Index<T,S>(ptrDataBuffer_IN)
      {
	// Allocate Index Buffer
	_indexBuffer.allocate(ptrDataBuffer_IN->getSize());

	// Initialize sorter
	_sorter.setArray(_Index);

	_sorter.sort();
      }



    private:
      A _sorter;
    };



  }
}


#endif /* SRC_DATASTRUCTURE_INDEX_HPP_ */
