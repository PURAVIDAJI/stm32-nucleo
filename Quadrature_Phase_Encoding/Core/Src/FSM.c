#include "FSM.h"

void InitializeFSM(FSMType *fsm) //초기화
{
	fsm->CurrentState =S1;
	fsm->Direction =CW;
	fsm->CurrentInput =0;

}


Direction NextDirectionFunction(FSMType *fsm)
{

	Direction nextDirection =fsm->Direction;
	FSMState nextState = fsm->CurrentState;
switch (fsm->CurrentState)
{
	case S1:
		if (fsm->CurrentInput == 0b01){
			nextDirection = CW;
			nextState =S2;
		}
		else if(fsm->CurrentInput == 0b10){
			nextDirection = CCW;
		    nextState =S4;
		}
		break;

	case S2:
		if (fsm->CurrentInput == 0b11){
			nextDirection = CW;
			nextState =S3;
		}
		else if(fsm->CurrentInput == 0b00){
			nextDirection = CCW;
		    nextState =S1;
		}
		break;
	case S3:
		if (fsm->CurrentInput == 0b10){
			nextDirection = CW;
			nextState =S4;
		}
		else if(fsm->CurrentInput == 0b01){
			nextDirection = CCW;
		    nextState =S1;
		}
		break;
	case S4:
		if (fsm->CurrentInput == 0b00){
			nextDirection = CW;
			nextState =S1;
		}
		else if(fsm->CurrentInput == 0b11){
			nextDirection = CCW;
		    nextState =S3;
		}
		break;

	}
	fsm->CurrentState = nextState;
	fsm->Direction = nextDirection;
	return nextDirection;
	}



