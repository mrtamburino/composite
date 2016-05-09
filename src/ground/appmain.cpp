/*
 * appmain.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: ale
 */

#include "../exceptions/excps.hpp"
#include "../logs/log.h"
#include "application.hpp"

extern composite::ground::ApplicationInterface* _application_;

int main(void)
{

  int returnCode = 0;

  if(!_application_)
  {
    // Application is not defined
      exit(-1);
  }

  try
  {
    _application_->printBanner();
    _application_->startUp();
    _application_->run();

  }
  catch(composite::excps::ApplicationException* e)
  {
      e->printDetail();
      REMOVE_EXCEPTION(e);
      returnCode = -1;

  }
  catch(composite::excps::AbortException* e)
    {
        e->printDetail();
        returnCode = e->getCode();
        REMOVE_EXCEPTION(e);
    }
  catch(...)
  {
      ELOG("Undefined exception\n");
      returnCode = -1;
  }

  ILOG("\n");
  ILOG("Shutdown application!\n");
  ILOG("\n");

  try
  {
    _application_->shutDown();
  }
  catch(composite::excps::ApplicationException* e)
  {
      e->printDetail();
      REMOVE_EXCEPTION(e);
      returnCode = -1;

  }
  catch(composite::excps::AbortException* e)
    {
        e->printDetail();
        returnCode = e->getCode();
        REMOVE_EXCEPTION(e);
    }
  catch(...)
  {
      ELOG("Undefined exception\n");
      returnCode = -1;
  }

  //check for undestroyed modules...


  exit(returnCode);

}

