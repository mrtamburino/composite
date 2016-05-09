/*
 * lslink.hpp
 *
 *  Created on: Jan 18, 2014
 *      Author: ale
 */

#ifndef LSLINK_HPP_
#define LSLINK_HPP_

#include <stdlib.h>
//#include <new>

namespace composite
{

  namespace dts
  {

/*
 * -----------------------------------
 * | Definition of class ListIyem<T> |
 * -----------------------------------
 */

    /*! \brief Lnked List Item
     *  Each item contains a reference to the next item and
     *  an object (not a pointer) of type T
     */
    template <typename T>
    class ListItem
    {

    public:

      ListItem():_ptrNext(NULL)
      {
    	TLOG("ListItem<T>ListItem()\n");
      }
      ListItem(const T& ptrItem):_ptrNext(NULL)
      {
    	TLOG("ListItem<T>ListItem(const T& ptrItem)\n");
        _ptrData_ = ptrItem;
      }
      //! \brief ListItem destructor
      ~ListItem()
      {
        TLOG("ListItem<T>::~ListItem()\n");
      }

      //! Pointer to the next element of type ListItem<T>
      ListItem<T>* _ptrNext;
      //! Object of type T
      T _ptrData_;

    };

    /*
     * -----------------------------------
     * | Definition of class ListIyem<T *> |
     * -----------------------------------
     */

    /*! \brief Lnked List Item
     *  Each item contains a reference to the next item and
     *  an object (not a pointer) of type T
     */
    template <typename T>
    class ListItem<T *>
    {

    public:

      ListItem():_ptrNext(NULL),_ptrData_(NULL)
      {
    	  TLOG("ListItem<T*>ListItem()\n");
      }
      ListItem(T* ptrItem):_ptrNext(NULL)
      {
    	TLOG("ListItem<T*>ListItem(T* ptrItem)\n");
        _ptrData_ = ptrItem;
      }
      //! \brief ListItem destructor
      ~ListItem()
      {
        TLOG("ListItem<T*>::~ListItem()\n");
      }

      //! Pointer to the next element of type ListItem<T>
      ListItem<T*>* _ptrNext;
      //! Object of type T
      T* _ptrData_;


    };

    /*
     * -----------------------------------
     * | Definition of class List<T>     |
     * -----------------------------------
     */

    /*! \brief Class that implement the Linked List
     * Generic specialization of the class. Each item is of type ListItem<T>
     */
    template <typename T>
    class List
    {

    public:

      typedef ListItem<T> item_t;

      List():_ptrFirstItem(NULL), _ptrLastItem(NULL), _uiLength(0)
      {
    	TLOG("List<T>List()\n");
      }
      ~List()
      {

        TLOG("List<T>::~List()\n");

        item_t* curentItem = _ptrFirstItem;
        item_t* tmp = NULL;
        while(curentItem)
        {
          tmp = curentItem;
          curentItem = curentItem->_ptrNext;
          delete tmp;
        }
      }


      /*! \brief Append an empty object.
       * Append an empty object of type T using the new operator without parameter
       * So the object T must implement default costructor
       */
      inline T* append();

      /*! \brief Append an object to the list.
       * Append an empty object of type T.
       * The object T must implement the copy constructor T(const T&)
       */
      inline T* append(const T& ptrItem);

      //! \brief First item of the list
      item_t* _ptrFirstItem;
      //! \brief Last item of the list
      item_t* _ptrLastItem;

      UINT32 _uiLength;
    };

    template <typename T>
    class ListItemRef
    {
    public:
    	ListItemRef(List<T>* ptrList_IN)
        {
    		_ptrList = ptrList_IN;
    		_ptrCurrent = _ptrList ? _ptrList->_ptrFirstItem : NULL;
        }

    	T* getDataAndMoveForward(void)
    	{
    		if(_ptrCurrent)
    		{
    			T* data = &(_ptrCurrent->_ptrData_);
    			_ptrCurrent = _ptrCurrent->_ptrNext;
    			return data;
    		}

    		return NULL;
    	}

    	void moveToFirst(void)
    	{
    		_ptrCurrent = _ptrList ? _ptrList->_ptrFirstItem : NULL;
    	}

    	T* getData(void)
    	{
    		return _ptrCurrent ? &(_ptrCurrent->_ptrData_) : NULL;
    	}

    private:
    	ListItem<T>* _ptrCurrent;
    	List<T>* _ptrList;
    };

    /*
     * -----------------------------------
     * | Definition of class List<T *>   |
     * -----------------------------------
     */

    /*! \brief Class that implement the Linked List with pointer object
     * Template specialization of the class List<T> that enable to use object of type pointer
     */
    template <typename T>
    class List<T *>
    {
    public:

      typedef ListItem<T*> item_t;

      List():_ptrFirstItem(NULL), _ptrLastItem(NULL), _uiLength(0)
      {
    	TLOG("List<T*>List()\n");
      }
      ~List()
      {

        TLOG("List<T*>::~List()\n");

        item_t* curentItem = _ptrFirstItem;
        item_t* tmp = NULL;
        while(curentItem)
        {
          tmp = curentItem;
          curentItem = curentItem->_ptrNext;
          delete tmp;
        }

      }

      item_t* getItemReference(void)
	  {
    	return _ptrFirstItem;
	  }


      /*! \brief Append an empty object.
       * Append an empty object of type T* using the new operator without parameter
       */
      inline T* append();

      /*! \brief Append an object to the list.
       * Append an empty object of type T.
       */
      inline T* append(T* ptrItem);

      //! \brief First item of the list
      ListItem<T*>* _ptrFirstItem;
      //! \brief Last item of the list
      ListItem<T*>* _ptrLastItem;

      UINT32 _uiLength;


    };

    template <typename T>
    class ListItemRef<T *>
    {
    public:
    	ListItemRef(List<T*>* ptrList_IN)
        {
    		_ptrList = ptrList_IN;
    		_ptrCurrent = _ptrList ? _ptrList->_ptrFirstItem : NULL;
        }

    	T* getDataAndMoveForward(void)
    	{
    		if(_ptrCurrent)
    		{
    			T* data = _ptrCurrent->_ptrData_;
    			_ptrCurrent = _ptrCurrent->_ptrNext;
    			return data;
    		}

    		return NULL;
    	}

    	void moveToFirst(void)
    	{
    		_ptrCurrent = _ptrList ? _ptrList->_ptrFirstItem : NULL;
    	}

    	T* getData(void)
    	{
    		return _ptrCurrent ? _ptrCurrent->_ptrData_ : NULL;
    	}

    private:
    	ListItem<T*>* _ptrCurrent;
    	List<T*>* _ptrList;
    };


/*
 * -----------------------------------------
 * | Start implementation of class List<T> |
 * -----------------------------------------
 */

    template <class T>
    T* List<T>::append()
    {
    	item_t* tmp = new ListItem<T>();

      if(_ptrLastItem)
      {
          _ptrLastItem->_ptrNext = tmp;
      }
      else
      {
          _ptrFirstItem = tmp;
      }

      _ptrLastItem = tmp;
      //return new (&(_ptrLastItem->_ptrData_)) T();

      _uiLength++;

      return &(_ptrLastItem->_ptrData_);
    }

    template <class T>
    T* List<T>::append(const T& ptrItem)
    {
    	item_t* tmp = new ListItem<T>(ptrItem);

	  if(_ptrLastItem)
	  {
	     _ptrLastItem->_ptrNext = tmp;
	  }
	  else
	  {
	    _ptrFirstItem = tmp;
	  }

	  _ptrLastItem = tmp;

	  _uiLength++;

	  return &(_ptrLastItem->_ptrData_);
    }


/*
 * -------------------------------------------
 * | Start implementation of class List<T *> |
 * -------------------------------------------
 */


    template <class T>
    T* List<T *>::append()
    {
    	item_t* tmp = new ListItem<T*>();

      if(_ptrLastItem)
      {
        _ptrLastItem->_ptrNext = tmp;
      }
      else
      {
        _ptrFirstItem = tmp;
      }

      _ptrLastItem = tmp;

      _uiLength++;

      return _ptrLastItem->_ptrData_;
    }

    template <class T>
    T* List<T *>::append(T* ptrItem)
    {
    	item_t* tmp = new ListItem<T*>(ptrItem);

      if(_ptrLastItem)
      {
         _ptrLastItem->_ptrNext = tmp;
      }
      else
      {
        _ptrFirstItem = tmp;
      }

      _ptrLastItem = tmp;

      _uiLength++;

      return _ptrLastItem->_ptrData_;
    }


  }

}

#endif /* LSLINK_HPP_ */
