/*
 * arrayytest.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: ale
 */

#include "../logs/log.h"
#include "../exceptions/excps.hpp"
#include <time.h>
#include "listitem.hpp"
#include <new>

#include "../datastructure/dbuffer.hpp"
#include "../datastructure/qindex.hpp"

int main(void)
{

     DLOG("-------------------\n");
     DLOG("RUN test dynamic array\n");
     DLOG("-------------------\n");
     DLOG("\n");

     int items = 10;
     test* item;

     DLOG("-------------------\n");
     DLOG("Test item pointer\n");
     DLOG("-------------------\n");
     DLOG("\n");


     composite::dts::DynamicArray<test*, composite::dts::small_array_t> dap;
     dap.allocate(2);

     for(int indx=0;indx<items;indx++ )
     {

       item = new test();
       item->k1 = rand() % 100 + 1;
       item->k2 = rand() % 100 + 1;
       item->a = NULL;

       dap.append(item);

     }

     composite::dts::QSortIndex<test*, composite::dts::small_array_t> qsp;
     qsp.setArray(&dap);
     qsp.sort();

     for(int indx=0;indx<items;indx++ )
     {
       DLOG("item: %d, %d\n", dap[indx]->k1, dap[indx]->k1);
     }



     DLOG("-------------------\n");
     DLOG("Test item object\n");
     DLOG("-------------------\n");
     DLOG("\n");


     composite::dts::DynamicArray<test, composite::dts::small_array_t> da;

     da.allocate(2);

     for(int indx=0;indx<items;indx++ )
     {

       item = new (da.append()) test();
       //test* a;
       //new (a) test;

       item->k1 = rand() % 100 + 1;
       item->k2 = rand() % 100 + 1;
       item->a = NULL;

     }

     composite::dts::QSortIndex<test, composite::dts::small_array_t>* qs;
     qs = new composite::dts::QSortIndex<test, composite::dts::small_array_t>();

     qs->setArray(&da);

     qs->sort();

     for(int indx=0;indx<items;indx++ )
     {
       DLOG("item: %d, %d\n", da[indx].k1, da[indx].k1);
     }


}
