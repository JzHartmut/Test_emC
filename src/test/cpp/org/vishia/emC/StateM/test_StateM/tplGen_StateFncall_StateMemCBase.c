#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testStateFncall_StateMemCBase.h>
#include <org/vishia/emC/StateM/test_StateM/tplGen_StateFncall_StateMemCBase.h>


#include <stdio.h>

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



#ifdef DONOTUSE_REFLECTION_emC
  //Define the reflection as simple ClassJc without Field definition for type test only. 
  ClassJc const reflection_MyStateM = INIZ_ClassJc(reflection_MyStateM, "MyStateM");
  ClassJc const reflection_MyData = INIZ_ClassJc(reflection_MyData, "MyData");
#else
  //here generated Reflection may be included (*.refl-File from CHeader2Reflection)
  //The simple form is, defined class, without field definition.
  ClassJc const refl_MyStateM = INIZ_ClassJc(refl_MyStateM, "MyStateM");
  ClassJc const refl_MyTestStatechartData = INIZ_ClassJc(refl_MyTestStatechartData, "MyData");
#endif




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

//Note: do not declare extern or extern_C because it is static, gcc error

CheckTrans_StateFnCall_StateM_emC transInit;
CheckTrans_StateFnCall_StateM_emC transIdle;

CheckTrans_StateFnCall_StateM_emC transRun;
CheckTrans_StateFnCall_StateM_emC transRunA;
CheckTrans_StateFnCall_StateM_emC transRunB;
CheckTrans_StateFnCall_StateM_emC transRunC;

CheckTrans_StateFnCall_StateM_emC transRunB1Init;
CheckTrans_StateFnCall_StateM_emC transRunB11;
CheckTrans_StateFnCall_StateM_emC transRunB12;
CheckTrans_StateFnCall_StateM_emC transRunB2Init;
CheckTrans_StateFnCall_StateM_emC transRunB21;
CheckTrans_StateFnCall_StateM_emC transRunB22;


/*@ All states @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

const StateFnCall_StateM_emC stateInit =   { "Init", 0x0, ixSTM_Top, 0, 0, null, null, null, transInit};

const StateFnCall_StateM_emC stateIdle =   { "Idle", 0x1, ixSTM_Top, 0, 0, null, doEntryIdle, doExitIdle, transIdle};

const StateFnCall_StateM_emC stateRun =    { "Run",  0x0, ixSTM_Top, ixSTM_Run, 0, null, doEntryRun, doExitRun, transRun};

const StateFnCall_StateM_emC stateRunA =   { "RunA", 0x3, ixSTM_Run, 0, 0, &stateRun, doEntryRunA, doExitRunA, transRunA};

const StateFnCall_StateM_emC stateRunB =   { "RunB", 0x0, ixSTM_Run, ixSTM_RunP1, 2, &stateRun, doEntryRunB, doExitRunB, transRunB};

const StateFnCall_StateM_emC stateRunC =   { "RunC", 0x4, ixSTM_Run, 0, 0, &stateRun, doEntryRunC, doExitRunC, transRunC};

//const StateFnCall_StateM_emC stateRunP2 = { "RunP2", ixSTM_RunP2, 0, &stateRun, doEntry_Run1, doExit_Run1, null};

const StateFnCall_StateM_emC stateRunB11 = { "RunB11", 0x010, ixSTM_RunP1, 0, 0, null, doEntryRunB11, doExitRunB11, transRunB11};

const StateFnCall_StateM_emC stateRunB12 = { "RunB12", 0x020, ixSTM_RunP1, 0, 0, null, doEntryRunB12, doExitRunB12, transRunB12};

const StateFnCall_StateM_emC stateRunB21 = { "RunB21", 0x100, ixSTM_RunP2, 0, 0, null, doEntryRunB21, doExitRunB21, transRunB21};

const StateFnCall_StateM_emC stateRunB22 = { "RunB22", 0x200, ixSTM_RunP2, 0, 0, null, doEntryRunB22, doExitRunB22, transRunB22};


/*@ Implementation of all entry, exit, trans @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/





//Note: cannot be declared as static, gcc error (?) it should be only visible in this module!
//Prototypedef: CheckTrans_StateFnCall_StateM_emC
StateFnCall_StateM_emC const* transInit(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass) {
  int32 idEvent1 = *idEvent;
  PRINTMSGLN(*idEvent, " ");
  doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
  //
  //The trans action ....
  PRINTMSG(": Init->Idle: ");
  //
  doEntry_StateMFnCall_emC(&stateIdle, 0, stmn, idEvent1, dataEvent, dataClass);
  return &stateIdle;
}


StateFnCall_StateM_emC const* transIdle(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==1) {
    PRINTMSGLN(*idEvent, " ");
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": Idle->RunA: ");
    //
    doEntry_StateMFnCall_emC(&stateRun, 0, stmn, idEvent1, dataEvent, dataClass);
    doEntry_StateMFnCall_emC(&stateRunA, 0, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunA;
  }
  else if(idEvent1 ==7) {
    PRINTMSGLN(*idEvent, " ");
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": Idle->Run-History: ");
    //
    StateFnCall_StateM_emC const* stateRet = 
      doEntry_StateMFnCall_emC(&stateRun, 2, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return stateRet;
  }
  else {
    return null;
  }
}


StateFnCall_StateM_emC const* transRun(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==9) {
    PRINTMSGLN(*idEvent, " ");
    doExitComposite_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": Run->Idle: ");
    //
    doEntry_StateMFnCall_emC(&stateIdle, 0, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateIdle;
  }
  else {
    return null;
  }
}



StateFnCall_StateM_emC const* transRunA(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==2) {
    PRINTMSGLN(*idEvent, " ");
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": RunA->RunB11,RunB21: ");
    //
    doEntry_StateMFnCall_emC(&stateRunB, 0, stmn, idEvent1, dataEvent, dataClass);
    doEntry_StateMFnCall_emC(&stateRunB11, 0, stmn, idEvent1, dataEvent, dataClass); //determined parallel state
    doEntry_StateMFnCall_emC(&stateRunB21, 0, stmn, idEvent1, dataEvent, dataClass); //determined parallel state
    *idEvent = -1;
    return &stateRunB; //to execute its trans action as RunToComplete
  }
  else {
    return null;
  }
}


StateFnCall_StateM_emC const* transRunB(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  int32 idEvent1 = *idEvent;
  if(false) {
    PRINTMSGLN(*idEvent, " ");
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": RunB->???: ");
    //
    return &stateIdle;
  }
  else {
    return null;
  }
}


StateFnCall_StateM_emC const* transRunC(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  if(ASSERTs_emC(INSTANCEOF_ObjectJc(dataClass, refl_MyTestStatechartData), "faulty", 0, 0)) {
    MyTestStatechartData* data = C_CAST(MyTestStatechartData*, dataClass);  //It is an downcast for C data without pointer adjustment.
    int32 idEvent1 = *idEvent;
    if(data->b1) {
      PRINTMSGLN(*idEvent, " ");
      doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
      doExit_StateMFnCall_emC(&stateRun, stmn, idEvent1, dataEvent, dataClass);
      //
      //The trans action ....
      PRINTMSG(": RunC->Idle: ");
      //
      doEntry_StateMFnCall_emC(&stateIdle, 0, stmn, idEvent1, dataEvent, dataClass);
      return &stateIdle;
    }
    else {
      return null;
    }
  } else { return null; } //The non-asserted case.
}


StateFnCall_StateM_emC const* transRunB11(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==3) {
    PRINTMSGLN(*idEvent, " ");
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": RunB11->RunB12: ");
    //
    doEntry_StateMFnCall_emC(&stateRunB12, 0, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunB12;
  }
  else if(idEvent1 ==4) {
    PRINTMSGLN(*idEvent, " ");
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": RunB11->RunB12: ");
    //
    doEntry_StateMFnCall_emC(&stateRunB12, 0, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunB12;
  }
  else {
    return null;
  }
}


StateFnCall_StateM_emC const* transRunB12(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  int32 idEvent1 = *idEvent;
  if(  idEvent1 ==5   //join transition, checks whether the other parallel is in the requested state.
    && stmn->substmn[stateRunB22.ixStmn].state == &stateRunB22) {
    PRINTMSGLN(*idEvent, " ");
    //It is necessary to exit all parallel and the container state here.
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    doExit_StateMFnCall_emC(&stateRunB22, stmn, idEvent1, dataEvent, dataClass);
    doExit_StateMFnCall_emC(&stateRunB, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": RunB12,RunB22->RunC: ");
    //

    doEntry_StateMFnCall_emC(&stateRunC, 0, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunC;
  }
  else {
    return null;
  }
}

StateFnCall_StateM_emC const* transRunB21(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==3) {
    PRINTMSGLN(*idEvent, " ");
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": RunB21->RunB22: ");
    //
    doEntry_StateMFnCall_emC(&stateRunB22, 0, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunB22;
  }
  else {
    return null;
  }
}

StateFnCall_StateM_emC const* transRunB22(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  int32 idEvent1 = *idEvent;
  if(idEvent1 ==5   //join transition, checks whether the other parallel is in the requested state.
    && stmn->substmn[stateRunB12.ixStmn].state == &stateRunB12) {
    PRINTMSGLN(*idEvent, " ");
    //It is necessary to exit all parallel and the container state here.
    doExit_StateMFnCall_emC(thiz, stmn, idEvent1, dataEvent, dataClass);
    doExit_StateMFnCall_emC(&stateRunB12, stmn, idEvent1, dataEvent, dataClass);
    doExit_StateMFnCall_emC(&stateRunB, stmn, idEvent1, dataEvent, dataClass);
    //
    //The trans action ....
    PRINTMSG(": RunB12,RunB22->RunC: ");
    //
    doEntry_StateMFnCall_emC(&stateRunC, 0, stmn, idEvent1, dataEvent, dataClass);
    *idEvent = -1;
    return &stateRunC;
  }
  else {
    return null;
  }
}



