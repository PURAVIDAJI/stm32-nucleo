#ifndef FSM_H
#define FSM_H

#include "main.h"


typedef enum {
S1, //00
S2, //01
S3, //11
S4  //10
} FSMState;
typedef enum {
    CW = 0,
    CCW = 1
} Direction;
typedef struct {

	FSMState CurrentState;  // current state
	uint8_t CurrentInput;
	Direction Direction;

} FSMType;
// Function Prototypes
void InitializeFSM(FSMType *fsm);

Direction NextDirectionFunction(FSMType *fsm);

#endif  /* FSM_H */



