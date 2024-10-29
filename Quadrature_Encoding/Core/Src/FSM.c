/*
 * FSM.c
 *
 *  Created on: Oct 10, 2024
 *      Author: ijk95
 */
#include "FSM.h"

const FSMTableType FSMTable[4] = {
//currentState,{clockwise, countercw}
{S1, {&FSMTable[1], &FSMTable[3]}},
{S2, {&FSMTable[2], &FSMTable[0]}},
{S3, {&FSMTable[3], &FSMTable[1]}},
{S4, {&FSMTable[0], &FSMTable[2]}},

};

void InitializeFSM(FSMType *FSM){
FSM->CurrentState = S1;

}
FSMState NextStateFunctionPointers(FSMType *FSM)
{
FSMState NextState = S1;
uint8_t TableIndex = (uint8_t)FSM->CurrentState;
uint8_t NextStateIndex = FSM ->CurrentInput;

//const 할당
const FSMTableType *NextStatePointer;

NextStatePointer=FSMTable[TableIndex].NextState[NextStateIndex];
NextState=NextStatePointer->CurrentState;
return NextState;
}


uint8_t OutputFunction(FSMType *FSM)
{
	uint8_t output = 0;

switch (FSM->CurrentState) {
case S1:
	output=0b00;

break;
case S2:
	output=0b01;
break;
case S3:
	output=0b11;
break;
case S4:
	output=0b10;
break;

}

return output;

}
