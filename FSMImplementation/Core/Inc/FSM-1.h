
/*
* FSM-1.h
*
* Created on: Sep 18, 2024
* Author: ijk95
*/
#ifndef INC_FSM_1_H_
#define INC_FSM_1_H_
#include "main.h"
#define ACTIVE 0
#define INACTIVE 1
// Type Definitions
typedef enum {
S1_Press, S1_Release, S2_Press, S2_Release,
S3_Press, S3_Release, S4_Press, S4_Release
} FSMState;
typedef struct {
FSMState CurrentState; // Current state of the FSM
uint8_t CurrentInput; // Current input of the FSM
uint16_t StateCounter; // Used to establish output frequencies
} FSMType;
// Function Prototypes
void InitializeFSM(FSMType *FSM);
FSMState NextStateFunction(FSMType *FSM);
FSMState NextStateFunctionTable(FSMType *FSM);
FSMState NextStateFunctionPointers(FSMType *FSM);
void OutputFunction(FSMType *FSM);
typedef struct FSMTableStruct {
const FSMState CurrentState;
const struct FSMTableStruct *NextState[2]; // Next state of the FSM
} FSMTableType;
#endif /* INC_FSM_1_H_ */
