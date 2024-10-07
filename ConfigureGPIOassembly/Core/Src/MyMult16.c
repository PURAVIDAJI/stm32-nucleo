/*
 * MyMult16.c
 *
 *  Created on: Sep 16, 2024
 *      Author: ijk95
 */


#include "MyMult16.h"

uint32_t multiplyTwoUnsignedTypes(uint16_t n1,uint16_t n2)
   {
	    uint32_t res=0;
		for(uint16_t i = 0; i < 16; i++){
			if(n2&(1<<i)){//bit mask for the each bit of n2

				res+=((uint32_t)n1<<i);
			}
		}
		 return res;

   }
