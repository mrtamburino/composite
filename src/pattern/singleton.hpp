/*
 * singleton.hpp
 *
 *  Created on: Jun 22, 2011
 *      Author: ale
 */

#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

#include <cstdlib>
#include "../logs/log.h"

#define _SUBMODULE_SINGLETON_  "Singleton"

namespace composite
{

  /*!
   * \brief Classe generica che implementa il pattern singleton
   *
   * Classe che implementa il pattern singleton. La classe singleton
   * deve avere questa classe com padre.
*/

  template <class T>
  class SingletonLifeCycle
  {
  public:
    static T* create(void)
    {
      //TMLOG(_SUBMODULE_SINGLETON_,"SingletonLifeCycle::create\n");
      static T _newInstance;
      return  &_newInstance;
    }
    static void destroy(void)
    {
      //TMLOG(_SUBMODULE_SINGLETON_,"SingletonLifeCycle::destroy\n");
    }

  };

  template <class T, template<class> class TSLC=SingletonLifeCycle >
  class Singleton
  {
  public:

    static T& getInstance(void)
    {
      //TLOG("Singleton::getInstance\n");
      if(!_instance)
        {
          _instance = TSLC<T>::create();
          std::atexit( (TSLC<T>::destroy) );
        }
      return *_instance;
    }

  protected:

  private:

    static T* _instance;

    /*!
     * \brief Costruttore
     */
    Singleton(){
      //TMLOG(_SUBMODULE_SINGLETON_,"Singleton::Singleton\n");
    }

    /*!
     * \brief Distruttore
     */
    ~Singleton(){
      //TMLOG(_SUBMODULE_SINGLETON_,"Singleton::~Singleton\n");
      TSLC<T>::destroy();
    }
  };

  template <class T, template<class> class TSLC >
  T* Singleton<T,TSLC>::_instance;

}

#endif /* SINGLETON_HPP_ */
