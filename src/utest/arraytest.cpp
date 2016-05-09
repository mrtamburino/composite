/*
 * arrayytest.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: ale
 */

#include "../logs/log.h"
#include "../exceptions/excps.hpp"
#include "../datastructure/buffer.hpp"
#include "../datastructure/dal.hpp"
#include "aitem.hpp"
#include <time.h>

int main(void)
{
  
  
    composite::dts::Buffer<int> aint;
     aint.allocate(4);
     aint.append (1);
     aint.append (2);
     aint.append (3);
     aint.append (4);
     
     aint.clear ();
     
     Item t;
     t.k1=1;
     t.k2=2;

     
     composite::dts::Buffer<Item*> astar;

     Item* i1 = new Item(1,1);
     Item* i2 = new Item(2,2);
     Item* i3 = new Item(3,3);
     Item* i4 = new Item(4,4);
     
     astar.allocate(4);
     astar.append (i1);
     astar.append (i2);
     astar.append (i3);
     astar.append (i4);
     
     astar[2]->print ();
     
     astar.clear ();
     
     i3->print ();

}
