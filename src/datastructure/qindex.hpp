/*
 * qindex.hpp
 *
 *  Created on: Feb 12, 2014
 *      Author: ale
 */

#ifndef QINDEX_HPP_
#define QINDEX_HPP_

#include "dal.hpp"

namespace composite
{

  namespace dts
  {

    template <class T, class S>
    class QSortIndex: public ArrayIndex<T,S>
    {
    public:
      QSortIndex<T,S>():ArrayIndex<T,S>(){}
      QSortIndex<T,S>(Array<T,S>* ptrArray_IN):ArrayIndex<T,S>(ptrArray_IN){}
      ~QSortIndex<T,S>(){}

      //void swap(const S uiIndxA_IN, const S uiIndxB_IN);
      void sort(void);

    private:


      void partialSort(const S uiLeft_IN, const S uiRight_IN);

    };

    template <class T, class S>
    void QSortIndex<T,S>::sort(void)
    {
      if(ArrayIndex<T,S>::_ptrArray_ == NULL || ArrayIndex<T,S>::_ptrArray_->_uiLength == 0 || ArrayIndex<T,S>::_ptrArray_->_uiLength == 1)
        return;

      partialSort(0, ArrayIndex<T,S>::_ptrArray_->_uiLength - 1);

    }

    template <class T, class S>
    void QSortIndex<T,S>::partialSort(const S uiLeft_IN, const S uiRight_IN)
    {
      if(uiLeft_IN == uiRight_IN)
        return;

      S lastLessItem = uiLeft_IN;

      for(S indx = uiLeft_IN; indx < uiRight_IN; indx++)
      {
        if(ArrayIndex<T,S>::_ptrArray_->_ptrBuffer[indx] < ArrayIndex<T,S>::_ptrArray_->_ptrBuffer[uiRight_IN])
        {
          if(indx != lastLessItem)
          {
            ArrayIndex<T,S>::swap(lastLessItem,indx);
          }
          lastLessItem++;
        }
      }

      if(lastLessItem != uiRight_IN)
      {
        ArrayIndex<T,S>::swap(lastLessItem,uiRight_IN);
      }

      if(lastLessItem != uiLeft_IN )
      {
        partialSort(uiLeft_IN, lastLessItem - 1);
        partialSort(lastLessItem, uiRight_IN);
      }
      else
      {
        partialSort(lastLessItem+1, uiRight_IN);
      }

    }


  }

}


#endif /* QINDEX_HPP_ */
