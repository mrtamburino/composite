/*
 * stlog.h
 *
 *  Created on: Jun 19, 2011
 *      Author: ale
 */

#ifndef STLOG_H_
#define STLOG_H_

#include "../preflog.h"


#ifdef _FILELOG_
#error "Log on file is not supported!"
#else
#include "cnslog.h"
#endif

#ifdef _LOG_MODULE_PREFIX_
#define _LOG_PREFIX_ "["_LOG_MODULE_PREFIX_"] "
#else
#define _LOG_PREFIX_ ""
#endif

/*
------------------------------------------------------------------
|              | ELOG | WLOG | ILOG | IILOG | TLOG |  DLOG | LOG |
|--------------+------+------+------+-------+------+-------+-----|
|NO_LOG        |      |      |      |       |      |       |     |
|--------------+------+------+------+-------+------+-------+-----|
|ERROR_LOG     |   X  |      |      |       |      |       |     |
|--------------+------+------+------+-------+------+-------+-----|
|WARNING_LOG   |      |   X  |      |       |      |       |     |
|--------------+------+------+------+-------+------+-------+-----|
|INFO_LOG      |      |      |   X  |       |      |       |  X  |
|--------------+------+------+------+-------+------+-------+-----|
|TRACE_LOG     |      |      |      |       |   X  |       |     |
|--------------+------+------+------+-------+------+-------+-----|
|DEBUG_LOG     |      |      |      |       |      |   X   |     |
|--------------+------+------+------+-------+------+-------+-----|
|L1_LOG        |  X   |      |      |       |   -  |   -   |     |
|--------------+------+------+------+-------+------+-------+-----|
|L2_LOG        |  X   |   X  |      |       |   -  |   -   |     |
|--------------+------+------+------+-------+------+-------+-----|
|L3_LOG        |  X   |   X  |   X  |       |   -  |   -   |  X  |
|--------------+------+------+------+-------+------+-------+-----|
|VERBOSE_LOG   |  X   |   X  |   X  |   X   |   X  |   X   |  X  |
------------------------------------------------------------------
*/

#if !defined(NO_LOG) && defined(L1_LOG)
#define ERROR_LOG
#endif

#if !defined(NO_LOG) && defined(L2_LOG)
#define ERROR_LOG
#define WARNING_LOG
#endif

#if !defined(NO_LOG) && defined(L3_LOG)
#define ERROR_LOG
#define WARNING_LOG
#define INFO_LOG
#endif

#if !defined(NO_LOG) && defined(VERBOSE_LOG)
#define ERROR_LOG
#define WARNING_LOG
#define INFO_LOG
#define TRACE_LOG
#define DEBUG_LOG
#endif

/*! \brief Macro che traccia un log relativo ad un modulo*/
#define _LOG_(sPrefix, ...) LOG_PRINT(sPrefix""_LOG_PREFIX_""__VA_ARGS__)
#define _MLOG_(sPrefix,sModule, sComponent, ...) LOG_PRINT(sPrefix"["sModule"] {"sComponent"} "__VA_ARGS__)

#if !defined(NO_LOG) && defined(ERROR_LOG)
/*! \brief Write an error log */
#define ELOG(...) _LOG_(_LOG_SEVERITY_PREFIX_ERROR,__VA_ARGS__)
#define EMLOG(sModule, sComponent, ...) _MLOG_(_LOG_SEVERITY_PREFIX_ERROR,sModule, sComponent,__VA_ARGS__)
#else
#define ELOG(...)
#define EMLOG(...)
#endif

#if !defined(NO_LOG) && defined(WARNING_LOG)
/*! \brief Write a warning log
 * \author mrTamburino
 * \param ...
 */
#define WLOG(...) _LOG_(_LOG_SEVERITY_PREFIX_WARNING,__VA_ARGS__)
#define WMLOG(sModule, sComponent,...) _MLOG_(_LOG_SEVERITY_PREFIX_WARNING,sModule, sComponent,__VA_ARGS__)
#else
#define WLOG(...)
#define WMLOG(...)
#endif

#if !defined(NO_LOG) && defined(DEBUG_LOG)
/*! \brief Write a debug log
 * \author mrTamburino
 * \param ...
 */
#define DLOG(...) _LOG_(_LOG_SEVERITY_PREFIX_DEBUG,__VA_ARGS__)
#define DMLOG(sModule, sComponent, ...) _MLOG_(_LOG_SEVERITY_PREFIX_DEBUG,sModule, sComponent,__VA_ARGS__)
#else
#define DLOG(...)
#define DMLOG(...)
#endif

#if !defined(NO_LOG) && defined(TRACE_LOG)
/*! \brief Write a code trace log
 * \author mrTamburino
 * \param ...
 */
#define TLOG(...) _LOG_(_LOG_SEVERITY_PREFIX_TRACE,__VA_ARGS__)
#define TMLOG(sModule, sComponent, ...) _MLOG_(_LOG_SEVERITY_PREFIX_TRACE,sModule, sComponent,__VA_ARGS__)
#else
#define TLOG(...)
#define TMLOG(...)
#endif

#if !defined(NO_LOG) && defined(INFO_LOG)
/*! \brief Write an info log
 * \author mrTamburino
 * \param ...
 */
#define ILOG(...) _LOG_(_LOG_SEVERITY_PREFIX,__VA_ARGS__)
#define IMLOG(sModule, sComponent,...) _MLOG_(_LOG_SEVERITY_PREFIX,sModule, sComponent,__VA_ARGS__)
#else
#define ILOG(...)
#define IMLOG(...)
#endif

#if !defined(NO_LOG) && defined(VERBOSE_LOG)
/*! \brief Write an info log
 * \author mrTamburino
 * \param ...
 */
#define IILOG(...) _LOG_(_LOG_SEVERITY_PREFIX_INFO,__VA_ARGS__)
#define IIMLOG(sModule, sComponent,...) _MLOG_(_LOG_SEVERITY_PREFIX_INFO,sModule, sComponent,__VA_ARGS__)
#else
#define IILOG(...)
#define IIMLOG(...)
#endif

#define LOG(...) ILOG(__VA_ARGS__)
#define MLOG(sModule, sComponent,...) IMLOG(sModule, sComponent,__VA_ARGS__)

#endif /* STLOG_H_ */
