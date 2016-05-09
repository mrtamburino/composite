/*
 * mdchain.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: ale
 */

#include <stdlib.h>
#include "mdchain.hpp"

namespace composite
{

  namespace ground
  {

    ModuleChain::ModuleChain()
    {
      ptrChain_ = NULL;
    }

    ModuleChain::~ModuleChain()
    {

    }

    void ModuleChain::addModule(BaseModuleLifeCycle* ptrMLC_IN)
    {

      if(!ptrMLC_IN)
        {
          return;
        }

      MLCNode* ptrNewNode = new MLCNode();
      ptrNewNode->ptrNext_ = ptrChain_;
      ptrNewNode->ptrMLC_ = ptrMLC_IN;

      ptrChain_ = ptrNewNode;

    }


  }

}


