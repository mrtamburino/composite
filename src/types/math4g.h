/*
 * math4g.h
 *
 *  Created on: May 29, 2013
 *      Author: ale
 */

#ifndef MATH4G_H_
#define MATH4G_H_

namespace mathlib
{

  typedef double real_t;

  typedef real_t* vector_t;
  
  typedef struct 
  {
      real_t x;
      real_t y;
      real_t z;
  } point_t;
  
  typedef point_t direction_t;

}


#endif /* MATH4G_H_ */
