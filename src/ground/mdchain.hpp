/*
 * mdchain.hpp
 *
 *  Created on: Dec 1, 2013
 *      Author: ale
 */

#ifndef MDCHAIN_HPP_
#define MDCHAIN_HPP_

#include "basemlc.hpp"

namespace composite
{

  namespace ground
  {

    struct MLCNode
    {
      BaseModuleLifeCycle* ptrMLC_;
      MLCNode* ptrNext_;
    };

    class ModuleChain
    {
    public:

      ModuleChain();
      ~ModuleChain();

      void addModule(BaseModuleLifeCycle* ptrMLC_IN);

      MLCNode* ptrChain_;
    };

  }

}

#endif /* MDCHAIN_HPP_ */
