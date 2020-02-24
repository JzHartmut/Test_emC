#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_StateM/testStateFncall_StateMemCBase.h>

#include <org/vishia/emC/StateM/StateFnCall_StateM_emC.h>

#include <stdio.h>

#ifdef DEF_DEVELOPER_TEST
  #define PRINTMSG(ID, MSG) printf("%d: %s\n", ID, MSG);
#else 
  #define PRINTMSG(ID, MSG)
#endif

#ifdef DONOTUSE_REFLECTION_emC
  //Define the reflection as simple ClassJc without Field definition for type test only. 
  ClassJc const reflection_MyStateM = INIZ_ClassJc(reflection_MyStateM, "MyStateM");
  ClassJc const reflection_MyData = INIZ_ClassJc(reflection_MyData, "MyData");
#else
  //here generated Reflection may be included (*.refl-File from CHeader2Reflection)
  //The simple form is, defined class, without field definition.
  ClassJc const reflection_MyStateM = INIZ_ClassJc(reflection_MyStateM, "MyStateM");
  ClassJc const reflection_MyData = INIZ_ClassJc(reflection_MyData, "MyData");
#endif

typedef struct MyStateM_T {

  StateMnTopFnCall_State_emC statesTop;

  #define stmRun 1
  StateMachineFnCall_StateM_emC statesRun; //:for the composite state Run, the nested ones

  #define stmRunP1 2
  StateMachineFnCall_StateM_emC statesRunParallel1; //:for the composite state Run, the nested ones
  #define stmRunP2 3
  StateMachineFnCall_StateM_emC statesRunParallel2; //:for the composite state Run, the nested ones

} MyStateM;

/**A data class appropriate to the state chart of this class. */
typedef struct MyData_T {
  union { ObjectJc obj; } base;
  /**Any boolean*/
  int b1;

  /**contains the statechart. */
  MyStateM stateChart;
} MyData;


#define INIZ_MyData(OBJ, REFL) \
  { { INIZ_objReflId_ObjectJc((OBJ).stateChart, REFL, 0) } \
  , 1 \
  , { {{ INIZ_objReflId_ObjectJc((OBJ).stateChart, &reflection_MyStateM , 0)}} ,0} \
  }



void doEntry_Idle(struct StateFnCall_StateM_emC_T const* thiz 
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
  ) {
}

void doExit_Idle(struct StateFnCall_StateM_emC_T const* thiz 
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
  ) {
}

//StateFnCall_StateM_emC_T const* transIdleRun(int32 idEvent, ObjectJc* dataEvent);
//StateFnCall_StateM_emC_T const* transInit(int32 idEvent, ObjectJc* dataEvent);

extern CheckTrans_StateFnCall_StateM_emC transInit;
extern CheckTrans_StateFnCall_StateM_emC transIdle;

extern CheckTrans_StateFnCall_StateM_emC transRun;
extern CheckTrans_StateFnCall_StateM_emC transRunA;
extern CheckTrans_StateFnCall_StateM_emC transRunB;
extern CheckTrans_StateFnCall_StateM_emC transRunC;

extern CheckTrans_StateFnCall_StateM_emC transRunB1Init;
extern CheckTrans_StateFnCall_StateM_emC transRunB11;
extern CheckTrans_StateFnCall_StateM_emC transRunB12;
extern CheckTrans_StateFnCall_StateM_emC transRunB2Init;
extern CheckTrans_StateFnCall_StateM_emC transRunB21;
extern CheckTrans_StateFnCall_StateM_emC transRunB22;

extern DoEntry_StateFnCall_StateM_emC doEntryIdle;
extern DoEntry_StateFnCall_StateM_emC doEntryRun;
extern DoEntry_StateFnCall_StateM_emC doEntryRun11;
extern DoEntry_StateFnCall_StateM_emC doEntryRun12;
extern DoEntry_StateFnCall_StateM_emC doEntryRun21;
extern DoEntry_StateFnCall_StateM_emC doEntryRun22;

extern DoExit_StateFnCall_StateM_emC doExitIdle;
extern DoExit_StateFnCall_StateM_emC doExitRun;
extern DoExit_StateFnCall_StateM_emC doExitRun11;
extern DoExit_StateFnCall_StateM_emC doExitRun12;
extern DoExit_StateFnCall_StateM_emC doExitRun21;
extern DoExit_StateFnCall_StateM_emC doExitRun22;


/*@ All states @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

const StateFnCall_StateM_emC stateInit = { "Init", 0, 0, null, null, null, transInit};

const StateFnCall_StateM_emC stateIdle = { "Idle", 0, 0, null, null, null, transIdle};

const StateFnCall_StateM_emC stateRun = { "Run", 0, 0, null, doEntryRun, doExitRun, transRun};

const StateFnCall_StateM_emC stateRunA = { "RunA", stmRun, 0, &stateRun, null, null, transRunA};

const StateFnCall_StateM_emC stateRunB = { "RunB", stmRun, 2, &stateRun, null, null, transRunB};

const StateFnCall_StateM_emC stateRunC = { "RunC", stmRun, 0, &stateRun, null, null, transRunC};

//const StateFnCall_StateM_emC stateRunP2 = { "RunP2", stmRunP2, 0, &stateRun, doEntry_Run1, doExit_Run1, null};

const StateFnCall_StateM_emC stateRunB11 = { "RunB11", stmRunP1, 0, null, doEntryRun11, null, transRunB11};

const StateFnCall_StateM_emC stateRunB12 = { "RunB12", stmRunP1, 0, null, doEntryRun12, doExitRun21, transRunB12};

const StateFnCall_StateM_emC stateRunB21 = { "RunB21", stmRunP2, 0, null, doEntryRun21, null, transRunB21};

const StateFnCall_StateM_emC stateRunB22 = { "RunB22", stmRunP2, 0, null, doEntryRun22, null, transRunB22};


/*@ Implementation of all entry, exit, trans @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


void doEntryIdle(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {

}

void doEntryRun(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
}

void doExitRun(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
}

void doExitRun21(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
}


void doEntryRun11(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
}

void doEntryRun12(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
}

void doEntryRun21(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
}

void doEntryRun22(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
}

void doExit_Run1(struct StateFnCall_StateM_emC_T const* thiz
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
}






static StateFnCall_StateM_emC const* transInit(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass) {
  int32 idEvent1 = *idEvent;
  doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
  //
  //The trans action ....
  PRINTMSG(*idEvent, "Init->Idle");
  //
  doEntry_StateMFnCall_emC(&stateIdle, stmn, idEvent1, dataEvent, dataClass);
  return &stateIdle;
}


static StateFnCall_StateM_emC const* transIdle(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  int32 idEvent1 = *idEvent;
  if(*idEvent ==1) {
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(*idEvent, "Idle->RunA");
    //
    doEntry_StateMFnCall_emC(&stateRunA, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunA;
  }
  else {
    return null;
  }
}


static StateFnCall_StateM_emC const* transRun(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==9) {
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(*idEvent, "Run->Idle");
    //
    doEntry_StateMFnCall_emC(&stateIdle, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateIdle;
  }
  else {
    return null;
  }
}



static StateFnCall_StateM_emC const* transRunA(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==2) {
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(*idEvent, "RunA->RunB11, RunB21");
    //
    doEntry_StateMFnCall_emC(&stateRunB, stmn, idEvent1, dataEvent, dataClass);
    doEntry_StateMFnCall_emC(&stateRunB11, stmn, idEvent1, dataEvent, dataClass); //determined parallel state
    doEntry_StateMFnCall_emC(&stateRunB21, stmn, idEvent1, dataEvent, dataClass); //determined parallel state
    *idEvent = -1;
    return &stateRunB; //to execute its trans action as RunToComplete
  }
  else {
    return null;
  }
}


static StateFnCall_StateM_emC const* transRunB(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  int32 idEvent1 = *idEvent;
  if(false) {
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(*idEvent, "RunB->???");
    //
    return &stateIdle;
  }
  else {
    return null;
  }
}


static StateFnCall_StateM_emC const* transRunC(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  if(ASSERTs_emC(instanceof_ObjectJc(dataClass, &reflection_MyData), "faulty", 0, 0)) {
    MyData* data = C_CAST(MyData*, dataClass);  //It is an downcast for C data without pointer adjustment.
    int32 idEvent1 = *idEvent;
    if(data->b1) {
      doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
      doExit_StateMFnCall_emC(&stateRun, stmn, idEvent1, dataEvent, dataClass);
      //
      //The trans action ....
      PRINTMSG(*idEvent, "RunC->Idle");
      //
      doEntry_StateMFnCall_emC(&stateIdle, stmn, idEvent1, dataEvent, dataClass);
      return &stateIdle;
    }
    else {
      return null;
    }
  } else { return null; } //The non-asserted case.
}


static StateFnCall_StateM_emC const* transRunB11(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==3) {
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(*idEvent, "RunB11->RunB12");
    //
    doEntry_StateMFnCall_emC(&stateRunB12, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunB12;
  }
  else {
    return null;
  }
}


static StateFnCall_StateM_emC const* transRunB12(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  int32 idEvent1 = *idEvent;
  if(  idEvent1 ==5   //join transition, checks whether the other parallel is in the requested state.
    && stmn->substmn[stateRunB22.ixInStmn].state == &stateRunB22) {
    //It is necessary to exit all parallel and the container state here.
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    doExit_StateMFnCall_emC(&stateRunB22, stmn, idEvent1, dataEvent, dataClass);
    doExit_StateMFnCall_emC(&stateRunB, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(*idEvent, "RunB12, RunB22->RunC");
    //

    doEntry_StateMFnCall_emC(&stateRunC, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunC;
  }
  else {
    return null;
  }
}

static StateFnCall_StateM_emC const* transRunB21(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==3) {
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(*idEvent, "RunB21->RunB22");
    //
    doEntry_StateMFnCall_emC(&stateRunB22, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunB22;
  }
  else {
    return null;
  }
}

static StateFnCall_StateM_emC const* transRunB22(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* dataClass
) {
  int32 idEvent1 = *idEvent;
  if(  idEvent1 ==5   //join transition, checks whether the other parallel is in the requested state.
    && stmn->substmn[stateRunB12.ixInStmn].state == &stateRunB12) {
    //It is necessary to exit all parallel and the container state here.
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    doExit_StateMFnCall_emC(&stateRunB12, stmn, idEvent1, dataEvent, dataClass);
    doExit_StateMFnCall_emC(&stateRunB, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(*idEvent, "RunB12, RunB22->RunC");
    //
    doEntry_StateMFnCall_emC(&stateRunC, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunC;
  }
  else {
    return null;
  }
}






int evIdents[] = { -1 //note: first call from init should be done before active event processing
  , 1    
  , 2    
  , 3    
  , 5    
  };


void testStateFncall_StateMemCBase(){

  MyData data = INIZ_MyData(data, &reflection_MyData);

  StateMnTopFnCall_State_emC* stmnTop = &data.stateChart.statesTop;
  init_StateFnCall_StateM_emC(stmnTop, &stateInit); 
  int ix;
  for(ix = 0; ix < ARRAYLEN_emC(evIdents); ++ix) {

    step_StateFnCall_StateM_emC(stmnTop, evIdents[ix], null, &data.base.obj);
  
  }




}

