/*
 * lltest.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: ale
 */


#include <time.h>

#include "../datastructure/event.hpp"
#include "listitem.hpp"
#include <new>


class test2
{
  public:
  UINT8 event2(const int* prova)
  {
    printf("prova b\n");
    return 0;
  }
  
  UINT8 eventVoid(void)
  {
    printf("prova c\n");
    return 1;
  }
        

};

int main(void)
{

  test* t = new test();
  test2* t2 = new test2();
  
  
  t->k1 = rand() % 100 + 1;
  t->k2 = rand() % 100 + 1;
  t->a = NULL;
  
  composite::Event<int> event;
  event.subscribe (t, &test::event1);
  event.subscribe (t2, &test2::event2);
  
  int p = 1;
  event.dispatch (&p);
  
  

  composite::Event<void> event2;
  event2.subscribe (t2, &test2::eventVoid );
  event2.dispatch ();

  


  
  /*
     DLOG("-------------------\n");
     DLOG("RUN test linked list\n");
     DLOG("-------------------\n");
     DLOG("\n");

     int items = 100;

     DLOG("Test with pointer type\n");

     composite::dts::List<test*> lp;
     test* itemp;
     for(int indx=0;indx<items;indx++ )
     {
    	 itemp = new test();
    	 itemp->k1 = rand() % 100 + 1;
    	 itemp->k2 = rand() % 100 + 1;
    	 itemp->a = NULL;

    	 DLOG("add: %d, %d\n", itemp->k1, itemp->k2 );
    	 lp.append(itemp);
     }

     DLOG("Items: %d\n", lp._uiLength);

     composite::dts::ListItemRef<test*> refp(&lp);

     test* datap = NULL;
     while( (datap = refp.getDataAndMoveForward()) )
     {
       DLOG("Data: %d, %d\n", datap->k1, datap->k2);
     }



     DLOG("Test with object type\n");

     test* item;

     composite::dts::List<test> l;

     for(int indx=0;indx<items;indx++ )
      {

    	 item = new (l.append()) test();
    	 //test* a;
    	 //new (a) test;

    	 item->k1 = rand() % 100 + 1;
    	 item->k2 = rand() % 100 + 1;
    	 item->a = NULL;
    	 DLOG("add: %d, %d\n", item->k1, item->k2 );

      }

     DLOG("Items: %d\n", l._uiLength);

     composite::dts::ListItemRef<test> ref(&l);
     test* data = NULL;
     while( (data = ref.getDataAndMoveForward()) )
     {
       DLOG("Data: %d, %d\n", data->k1, data->k2);
     }
     */

}
