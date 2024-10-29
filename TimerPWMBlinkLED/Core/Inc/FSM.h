#ifndef FSM_H
#define FSM_H

#include "main.h"


typedef enum {
UP, //증가
DW//감소 상태
} FSMState;
typedef struct {

	FSMState CurrentState;  // current state
	    uint16_t CCRx;          // duty cycle value
	    uint16_t ARR;           // 듀티 사이클 최대값 (Auto-Reload 값)

} FSMType;
// Function Prototypes
void InitializeFSM(FSMType *FSM, uint16_t ARR);
FSMState NextStateFunction(FSMType *FSM);

#endif  /* FSM_H */
