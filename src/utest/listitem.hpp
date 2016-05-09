/*
 * listitem.hpp
 *
 *  Created on: Jan 30, 2014
 *      Author: ale
 */

#ifndef LISTITEM_HPP_
#define LISTITEM_HPP_

#include "../types/types.h"

class test
{
public:

	test():k1(0),k2(0),a(NULL){}
	test(const test& test_IN)
	{
		k1=test_IN.k1;
		k2=test_IN.k2;
		a=NULL;
	}

	test(const int& test_IN)
        {
                k1=test_IN;
                k2=0;
                a=NULL;
        }
        
        UINT8 event1(const int* prova)
        {
            printf("prova\n");
            return 1;
        }

	int k1,k2;
	char* a;

	inline bool operator==(const test& rhs){ return this->k1==rhs.k1 && this->k2==rhs.k2; }
	inline bool operator!=(const test& rhs){ return ! this->operator==(rhs); }
	inline bool operator< (const test& rhs){ return this->k1<rhs.k1 || (this->k1==rhs.k1 && this->k2<rhs.k2 ); }
	inline bool operator> (const test& rhs){return this->k1>rhs.k1 || (this->k1==rhs.k1 && this->k2>rhs.k2 );}
	inline bool operator<=(const test& rhs){return ! this->operator>(rhs);}
	inline bool operator>=(const test& rhs){return !this->operator<(rhs);}

	inline bool operator==(const int& rhs){ return this->k1==rhs; }
        inline bool operator!=(const int& rhs){ return ! this->operator==(rhs); }
        inline bool operator< (const int& rhs){ return this->k1<rhs; }
        inline bool operator> (const int& rhs){return this->k1>rhs;}
        inline bool operator<=(const int& rhs){return ! this->operator>(rhs);}
        inline bool operator>=(const int& rhs){return !this->operator<(rhs);}

};


#endif /* LISTITEM_HPP_ */
