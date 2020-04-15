#ifndef HEADERGUARD_org_vishia_emC_Base_test_StateM_tplGen_StateFnCall_StateM_emC
#define HEADERGUARD_org_vishia_emC_Base_test_StateM_tplGen_StateFnCall_StateM_emC

#include <emC/StateM/StateFnCall_StateM_emC.h>

extern const StateFnCall_StateM_emC stateInit;
extern const StateFnCall_StateM_emC stateIdle;
extern const StateFnCall_StateM_emC stateRun;
extern const StateFnCall_StateM_emC stateRunA;
extern const StateFnCall_StateM_emC stateRunB;
extern const StateFnCall_StateM_emC stateRunB11;
extern const StateFnCall_StateM_emC stateRunB12;
extern const StateFnCall_StateM_emC stateRunB21;
extern const StateFnCall_StateM_emC stateRunB22;
extern const StateFnCall_StateM_emC stateRunC;


extern DoEntry_StateFnCall_StateM_emC doEntryIdle;
extern DoEntry_StateFnCall_StateM_emC doEntryRun;
extern DoEntry_StateFnCall_StateM_emC doEntryRunA;
extern DoEntry_StateFnCall_StateM_emC doEntryRunB;
extern DoEntry_StateFnCall_StateM_emC doEntryRunC;
extern DoEntry_StateFnCall_StateM_emC doEntryRunB11;
extern DoEntry_StateFnCall_StateM_emC doEntryRunB12;
extern DoEntry_StateFnCall_StateM_emC doEntryRunB21;
extern DoEntry_StateFnCall_StateM_emC doEntryRunB22;

extern DoExit_StateFnCall_StateM_emC doExitIdle;
extern DoExit_StateFnCall_StateM_emC doExitRun;
extern DoExit_StateFnCall_StateM_emC doExitRunA;
extern DoExit_StateFnCall_StateM_emC doExitRunB;
extern DoExit_StateFnCall_StateM_emC doExitRunC;
extern DoExit_StateFnCall_StateM_emC doExitRunB11;
extern DoExit_StateFnCall_StateM_emC doExitRunB12;
extern DoExit_StateFnCall_StateM_emC doExitRunB21;
extern DoExit_StateFnCall_StateM_emC doExitRunB22;



typedef struct MyStateM_T {

  #define ixSTM_Top 0
  StateMnTopFnCall_State_emC statesTop;

  #define ixSTM_Run 1
  StateMPartFnCall_StateM_emC statesRun; //:for the composite state Run, the nested ones

  #define ixSTM_RunP1 2
  StateMPartFnCall_StateM_emC statesRunParallel1; //:for the composite state Run, the nested ones
  #define ixSTM_RunP2 3
  StateMPartFnCall_StateM_emC statesRunParallel2; //:for the composite state Run, the nested ones

} MyStateM;


#define INIZ_MyStateM(OBJ) \
  { INIZ_StateMnTopFnCall_StateM_emC(OBJ, &reflection_MyStateM, 4, stateInit) \
  , INIZ_StateMPartFnCall_StateM_emC(1, stateRunA) \
  , INIZ_StateMPartFnCall_StateM_emC(2, stateRunB11) \
  , INIZ_StateMPartFnCall_StateM_emC(3, stateRunB21) \
  } 





/**A data class appropriate to the state chart of this class. */
typedef struct MyData_T {
  union { ObjectJc obj; } base;
  /**Any boolean*/
  int b1;

  /**contains the statechart. */
  MyStateM stateChart;
} MyData;


#define INIZ_MyData(OBJ, REFL) \
  { { INIZ_ObjectJc((OBJ).base.obj, REFL, 0) } \
  , 1 \
  , INIZ_MyStateM((OBJ).stateChart) \
  }



#endif //HEADERGUARD_org_vishia_emC_Base_test_StateM_tplGen_StateFnCall_StateM_emC
