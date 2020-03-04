#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testStateFncall_StateMemCBase.h>
#include <org/vishia/emC/StateM/test_StateM/tplGen_StateFncall_StateMemCBase.h>
#include <emC/Test/testAssert.h>

extern_C ClassJc const reflection_MyStateM;
extern_C ClassJc const reflection_MyData;


#ifdef DEF_DEVELOPER_TEST
#include <stdio.h>
#define PRINTMSGLN(ID, MSG) printf("\n%d: %s", ID, MSG);
#define PRINTMSG(MSG) printf(MSG);
#else 
//yet same outputs as in developer test.
#include <stdio.h>
#define PRINTMSGLN(ID, MSG) printf("\n%d: %s", ID, MSG);
#define PRINTMSG(MSG) printf(MSG);
//#define PRINTMSGLN(ID, MSG)
//#define PRINTMSG(MSG)
#endif

void doEntryIdle(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-Idle, ");
}

void doEntryRun(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-Run, ");
}

void doEntryRunA(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-RunA, ");
}

void doEntryRunB(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-RunB, ");
}

void doEntryRunC(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-RunC, ");
}

void doExitIdle(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-Idle, ");
}

void doExitRun(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-Run, ");
}

void doExitRunA(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-RunA, ");
}

void doExitRunB(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-RunB, ");
}

void doExitRunC(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-RunC, ");
}

void doExitRunB11(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-RunB11, ");
}


void doExitRunB12(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-RunB12, ");
}


void doExitRunB21(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-RunB21, ");
}


void doExitRunB22(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("exit-RunB22, ");
}


void doEntryRunB11(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-RunB11, ");
}

void doEntryRunB12(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-RunB12, ");
}

void doEntryRunB21(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-RunB21, ");
}

void doEntryRunB22(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  PRINTMSG("entry-RunB22, ");
}








int evIdents[] = { -1 //note: first call from init should be done before active event processing
  , 1    
  , 2    
  , 3    
  , 5
  , 7
  , 1
  , 2
  , 4
  , 9
  , 7
  , 3
  , 5    
  };


StateFnCall_StateM_emC const* expectedStates[][4] = 
{ { &stateIdle, null      , null        , null }
, { &stateRun, &stateRunA, null        , null }
, { &stateRun, &stateRunB, &stateRunB11, &stateRunB21 }
, { &stateRun, &stateRunB, &stateRunB12, &stateRunB22 }
, { &stateIdle, null, null, null }
, { &stateIdle, null, null, null }
, { &stateRun, &stateRunA, null, null }
, { &stateRun, &stateRunB, &stateRunB11, &stateRunB21 }
, { &stateRun, &stateRunB, &stateRunB12, &stateRunB21 }
, { &stateIdle, null, null, null }
, { &stateRun, &stateRunB, &stateRunB12, &stateRunB21 }
, { &stateRun, &stateRunB, &stateRunB12, &stateRunB22 }
, { &stateIdle, null, null, null }
};


void testStateFncall_StateMemCBase(){
  TEST("testStateFncall_StateMemCBase");

  MyData data = INIZ_MyData(data, &reflection_MyData);

  StateMnTopFnCall_State_emC* stmnTop = &data.stateChart.statesTop;
  init_StateFnCall_StateM_emC(stmnTop, &stateInit); 
  int ix;
  for(ix = 0; ix < ARRAYLEN_emC(evIdents); ++ix) {

    step_StateFnCall_StateM_emC(stmnTop, evIdents[ix], null, &data.base.obj);
    EXPECTs_TRUE(expectedStates[ix][0] == getState_StateMnTopFnCall_StateM_emC(&data.stateChart.statesTop), "faulty top state");
    EXPECTs_TRUE(expectedStates[ix][1] == getState_StateMPartFnCall_StateM_emC(&data.stateChart.statesRun), "faulty Run state");
    EXPECTs_TRUE(expectedStates[ix][2] == getState_StateMPartFnCall_StateM_emC(&data.stateChart.statesRunParallel1), "faulty Run1 state");
    EXPECTs_TRUE(expectedStates[ix][3] == getState_StateMPartFnCall_StateM_emC(&data.stateChart.statesRunParallel2), "faulty Run2 state");


  }




}

