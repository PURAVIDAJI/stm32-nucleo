#include "FSM.h"

void InitializeFSM(FSMType *FSM,uint16_t ARR) //초기화
{
	FSM->CurrentState =UP;
	FSM->CCRx = 0;
	FSM-> ARR =ARR;

}

FSMState NextStateFunction(FSMType *FSM)
{
	FSMState NextState=FSM->CurrentState;

	if(FSM -> CurrentState ==UP){
		if(FSM->CCRx <FSM->ARR){
			FSM->CCRx +=1;

		}else{
			NextState =DW;
		}

	}else if(FSM -> CurrentState ==DW){
		if(FSM->CCRx >0){
			FSM ->CCRx -=1;
		}else{
			NextState =UP;
		}
	}

	FSM->CurrentState = NextState;
	return NextState;
}


