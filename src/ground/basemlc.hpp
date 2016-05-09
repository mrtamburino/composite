/*
 * basemlc.hpp
 *
 *  Created on: Dec 2, 2013
 *      Author: ale
 */

#ifndef BASEMLC_HPP_
#define BASEMLC_HPP_

#include "../types/types.h"

namespace composite
{

  namespace ground
  {

    typedef enum {MS_SHUTDOWN=0, MS_STARTING, MS_UNCOMPLETESTART, MS_STARTED } module_state_t;


    class BaseModuleLifeCycle
    {
    public:
      BaseModuleLifeCycle():eState(MS_SHUTDOWN), uiReferenceCount(0){}
      virtual ~BaseModuleLifeCycle(){}

      virtual void unBind(void) = 0;

    protected:
      module_state_t eState;
      UINT32         uiReferenceCount;

    };

  }

}


#endif /* BASEMLC_HPP_ */
