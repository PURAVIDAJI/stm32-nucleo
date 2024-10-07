/*
 * MyMulti16.c
 *
 *  Created on: Sep 2, 2024
 *      Author: ijk95
 */


#include "MyMult16.h"

uint16_t multiplyTwoUnsignedTypes(uint16_t n1,uint16_t n2)
   {
	    uint32_t res=0;
		while(n2>0){
			if(n2&1){//bit mask for the 1st bit of n2

				res+=(uint32_t)n1;
			}
			n1<<=1;
			n2>>=1;

		}
		 return res;

   }
