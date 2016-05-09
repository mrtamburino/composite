/*
 * excps.hpp
 *
 *  Created on: Dec 14, 2012
 *      Author: ale
 */

#ifndef EXCPS_HPP_
#define EXCPS_HPP_

#include <exception>
#include "../types/types.h"
#include "../logs/log.h"
#include "string.h"
#include "stdlib.h"


#define DEFINE_APP_EXCEPTION(CLASS, DESCRIPTION)    class CLASS: public composite::excps::GenericException\
  {\
  public:\
    CLASS(int uiLineNumber, const char* ptrFileName, composite::excps::excp_gravity_t eGravity):GenericException(uiLineNumber, ptrFileName, eGravity){}\
    CLASS(int uiLineNumber, const char* ptrFileName):GenericException(uiLineNumber, ptrFileName){}\
    CLASS(int uiLineNumber, const char* ptrFileName, GenericException* ptrInnerException_IN):\
       GenericException(uiLineNumber, ptrFileName, ptrInnerException_IN){}\
    const char* getExceptionName(void){return #CLASS;}\
  }


#define THROW_EXCEPTION(TYPE)            throw new TYPE(__LINE__,__FILE__ )
#define RAISE_OOB                        THROW_EXCEPTION(composite::excps::OutOfBoundException);
#define RAISE_OOM                        THROW_EXCEPTION(composite::excps::OutOfMemoryException);
#define WRAP_EXCEPTION(TYPE,EXCEPTION)   throw new TYPE(__LINE__,__FILE__, EXCEPTION )
#define REMOVE_EXCEPTION(EXCEPTION)      if(EXCEPTION){delete EXCEPTION;}

namespace composite
{
  namespace excps
  {

    typedef enum {eg_warning=0, eg_error, eg_critical} excp_gravity_t;

    class GenericException: public std::exception
    {
    public:
      GenericException(int uiLineNumber, const char* ptrFileName):
	_ptrInnerException_(NULL),
	_uiLine(uiLineNumber),
	_eGravity(eg_error)
    {
	setFileName(ptrFileName);
    }

      GenericException(int uiLineNumber, const char* ptrFileName, excp_gravity_t eGravity):
      	_ptrInnerException_(NULL),
      	_uiLine(uiLineNumber),
      	_eGravity(eGravity)
          {
      	setFileName(ptrFileName);
          }

      GenericException(int uiLineNumber, const char* ptrFileName,  GenericException* ptrInnerException_IN ):
	_ptrInnerException_(ptrInnerException_IN),
	_uiLine(uiLineNumber)
      {
	setFileName(ptrFileName);
	if(ptrInnerException_IN)
	  _eGravity =  ptrInnerException_IN->getGravity();
	else
	  _eGravity=eg_error;
      }

      virtual ~GenericException() throw()
      {
          if(_sFileName)
            free(_sFileName);

          if(_ptrInnerException_)
          {
            REMOVE_EXCEPTION(_ptrInnerException_);
          }

      }

      const char* getFileName(void)
      {
          return _sFileName;
      }

      const int getLineumber(void)
      {
          return _uiLine;
      }

      const excp_gravity_t getGravity(void)
      {
          return _eGravity;
      }

      void  setGravity(excp_gravity_t eGravity)
      {
          _eGravity = eGravity;
      }
      
      void printTrace(void)
      {
          if(_eGravity==eg_warning)
          {
              WLOG("%s [%d]: %s\n", _sFileName, _uiLine, getExceptionName());
          }
          else
          {
              ELOG("%s [%d]: %s\n", _sFileName, _uiLine, getExceptionName());
          }
          
          if(_ptrInnerException_)
              _ptrInnerException_->printTrace();
      }

      virtual const char* getExceptionName(void){return "GenericException";}

      protected:
        GenericException* _ptrInnerException_;
        int _uiLine;
        char* _sFileName;
        excp_gravity_t _eGravity;


      private:

        void setFileName(const char* ptrFileName)
        {
          if(ptrFileName)
          {
            if(!(_sFileName=(char*)malloc(strlen(ptrFileName)+1)))
            {
              _sFileName=NULL;
            }
            else
            {
              memcpy(_sFileName, ptrFileName, strlen(ptrFileName)+1);
            }
          }
          else
            _sFileName=NULL;
        }

      };

      DEFINE_APP_EXCEPTION(OutOfBoundException, "Index out of bound!");
      DEFINE_APP_EXCEPTION(OutOfMemoryException, "Allocation failed! Not enough memory!");
      DEFINE_APP_EXCEPTION(ForbiddenCallException, "Forbidden call method!");
      DEFINE_APP_EXCEPTION(NotImplementedMethodException, "Method not yet implemented!");
      DEFINE_APP_EXCEPTION(IllegalPrameterException, "The parameter value not admitted!");
      DEFINE_APP_EXCEPTION(FileNotFoundException, "File not found!");

  }

}


#endif /* EXCPS_HPP_ */
