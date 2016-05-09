/*
 * module.hpp
 *
 *  Created on: Dec 1, 2013
 *      Author: ale
 */

#ifndef MODULE_HPP_
#define MODULE_HPP_

#include <pthread.h>
#include "../exceptions/excps.hpp"
#include "../pattern/singleton.hpp"
#include "groundexcps.hpp"
#include "basemlc.hpp"


#define MODULE_STARTED  (eState==MS_STARTED)
#define MODULE_SHUTDOWN (eState==MS_SHUTDOWN)
#define MODULE_STARTING (eState==MS_STARTING)

#define DECLARE_MODULE_PROXY(MODULE, PROXY)     composite::ground::ModuleProxy<MODULE> PROXY

namespace composite
{

  namespace ground
  {

    template <class T>
    class ModuleLifeCycle: protected BaseModuleLifeCycle
    {
      public:

      ModuleLifeCycle():BaseModuleLifeCycle(), _ptrModule_(NULL)
      {
        //TLOG("T* composite::ground::ModuleLifeCycle<T>\n");
        pthread_mutex_init (&_mtxMutx_, NULL);

      }

      virtual ~ModuleLifeCycle()
      {
        //TLOG("T* composite::ground::~ModuleLifeCycle<T>\n");
        if(_ptrModule_)
        {
            WLOG("Destroyng referenced module!!\n");
            uiReferenceCount = 0;
            delete _ptrModule_;
            eState = MS_SHUTDOWN;
        }
      }


      T* bind(void)
      {

        //TLOG("T* composite::ground::ModuleLifeCycle<T>::bind(void)\n");

        pthread_mutex_lock(&_mtxMutx_);

        try
        {

          if(!_ptrModule_)
          {

              if(uiReferenceCount)
              {
                  THROW_EXCEPTION(ModuleReferencedException);
              }

             eState = MS_STARTING;
             _ptrModule_ = new T();
             eState = MS_STARTED;

          }


        }
        catch(composite::excps::GenericException* e)
        {
            pthread_mutex_unlock(&_mtxMutx_);
            eState = MS_UNCOMPLETESTART;
            throw e;

        }
        catch(...)
        {
            pthread_mutex_unlock(&_mtxMutx_);
            eState = MS_UNCOMPLETESTART;
            THROW_EXCEPTION(StartModuleException);
        }
        
        pthread_mutex_unlock(&_mtxMutx_);

        uiReferenceCount++;

        return _ptrModule_;
      }

      void unBind(void)
      {
        //TLOG("T* composite::ground::ModuleLifeCycle<T>::unBind(void)\n");

        pthread_mutex_lock(&_mtxMutx_);
        try
        {

          if(!uiReferenceCount)
          {
              THROW_EXCEPTION(ModuleUnreferencedException);
          }

          if(!(--uiReferenceCount))
          {
            delete _ptrModule_;
            _ptrModule_ = NULL;
            eState = MS_SHUTDOWN;
          }
          
        }
        catch(composite::excps::GenericException* e)
        {
            pthread_mutex_unlock(&_mtxMutx_);
            throw e;

        }
        catch(...)
        {
            pthread_mutex_unlock(&_mtxMutx_);
            THROW_EXCEPTION(StartModuleException);
        }
        
        pthread_mutex_unlock(&_mtxMutx_);


      }

      private:
        T*             _ptrModule_;
        pthread_mutex_t _mtxMutx_;

    };

    template <class T>
    class ModuleProxy
    {
      public:

      ModuleProxy():ptrReference(NULL)
      {
        //TLOG("composite::ground::ModuleProxy()\n");
      }
      ~ModuleProxy()
      {
        //TLOG("composite::ground::~ModuleProxy()\n");
        unbind();
      }

      void bind()
      {
        ptrReference = composite::Singleton<ModuleLifeCycle<T> >::getInstance().bind();
      }

      void unbind()
      {
        if(ptrReference)
        {
          composite::Singleton<ModuleLifeCycle<T> >::getInstance().unBind();
          ptrReference = NULL;
        }
      }

      inline T* operator->()
      {
        return ptrReference;
      }

      T* ptrReference;

    };

  }

}


#endif /* MODULE_HPP_ */
