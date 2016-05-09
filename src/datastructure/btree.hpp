/*
 * btee.hpp
 *
 *  Created on: Nov 16, 2014
 *      Author: ale
 */

#ifndef BTREE_HPP_
#define BTREE_HPP_

#include <stdlib.h>

namespace composite
{

  namespace dts
  {

    template <class T>
    class BNodeDown
    {
      public:
      BNodeDown():ptrLeft(NULL), ptrRight(NULL){}

	virtual ~BNodeDown()
	{
	  if(ptrLeft)
	    delete ptrLeft;

	  if(ptrRight)
	  	    delete ptrRight;
	}

	BNodeDown<T>* ptrLeft;
	BNodeDown<T>* ptrRight;


      private:
    };

    template <class T>
    class BNodeUpDown
    {
    public:
      BNodeUpDown():ptrParent(NULL),ptrLeft(NULL), ptrRight(NULL){}

      virtual ~BNodeUpDown()
      {
	if(ptrLeft)
	  delete ptrLeft;

	if(ptrRight)
	  delete ptrRight;
      }

      BNodeUpDown<T>* ptrParent;
      BNodeUpDown<T>* ptrLeft;
      BNodeUpDown<T>* ptrRight;

    };

    template <class B>
    B* buildNode()
    {
      return new B();
    }

    template <class B>
    B* buildRoot()
    {
      return buildNode<B>();
    }

    template <class B,class T>
    class BNode: public B
    {
    public:
      BNode(){}

      T* getData(void)
      {
	return &data;
      }

      T data;

    };

    template <class B,class T>
    class BTBrowser
    {
    public:
      BTBrowser(BNode<B,T>& ptrNode_IN):_currentNode(ptrNode_IN){}


      T* moveToLeft(void)
      {
	if(_currentNode)
	  _currentNode = _currentNode.ptrLeft;
	return getData();
      }

      T* moveToRight(void)
      {
	if(_currentNode)
	  _currentNode = _currentNode.ptrRight;
	return getData();
      }

      T* moveUp(void);

      T* getData(void)
      {
	if(_currentNode) return _currentNode.getData();
	else return NULL;
      }

    private:
      BNode& _currentNode;

    };

    template <BNodeDown,class T>
    T* BTBrowser<BNodeDown,T>::moveUp(void)
    {
      return NULL;
    }

    template <BNodeUpDown,class T>
    T* <BNodeDown,T>::moveUp(void)
    {
      if(ptrParent) return ptrParent.getData();
      	else return NULL;
    }


  }



}


#endif /* BTEE_HPP_ */
