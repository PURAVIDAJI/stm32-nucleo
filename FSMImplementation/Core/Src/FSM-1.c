
/*
* FSM-1.c
*
* Created on: Sep 18, 2024
* Author: ijk95
*/
#include "FSM-1.h"
#define f1 500
#define f2 250
#define f3 100
#define f4 50
const FSMState NextStateTable[8][2] =
{
//Active Inactive
{S1_Release, S1_Press},
{S1_Release, S2_Press},
{S2_Release, S2_Press},
{S2_Release, S3_Press},
{S3_Release, S3_Press},
{S3_Release, S4_Press},
{S4_Release, S4_Press},
{S4_Release, S1_Press}
};
#define S1_PRESS &FSMTable[0]
#define S1_RELEASE &FSMTable[1]
#define S2_PRESS &FSMTable[2]
#define S2_RELEASE &FSMTable[3]
#define S3_PRESS &FSMTable[4]
#define S3_RELEASE &FSMTable[5]
#define S4_PRESS &FSMTable[6]
#define S4_RELEASE &FSMTable[7]
const FSMTableType FSMTable[8] = {
		// Next State
        // Current State Active Inactive
{S1_Press, {S1_RELEASE, S1_PRESS}},
//active 0-> release FSMTable[1], inactive 1->FSMTable[0]
{S1_Release, {S1_RELEASE, S2_PRESS}},
{S2_Press, {S2_RELEASE, S2_PRESS}},
{S2_Release, {S2_RELEASE, S3_PRESS}},
{S3_Press, {S3_RELEASE, S3_PRESS}},
{S3_Release, {S3_RELEASE, S4_PRESS}},
{S4_Press, {S4_RELEASE, S4_PRESS}},
{S4_Release, {S4_RELEASE, S1_PRESS}}
};
void InitializeFSM(FSMType *FSM) //초기화
{
FSM->CurrentState = S1_Press;
FSM->StateCounter = 0;
}
FSMState NextStateFunctionTable(FSMType *FSM)
{
FSMState NextState = S1_Press;
uint8_t TableIndex = (uint8_t) FSM-> CurrentState;
uint8_t NextStateIndex = FSM->CurrentInput;
NextState= NextStateTable[TableIndex][NextStateIndex];
return NextState;
}
FSMState NextStateFunctionPointers(FSMType *FSM)
{
FSMState NextState = S1_Press;
uint8_t TableIndex = (uint8_t)FSM->CurrentState;
uint8_t NextStateIndex = FSM ->CurrentInput;
FSMTableType *NextStatePointer;
NextStatePointer=FSMTable[TableIndex].NextState[NextStateIndex];
NextState=NextStatePointer->CurrentState;
return NextState;
}
FSMState NextStateFunction(FSMType *FSM)
{
FSMState NextState = S1_Press;
switch (FSM->CurrentState)
{
	case S1_Press:
		if (FSM->CurrentInput ==ACTIVE){
			NextState = S1_Release;
		}
		else{
			NextState =S1_Press;
		}
		break;
	case S1_Release:
		if (FSM->CurrentInput ==ACTIVE){
			NextState = S1_Release;
		}
		else{
			NextState =S2_Press;
		}
		break;
	case S2_Press:
		if (FSM->CurrentInput ==ACTIVE){
			NextState = S2_Release;
		}
		else{
			NextState =S2_Press;
		}
		break;
	case S2_Release:
		if (FSM->CurrentInput ==ACTIVE){
			NextState = S2_Release;
		}
		else{
			NextState =S3_Press;
		}
		break;
	case S3_Press:
		if (FSM->CurrentInput ==ACTIVE){
			NextState = S3_Release;
		}
		else{
			NextState =S3_Press;
		}
		break;
	case S3_Release:
		if (FSM->CurrentInput ==ACTIVE){
			NextState = S3_Release;
		}
		else{
			NextState =S4_Press;
		}
		break;
	case S4_Press:
		if (FSM->CurrentInput ==ACTIVE){
			NextState = S4_Release;
		}
		else{
			NextState =S4_Press;
		}
		break;
	case S4_Release:
		if (FSM->CurrentInput ==ACTIVE){
			NextState = S4_Release;
		}
		else{
			NextState =S1_Press;
		}
		break;
	}
	return NextState;
	}

void OutputFunction(FSMType *FSM)
{
uint16_t max_counter = 0;

switch (FSM->CurrentState) {
case S1_Press:
max_counter =f1; //1Hz
break;
case S1_Release:
max_counter =f1;
break;
case S2_Press:
max_counter =f2;
break;
case S2_Release:
max_counter =f2;
break;
case S3_Press:
max_counter =f3;
break;
case S3_Release:
max_counter =f3;
break;
case S4_Press:
max_counter =f4;
break;
case S4_Release:
max_counter =f4;
break;
}
FSM->StateCounter++; // increase
if (FSM->StateCounter >= max_counter) {
HAL_GPIO_TogglePin(Grn_LED_GPIO_Port, Grn_LED_Pin); // LED 토글
FSM->StateCounter = 0; // reset
}
}
