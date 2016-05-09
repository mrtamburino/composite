/*
 * application.h
 *
 *  Created on: Dec 26, 2012
 *      Author: ale
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#define SET_AS_APP(APPLICATION) composite::ground::ApplicationInterface* _application_ = new APPLICATION()

#include "../logs/log.h"

namespace composite
{

  namespace ground
  {

    class ApplicationInterface
    {
    public:

      ApplicationInterface() throw(){}
      virtual ~ApplicationInterface(){}

      virtual void getApplicationInfo(void) = 0;
      virtual void startUp(void) = 0;
      virtual void run(void) = 0;
      virtual void shutDown(void) = 0;
    };

  }
}


#endif /* APPLICATION_H_ */
