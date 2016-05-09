/*
 * test.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: ale
 */

//#include "../ground/application.hpp"
#include "../logs/log.h"
//#include "../exceptions/excps.hpp"
//#include "../datastructure/array.hpp"
//#include "../datastructure/darray.hpp"
//#include "../datastructure/lslink.hpp"
//#include "../datastructure/arrayindex.hpp"
//#include "../pattern/msgbroker.hpp"
//#include <time.h>

class test
{
public:

  test(){}
  ~test()
  {
    DLOG("Destroy test\n");
  }

  int k1,k2;
  char* a;

  inline bool operator==(const test& rhs){ return this->k1==rhs.k1 && this->k1==rhs.k1; }
  inline bool operator!=(const test& rhs){ return ! this->operator==(rhs); }
  inline bool operator< (const test& rhs){ return this->k1<rhs.k1 || (this->k1==rhs.k1 && this->k2<rhs.k2 ); }
  inline bool operator> (const test& rhs){return this->k1>rhs.k1 || (this->k1==rhs.k1 && this->k2>rhs.k2 );}
  inline bool operator<=(const test& rhs){return ! this->operator>(rhs);}
  inline bool operator>=(const test& rhs){return !this->operator<(rhs);}

  void print(void)
  {
    DLOG("k1:%d, k2:%d\n", k1,k2);
  }

};

/*
class MyApp: public composite::ground::ApplicationInterface
{
public:

  virtual void printBanner(void)
  {
    ILOG("------------------------------\n");
    ILOG("| Composite Test application |\n");
    ILOG("------------------------------\n\n");
  }

   void startUp(void)
   {
     DLOG("startUp\n");
     //RAISE_OOM;
   }

   UINT8 (cb1)(void* tmp)
   {
	 DLOG("cb1\n");
   }

   void run(void)
   {

	 srand ( time(NULL) );
	 //srand ( 50 );

     DLOG("run\n");
     int items = 100;


     DLOG("-------------------\n");
     DLOG("RUN test array\n");
     DLOG("-------------------\n");
     DLOG("\n");
     composite::dts::Array<test, UINT8> a;
     composite::dts::DynamicArray<test, UINT8> da;

     a.allocate(20);
     da.allocate(2);

     test item;


     for(int indx=0;indx<items;indx++ )
     {
    	item.k1 = rand() % 100 + 1;
    	item.k2 = rand() % 100 + 1;
    	item.a = NULL;
    	da.append( item );
     }

     for(int indx=0;indx<items;indx++ )
     {
       DLOG("indx:%d, value: %d, %d\n", indx, da[indx].k1, da[indx].k2);
     }

     DLOG("-------------------\n");
     DLOG("RUN test array index\n");
     DLOG("-------------------\n");
     DLOG("\n");
     composite::dts::QSortIndex<test,UINT8> qs;
     qs.setArray(&da);
     qs.sort();
     for(int indx=0;indx<items;indx++ )
     {
    	 DLOG("indx:%d, value: %d, %d\n", indx, da[indx].k1, da[indx].k2);
     }


     DLOG("-------------------\n");
	 DLOG("RUN test message broker\n");
	 DLOG("-------------------\n");
	 DLOG("\n");

	 composite::MessageBroker<test,void*> msg;
	 test tp;
	 tp.k1 = 1;
	 tp.k2 = 2;

	 composite::Callback<MyApp, void*> cb(this, &MyApp::cb1);

	 msg.addRecipient(&tp, &cb);

     /*
     DLOG("-------------------\n");
     DLOG("RUN test linked list\n");
     DLOG("-------------------\n");
     DLOG("\n");

     int* item;
     composite::dts::List<int> l;

     for(int indx=0;indx<items;indx++ )
      {
         item = l.append(indx);
         //*item = indx;
      }

     item = l.goToFirst();
     while(item)
     {
       DLOG("Data: %d\n", *item);
       item=l.next();
     }
/







   }

   void shutDown(void)
   {
     DLOG("shutDown\n");
   }
};

SET_AS_APP(MyApp);
*/
