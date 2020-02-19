#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_StateM/testStateFncall_StateMemCBase.h>

#include <org/vishia/emC/StateM/StateFnCall_StateM_emC.h>



typedef struct MyStateM_T {

  StateMnTopFnCall_State_emC statesTop;


  StateMachineFnCall_StateM_emC statesRun; //:for the composite state Run, the nested ones

} MyStateM;


void doEntry_Idle(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn ) {
  StateMachineFnCall_StateM_emC* substmn = &stmn->substmn[thiz->ixInStmn]; 
  substmn->state = thiz;
  substmn->active = 1;
  substmn->ctEntry += 1;
}

void doExit_Idle(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn ) {
  stmn->substmn[thiz->ixInStmn].active = 0;
}

//StateFnCall_StateM_emC_T const* transIdleRun(int32 idEvent, ObjectJc* dataEvent);
//StateFnCall_StateM_emC_T const* transInit(int32 idEvent, ObjectJc* dataEvent);

extern CheckTrans_StateFnCall_StateM_emC transIdleRun;

extern CheckTrans_StateFnCall_StateM_emC transInit;


void doEntry_Run(){}

void doExit_Run(){}


void doEntry_Run1(){}

void doExit_Run1(){}


void doEntry_Run2(){}

void doExit_Run2(){}



const StateFnCall_StateM_emC stateInit = { "Init", 0, 0, null, null, null, transInit};

const StateFnCall_StateM_emC stateIdle = { "Idle", 0, 0, null, null, null, transIdleRun};

const StateFnCall_StateM_emC stateRun = { "Run", 0, 0, null, null, null, null};

const StateFnCall_StateM_emC stateRun1 = { "Run1", 1, 0, &stateRun, null, null, null};

const StateFnCall_StateM_emC stateRun2 = { "Run2", 1, 0, &stateRun, null, null, null};



static bool transInit(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32 idEvent, ObjectJc* dataEvent) {
  return true;
}


///Implementation of the transition between Idle and Run1 in Run,
//It checks the idEvent==1
static bool transIdleRun(
    struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
    int32 idEvent, ObjectJc* dataEvent
  ) {
  if(idEvent ==1) {
    doExit_Idle(&stateIdle, stmn);
    doEntry_Run(&stateRun, stmn);
    doEntry_Run1(&stateRun1, stmn);
    return true;
  }
  else {
    return false;
  }
}



static bool transRunIdle(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32 idEvent, ObjectJc* dataEvent
  ) {
  if(idEvent ==3) {
    doExit_Run();
    doEntry_Idle();
    return true;
  }
  else {
    return false;
  }
}


int evIdents[] = { 2, 1, 3};


void testStateFncall_StateMemCBase(){


  StateMachineFnCall_StateM_emC stm[2] = {0};

  init_StateFnCall_StateM_emC(&stm[0], &stateInit); 

  for(int ix = 0; ix < ARRAYLEN_emC(evIdents); ++ix) {

    step_StateFnCall_StateM_emC(&stm[0], evIdents[ix], null);
  
  }




}

