/*
 * index.cpp
 *
 *  Created on: Jan 31, 2014
 *      Author: ale
 */


#include "../logs/log.h"
#include "../exceptions/excps.hpp"
#include "../pattern/eventbkr.hpp"
#include "../pattern/callback.hpp"
#include "listitem.hpp"
#include <time.h>
#include <new>

class EventMgr
{
public:

	EventMgr(){}

	UINT8 call_1_OK(const int* data)
	{
		DLOG("Event ok: %d\n", *data);
		return 1;
	}

	UINT8 call_2_OK(const int* data)
	{
		DLOG("Event ok: 2\n");
		return 1;
	}

	UINT8 call_3_OK(const int* data)
	{
		DLOG("Event ok: 3\n");
		return 1;
	}

	UINT8 call_4_OK(const int* data)
	{
		DLOG("Event ok: 4\n");
		return 0;
	}

	UINT8 call_5_OK(const int* data)
	{
		DLOG("Event ok: 5\n");
		return 1;
	}

};

int main(void)
{

     DLOG("-------------------\n");
     DLOG("RUN test events\n");
     DLOG("-------------------\n");
     DLOG("\n");

     int items = 20;
     test item;

     composite::EventBroker<int,int> eb;

     EventMgr em;

     DLOG("\n");

     srand(time(NULL));

     int eventType;

     eventType = 1;

     composite::Callback<EventMgr,int> cb1(&em, &EventMgr::call_1_OK);


     for(int indx=0;indx<items;indx++ )
     {
    	 eventType = rand() % 10 + 1;
    	 DLOG("Subscribe %d\n", eventType);
    	 eb.subscribe(eventType, &cb1);

     }

     //eb.listSuscriber();

     DLOG("Dispatch...\n");

     for(int indx=0;indx<items;indx++ )
	 {
	   eventType = rand() % 10 + 1;
	   DLOG("Dispatch %d\n", eventType);
	   eb.notify(eventType, &eventType);
	  }

}


