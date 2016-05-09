/*
 * groundexcps.hpp
 *
 *  Created on: Dec 1, 2013
 *      Author: ale
 */

#ifndef GROUNDEXCPS_HPP_
#define GROUNDEXCPS_HPP_

#include "../exceptions/excps.hpp"

namespace composite
{

  namespace ground
  {

    DEFINE_APP_EXCEPTION(ModuleStartingException, "Module is starting!");
    DEFINE_APP_EXCEPTION(ModuleUnreferencedException, "Module is not referenced!");
    DEFINE_APP_EXCEPTION(ModuleReferencedException, "Startup a referenced module!");
    DEFINE_APP_EXCEPTION(StartModuleException, "ErrorStartingModule!");

  }

}

#endif /* GROUNDEXCPS_HPP_ */
