/*
 * swapFunction.c
 *
 *  Created on: Sep 2, 2024
 *      Author: ijk95
 */

#include "swapfunction.h"

void swap(uint32_t *n1,uint32_t *n2)
   {
		uint32_t temp;
		temp=*n1;
		*n1 =*n2;
		*n2 = temp;
   }
