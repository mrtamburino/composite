/*
 * aitem.hpp
 *
 *  Created on: Apr 6, 2015
 *      Author: ale
 */

#ifndef SRC_UTEST_AITEM_HPP_
#define SRC_UTEST_AITEM_HPP_

#include "../logs/log.h"

class Item
{
public:

  Item():k1(0),k2(0),a(NULL){}
  Item(const int k1_IN, const int k2_IN):k1(k1_IN),k2(k2_IN),a(NULL){}
  Item(const Item& i):k1(i.k1),k2(i.k2),a(i.a){}
  ~Item()
  {
    DLOG("Destroy test\n");
  }

  int k1,k2;
  char* a;

  inline bool operator==(const Item& rhs){ return this->k1==rhs.k1 && this->k1==rhs.k1; }
  inline bool operator!=(const Item& rhs){ return ! this->operator==(rhs); }
  inline bool operator< (const Item& rhs){ return this->k1<rhs.k1 || (this->k1==rhs.k1 && this->k2<rhs.k2 ); }
  inline bool operator> (const Item& rhs){return this->k1>rhs.k1 || (this->k1==rhs.k1 && this->k2>rhs.k2 );}
  inline bool operator<=(const Item& rhs){return ! this->operator>(rhs);}
  inline bool operator>=(const Item& rhs){return !this->operator<(rhs);}

  void print(void)
  {
    DLOG("k1:%d, k2:%d\n", k1,k2);
  }

};


#endif /* SRC_UTEST_AITEM_HPP_ */
