/*
 * types.h
 *
 *  Created on: Jun 19, 2011
 *      Author: ale
 */

#ifndef TYPES_H_
#define TYPES_H_

//! \breif One byte unsigned int
typedef unsigned char     UINT8;
typedef char               INT8;

typedef unsigned long int ULINT;

#ifdef _LP64

#warning "64 bit architecture!!!"
typedef unsigned short int UINT16;
typedef unsigned int       UINT32;
typedef ULINT                UINT64;
typedef UINT64             PTRINT; // intero della dimensione di un puntatore
typedef short int          INT16;
typedef int                INT32;
typedef long int           INT64;
#else
#warning "32 bit architecture!!!"
typedef unsigned short int UINT16;
typedef unsigned int       UINT32;
typedef UINT32             PTRINT; // intero della dimensione di un puntatore
typedef short int          INT16;
typedef int                INT32;
#endif

//! \brief resource handler
typedef UINT16 HND;

typedef UINT8 BOOLEAN;
#define TRUE 1
#define FALSE 0

#endif /* TYPES_H_ */
