/*
 * index.cpp
 *
 *  Created on: Jan 31, 2014
 *      Author: ale
 */


#include "../logs/log.h"
#include "../exceptions/excps.hpp"
#include <time.h>
#include "../datastructure/qindex.hpp"
#include "../datastructure/arrayindex.hpp"
#include "../datastructure/dbuffer.hpp"
#include "listitem.hpp"
//#include <new>


int main(void)
{

     DLOG("-------------------\n");
     DLOG("RUN test array\n");
     DLOG("-------------------\n");
     DLOG("\n");

     int items = 100;
     test item;

     composite::dts::DynamicArray<test, composite::dts::small_array_t> da;
     da.allocate(10);

     DLOG("-------------------\n");
     DLOG("Test simple inser\n");
     DLOG("-------------------\n");
     DLOG("\n");

     composite::dts::AccessIndex<test, composite::dts::small_array_t> ai(&da);

     for(int indx=0;indx<(items>>1);indx++ )
     {

        item.k1= rand() % 100 + 1;
        item.k2= rand() % 100 + 1;
        item.a = NULL;
        DLOG("insert %d: %d, %d\n", indx, item.k1, item.k2);

        ai.insert(item, TRUE);
/*
        DLOG("\n");

        for(int indx2=0;indx2<da._uiLength;indx2++ )
        {

                DLOG("\titem %d: %d, %d\n", indx2, da[indx2].k1, da[indx2].k2);
        }
        DLOG("\n");
*/
     }

     DLOG("-------------------\n");
     DLOG("Test K inser\n");
     DLOG("-------------------\n");
     DLOG("\n");

     composite::dts::AccessIndex<test, composite::dts::small_array_t, int> ki(&da);

     for(int indx=0;indx<(items>>1);indx++ )
     {

       item.k1= rand() % 100 + 1;
       item.k2= rand() % 100 + 1;
       item.a = NULL;
       DLOG("insert %d: %d, %d\n", indx, item.k1, item.k2);

       ki.insert(item.k1, TRUE);

/*
       DLOG("\n");

       for(int indx2=0;indx2<da._uiLength;indx2++ )
       {

               DLOG("\titem %d: %d, %d\n", indx2, da[indx2].k1, da[indx2].k2);
       }
       DLOG("\n");
*/
     }

     DLOG("\n");

     for(int indx=0;indx<da._uiLength;indx++ )
     {

             DLOG("\titem %d: %d, %d\n", indx, da[indx].k1, da[indx].k2);
     }
     DLOG("\n");

     DLOG("-------------------\n");
     DLOG("Test Q inser\n");
     DLOG("-------------------\n");
     DLOG("\n");

     composite::dts::DynamicArray<test, composite::dts::small_array_t> da2;
     da2.allocate(10);

     for(int indx=0;indx<(items>>1);indx++ )
     {

         item.k1= rand() % 100 + 1;
         item.k2= rand() % 100 + 1;
         item.a = NULL;
         DLOG("insert %d: %d, %d\n", indx, item.k1, item.k2);

         da2.append(item);
     }

     composite::dts::QSortIndex<test, composite::dts::small_array_t> qsi(&da2);
     qsi.sort();

     DLOG("\n");

     for(int indx=0;indx<da._uiLength;indx++ )
     {

             DLOG("\titem %d: %d, %d\n", indx, da[indx].k1, da[indx].k2);
     }
     DLOG("\n");


}


