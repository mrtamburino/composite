/*
 * preflog.h
 *
 *  Created on: Nov 27, 2011
 *      Author: ale
 */

#ifndef PREFLOG_H_
#define PREFLOG_H_

/*! \brief Costante che indica il singolo per log di errore*/
#define _LOG_SEVERITY_PREFIX_ERROR   "(X) "
/*! \brief Costante che indica il singolo per log di warning*/
#define _LOG_SEVERITY_PREFIX_WARNING "/!\\ "
/*! \brief Costante che indica il singolo per log di debug*/
#define _LOG_SEVERITY_PREFIX_DEBUG   " *  "
/*! \brief Costante che indica il singolo per log di tipo trace*/
#define _LOG_SEVERITY_PREFIX_TRACE   " ~  "
/*! \brief Costante che indica il singolo per log informativi*/
#define _LOG_SEVERITY_PREFIX_INFO    "(i) "

/*! \brief ...*/
#define _LOG_SEVERITY_PREFIX         "    "
#define _LOG_OPEN_OWNER         ""
#define _LOG_CLOSE_OWNER         "::"

#endif /* PREFLOG_H_ */
