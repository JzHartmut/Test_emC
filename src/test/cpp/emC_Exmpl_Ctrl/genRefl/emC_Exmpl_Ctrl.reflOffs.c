/**This file is generated by Cheaer2Refl.jzTc mady by Hartmut Schorrig Version 2020-04-26
 */
#include <applstdef_emC.h>  //may/should contain following compilerswitch:
#ifdef DEF_REFLECTION_OFFS  //compile this only if DEF_REFLECTION_OFFS should be used 
#include <emC/InspcTargetSimple/Target2Proxy_Inspc.h>  //declares reflectionOffsetArrays


    
#include <emC_Exmpl_Ctrl/applstdef_emC.h>  

    
#include <emC_Exmpl_Ctrl/Test_Ctrl.h>  

int32 const reflectionOffset_Base_Test_Ctrl[] =
{ 1   //index of class in Offset data
, ((sizeof(ObjectJc)<<16) | 0 + sizeof(ObjectJc)/* offset on bitfield: offset of element before + sizeof(element before) */)
};

extern_C ClassJc const refl_Base_Test_Ctrl; //forward declaration because extern "C" 
ClassJc const refl_Base_Test_Ctrl = 
{ 1   //index of class in Offset data    //sizeof(reflectionOffset_Base_Test_Ctrl)
, &reflectionOffset_Base_Test_Ctrl[0]
};

int32 const reflectionOffset_Test_Ctrl[] =
{ 2   //index of class in Offset data
, ((sizeof(((Test_Ctrl*)(0x1000))->ws)<<16) | (int16)( ((intptr_t)(&((Test_Ctrl*)(0x1000))->ws)) -0x1000 ))
, ((sizeof(((Test_Ctrl*)(0x1000))->fT1)<<16) | (int16)( ((intptr_t)(&((Test_Ctrl*)(0x1000))->fT1)) -0x1000 ))
, ((sizeof(((Test_Ctrl*)(0x1000))->fs)<<16) | (int16)( ((intptr_t)(&((Test_Ctrl*)(0x1000))->fs)) -0x1000 ))
, ((sizeof(((Test_Ctrl*)(0x1000))->sT1)<<16) | (int16)( ((intptr_t)(&((Test_Ctrl*)(0x1000))->sT1)) -0x1000 ))
, ((sizeof(((Test_Ctrl*)(0x1000))->sI)<<16) | (int16)( ((intptr_t)(&((Test_Ctrl*)(0x1000))->sI)) -0x1000 ))
, ((sizeof(((Test_Ctrl*)(0x1000))->s)<<16) | (int16)( ((intptr_t)(&((Test_Ctrl*)(0x1000))->s)) -0x1000 ))
, ((sizeof(((Test_Ctrl*)(0x1000))->par)<<16) | (int16)( ((intptr_t)(&((Test_Ctrl*)(0x1000))->par)) -0x1000 ))
, ((sizeof(((Test_Ctrl*)(0x1000))->pid)<<16) | (int16)( ((intptr_t)(&((Test_Ctrl*)(0x1000))->pid)) -0x1000 ))
};

extern_C ClassJc const refl_Test_Ctrl; //forward declaration because extern "C" 
ClassJc const refl_Test_Ctrl = 
{ 2   //index of class in Offset data    //sizeof(reflectionOffset_Test_Ctrl)
, &reflectionOffset_Test_Ctrl[0]
};

    
#include <emC/Ctrl/PIDf_Ctrl_emC.h>  

int32 const reflectionOffset_Par_PIDf_Ctrl_emC_T_Internal_PIDf_Ctrl_emC_t[] =
{ 3   //index of class in Offset data
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fTsD)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fTsD)) - ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) )  /*implicit struct*/)
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fD)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fD)) - ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) )  /*implicit struct*/)
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fI)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fI)) - ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) )  /*implicit struct*/)
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fIx)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fIx)) - ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) )  /*implicit struct*/)
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fIy)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.fIy)) - ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) )  /*implicit struct*/)
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.dbgct_reparam)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i.dbgct_reparam)) - ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) )  /*implicit struct*/)
};

extern_C ClassJc const refl_Par_PIDf_Ctrl_emC_T_Internal_PIDf_Ctrl_emC_t; //forward declaration because extern "C" 
ClassJc const refl_Par_PIDf_Ctrl_emC_T_Internal_PIDf_Ctrl_emC_t = 
{ 3   //index of class in Offset data    //sizeof(reflectionOffset_Par_PIDf_Ctrl_emC_T_Internal_PIDf_Ctrl_emC_t)
, &reflectionOffset_Par_PIDf_Ctrl_emC_T_Internal_PIDf_Ctrl_emC_t[0]
};

int32 const reflectionOffset_Par_PIDf_Ctrl_emC[] =
{ 4   //index of class in Offset data
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->Tstep)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->Tstep)) -0x1000 ))
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->kP)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->kP)) -0x1000 ))
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->Tn)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->Tn)) -0x1000 ))
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->Td)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->Td)) -0x1000 ))
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->T1d)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->T1d)) -0x1000 ))
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->lim)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->lim)) -0x1000 ))
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) -0x1000 ))
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) -0x1000 ) + sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)/* offset on bitfield: offset of element before + sizeof(element before) */)
, ((sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)<<16) | (int16)( ((intptr_t)(&((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)) -0x1000 ) + sizeof(((Par_PIDf_Ctrl_emC_s*)(0x1000))->i)/* offset on bitfield: offset of element before + sizeof(element before) */)
};

extern_C ClassJc const refl_Par_PIDf_Ctrl_emC; //forward declaration because extern "C" 
ClassJc const refl_Par_PIDf_Ctrl_emC = 
{ 4   //index of class in Offset data    //sizeof(reflectionOffset_Par_PIDf_Ctrl_emC)
, &reflectionOffset_Par_PIDf_Ctrl_emC[0]
};

int32 const reflectionOffset_PIDf_Ctrl_emC[] =
{ 5   //index of class in Offset data
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->par)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->par)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->Tstep)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->Tstep)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->dwxP)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->dwxP)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->wxP)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->wxP)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->wxPD)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->wxPD)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->y)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->y)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->qI)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->qI)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->qIhi)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->qIhi)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->wxP32)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->wxP32)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->wxPD32)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->wxPD32)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->qD1)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->qD1)) -0x1000 ))
, ((sizeof(((PIDf_Ctrl_emC_s*)(0x1000))->dbgct_reparam)<<16) | (int16)( ((intptr_t)(&((PIDf_Ctrl_emC_s*)(0x1000))->dbgct_reparam)) -0x1000 ))
};

extern_C ClassJc const refl_PIDf_Ctrl_emC; //forward declaration because extern "C" 
ClassJc const refl_PIDf_Ctrl_emC = 
{ 5   //index of class in Offset data    //sizeof(reflectionOffset_PIDf_Ctrl_emC)
, &reflectionOffset_PIDf_Ctrl_emC[0]
};

    
#include <emC/Base/Time_emC.h>  

int32 const reflectionOffset_SimTime_emC[] =
{ 6   //index of class in Offset data
, ((sizeof(((SimTime_emC*)(0x1000))->timeShort)<<16) | (int16)( ((intptr_t)(&((SimTime_emC*)(0x1000))->timeShort)) -0x1000 ))
, ((sizeof(((SimTime_emC*)(0x1000))->spare1_8aligned)<<16) | (int16)( ((intptr_t)(&((SimTime_emC*)(0x1000))->spare1_8aligned)) -0x1000 ))
, ((sizeof(((SimTime_emC*)(0x1000))->timeSim)<<16) | (int16)( ((intptr_t)(&((SimTime_emC*)(0x1000))->timeSim)) -0x1000 ))
};

extern_C ClassJc const refl_SimTime_emC; //forward declaration because extern "C" 
ClassJc const refl_SimTime_emC = 
{ 6   //index of class in Offset data    //sizeof(reflectionOffset_SimTime_emC)
, &reflectionOffset_SimTime_emC[0]
};

int32 const reflectionOffset_MinMaxCalcTime_emC[] =
{ 7   //index of class in Offset data
, ((sizeof(((MinMaxCalcTime_emC*)(0x1000))->minCalcTime)<<16) | (int16)( ((intptr_t)(&((MinMaxCalcTime_emC*)(0x1000))->minCalcTime)) -0x1000 ))
, ((sizeof(((MinMaxCalcTime_emC*)(0x1000))->midCalcTime)<<16) | (int16)( ((intptr_t)(&((MinMaxCalcTime_emC*)(0x1000))->midCalcTime)) -0x1000 ))
, ((sizeof(((MinMaxCalcTime_emC*)(0x1000))->actCalcTime)<<16) | (int16)( ((intptr_t)(&((MinMaxCalcTime_emC*)(0x1000))->actCalcTime)) -0x1000 ))
, ((sizeof(((MinMaxCalcTime_emC*)(0x1000))->maxCalcTime)<<16) | (int16)( ((intptr_t)(&((MinMaxCalcTime_emC*)(0x1000))->maxCalcTime)) -0x1000 ))
};

extern_C ClassJc const refl_MinMaxCalcTime_emC; //forward declaration because extern "C" 
ClassJc const refl_MinMaxCalcTime_emC = 
{ 7   //index of class in Offset data    //sizeof(reflectionOffset_MinMaxCalcTime_emC)
, &reflectionOffset_MinMaxCalcTime_emC[0]
};

int32 const reflectionOffset_MinMaxTime_emC[] =
{ 8   //index of class in Offset data
, ((sizeof(((MinMaxTime_emC*)(0x1000))->ct)<<16) | (int16)( ((intptr_t)(&((MinMaxTime_emC*)(0x1000))->ct)) -0x1000 ))
, ((sizeof(((MinMaxTime_emC*)(0x1000))->_lastTime)<<16) | (int16)( ((intptr_t)(&((MinMaxTime_emC*)(0x1000))->_lastTime)) -0x1000 ))
, ((sizeof(((MinMaxTime_emC*)(0x1000))->minCyclTime)<<16) | (int16)( ((intptr_t)(&((MinMaxTime_emC*)(0x1000))->minCyclTime)) -0x1000 ))
, ((sizeof(((MinMaxTime_emC*)(0x1000))->actCyclTime)<<16) | (int16)( ((intptr_t)(&((MinMaxTime_emC*)(0x1000))->actCyclTime)) -0x1000 ))
, ((sizeof(((MinMaxTime_emC*)(0x1000))->midCyclTime)<<16) | (int16)( ((intptr_t)(&((MinMaxTime_emC*)(0x1000))->midCyclTime)) -0x1000 ))
, ((sizeof(((MinMaxTime_emC*)(0x1000))->maxCyclTime)<<16) | (int16)( ((intptr_t)(&((MinMaxTime_emC*)(0x1000))->maxCyclTime)) -0x1000 ))
, ((sizeof(((MinMaxTime_emC*)(0x1000))->calc)<<16) | (int16)( ((intptr_t)(&((MinMaxTime_emC*)(0x1000))->calc)) -0x1000 ))
};

extern_C ClassJc const refl_MinMaxTime_emC; //forward declaration because extern "C" 
ClassJc const refl_MinMaxTime_emC = 
{ 8   //index of class in Offset data    //sizeof(reflectionOffset_MinMaxTime_emC)
, &reflectionOffset_MinMaxTime_emC[0]
};

int32 const reflectionOffset_Clock_MinMaxTime_emC[] =
{ 9   //index of class in Offset data
, ((sizeof(((Clock_MinMaxTime_emC*)(0x1000))->microSecondsPerClock)<<16) | (int16)( ((intptr_t)(&((Clock_MinMaxTime_emC*)(0x1000))->microSecondsPerClock)) -0x1000 ))
, ((sizeof(((Clock_MinMaxTime_emC*)(0x1000))->nrofSlices)<<16) | (int16)( ((intptr_t)(&((Clock_MinMaxTime_emC*)(0x1000))->nrofSlices)) -0x1000 ))
, ((sizeof(((Clock_MinMaxTime_emC*)(0x1000))->times)<<16) | (int16)( ((intptr_t)(&((Clock_MinMaxTime_emC*)(0x1000))->times)) -0x1000 ))
};

extern_C ClassJc const refl_Clock_MinMaxTime_emC; //forward declaration because extern "C" 
ClassJc const refl_Clock_MinMaxTime_emC = 
{ 9   //index of class in Offset data    //sizeof(reflectionOffset_Clock_MinMaxTime_emC)
, &reflectionOffset_Clock_MinMaxTime_emC[0]
};


/**Array of pointer to all refl_Type definition.
 * The order of the pointer matches to the ClassJc#index
 * The target2proxy service accesses the correct ClassJc by given index in communication.
 */
ClassJc const* const reflectionOffsetArrays[] =
{ null  //index 0 left free 
, &refl_Base_Test_Ctrl
, &refl_Test_Ctrl
, &refl_Par_PIDf_Ctrl_emC_T_Internal_PIDf_Ctrl_emC_t
, &refl_Par_PIDf_Ctrl_emC
, &refl_PIDf_Ctrl_emC
, &refl_SimTime_emC
, &refl_MinMaxCalcTime_emC
, &refl_MinMaxTime_emC
, &refl_Clock_MinMaxTime_emC
    
};

#endif //DEF_REFLECTION_OFFS
