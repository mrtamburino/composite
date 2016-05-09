/*
 * cnslog.h
 *
 *  Created on: Jun 19, 2011
 *      Author: ale
 */

#ifndef CNSLOG_H_
#define CNSLOG_H_


#include "stdio.h"

/*!
 * \brief LOG_PRINT è una macro richiamata dal file log.h e che
 * viene utilizzate per scrivere su console
 *
 * Il fil log.h non implementa LOG_PRINT ma ha una serie di inclusioni
 * condizionate che importano il file che implementa LOG_PRINT. In questo
 * modo posso pilotare la pilotare il terget del log definendo opportune
 * macro.
*/
#define LOG_PRINT(...) printf(__VA_ARGS__)

#endif /* CNSLOG_H_ */
