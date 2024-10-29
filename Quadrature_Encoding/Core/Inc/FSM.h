/*
 * FSM.h
 *
 *  Created on: Oct 10, 2024
 *      Author: ijk95
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#define CLOCKWISE 0
#define COUNTERCW 1

typedef enum {
	S1, S2,
	S3, S4
} FSMState;

//state transition based on the currentState and Input
typedef struct{
	FSMState CurrentState;
	uint8_t CurrentInput;

}FSMType;
typedef struct FSMTableStruct {
const FSMState CurrentState;
const struct FSMTableStruct *NextState[2]; // Next state of the FSM
} FSMTableType;

void InitializeFSM(FSMType *FSM);
FSMState NextStateFunctionPointers(FSMType *FSM);
uint8_t OutputFunction(FSMType *FSM);





#endif /* INC_FSM_H_ */
