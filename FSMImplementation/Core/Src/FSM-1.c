/*
 * FSM-1.c
 *
 *  Created on: Sep 18, 2024
 *      Author: ijk95
 */


#include "FSM-1.h"
#define f1 500
#define f2 250
#define f3 100
#define f4 50


const FSMState NextStateTable[8][2] =
{
		//Active Inactive
		{S2_Release, S1_Release},
		{S3_Release, S2_Release},
		{S4_Release, S2_Release},
		{S1_Release, S3_Release},

		};


void InitializeFSM(FSMType *FSM) //초기화
{
FSM->CurrentState = S1_Release;
FSM->StateCounter = 0;
}

FSMState NextStateFunction(FSMType *FSM)
{
	FSMState NextState = S1_Release;

	switch (FSM->CurrentState) {
	case S1_Release:
			NextState = S2_Release;
		break;
	case S2_Release:
			NextState = S3_Release;
		break;
	case S3_Release:
			NextState = S4_Release;
		break;
	case S4_Release:
			NextState = S1_Release;
		break;
}
return NextState;
}



void OutputFunction(FSMType *FSM)
{
	uint16_t max_counter = 0;
switch (FSM->CurrentState) {
case S1_Release:
	max_counter =f1;
break;
case S2_Release:
	max_counter =f2;
break;
case S3_Release:
	max_counter =f3;
break;
case S4_Release:
	max_counter =f4;
break;
}

      FSM->StateCounter++; // increase
HAL_Delay(0);
if (FSM->StateCounter >= max_counter) {
       HAL_GPIO_TogglePin(Grn_LED_GPIO_Port, Grn_LED_Pin); // LED 토글
       FSM->StateCounter = 0; // reset
   }

}
