#include "TestException.h"

#include <emC/OSAL/os_time.h>


#include <stdio.h>
#include <signal.h>

#ifdef DEF_NO_REFLECTION
//  char const refl_MyData[] = "REFLMyData";
#else
//  #include "../genRefl/TestExcReflVariants.crefl"
#endif

ClassJc const refl_MyData = INIZ_ClassJc(refl_MyData, "MyData");


//Hint: CONST_MyData is a define which follows with { { ....} ...} the typedef of Mydata.
//The using of the macor of user level should present only the important things.
MyData data = INIZ_MyData(data, refl_MyData);



void segmSignal(int signal2){
  STACKTRC_ENTRY("MemorySegmentationViolation");
  THROW_s0(Exception, "memory", 0, 0);
  STACKTRC_LEAVE;
}



int test_Exception ( ) {
  STACKTRC_ENTRY("test_Exception");
  ctor_MyData(&data);
  data.base.super.bRun = 1;
  signal(SIGSEGV, segmSignal );
  TRY{
    //raise(SIGSEGV);
    testTry(&data);
  }_TRY
    CATCH(Exception, exc) {
    #ifndef NoStringJcCapabilities_emC
    char buffer[1000] = "\nException: ";
    writeException(buffer+12, sizeof(buffer)-12, exc, __FILE__, __LINE__, _thCxt);
    printf(buffer);
    printStackTrace_ExceptionJc(exc, _thCxt);
    #endif
    data.testThrowResult = 0;  //falback strategy: This calculation may faulty.
  }END_TRY;
  //
  TRY{
    test_MyData(&data, 124.7f); //forces a null-pointer exception in C++
  }_TRY
    CATCH(Exception, exc) {
    #ifndef NoStringJcCapabilities_emC
    printStackTrace_ExceptionJc(exc, _thCxt);
    char buffer[1000] = { 0 };
    writeException(buffer, sizeof(buffer), exc, __FILE__, __LINE__, _thCxt);
    printf(buffer);
    #endif
    data.testThrowResult = 0;  //falback strategy: This calculation may faulty.
  }END_TRY;
  //

//  calculateInLoop(&data);    //to test reflection access via inspector.
  STACKTRC_LEAVE; return 0;
}


MyData* ctor_MyData(MyData* thiz) {
  CTOR_ObjectJc(&thiz->base.object, thiz, sizeof(MyData), refl_MyData, 0);
  return thiz;
}





void test_MyData(MyData* thiz, float val){
  STACKTRC_ENTRY("test_MyData");
  thiz->array[0] = val;
  float* array1 = thiz->array; //not recommended, size is unknown.
  CALLINE;
  #if defined(__TRYCPPJc)
  //faulty, forces asynchron exception, works only in C++ with exception handling
  //It is here to demonstrate the C++ asynchron exception handling on PC (Visual Studio)
  //For PC run, it fails if Exception handling is not activated. 
  //The Program stops, advantage: position of error is visible
  //Such errors should be eliminated if the software is used well tested without exception handling.
  //On a target platform without memory protection the error may not be detected.
  //But side effects are possible.
  array1 = null;
  array1[1] = 5.0f * val;
  #endif
  STACKTRC_LEAVE;
}



/**This routine contains a TRY...CATCH and continues work. */
float testTry(MyData* thiz) {
  STACKTRC_ENTRY("testTry");
  float val;
  TRY{
    val = testTryLevel2(thiz, _thCxt);
  }_TRY
  CATCH(ClassCastException, exc) {
    //It is not recommended to do printStacktrace in normal case
    //because the exception is handled here. Only for debug, it may be important.
    printStackTrace_ExceptionJc(exc, _thCxt);
    //But save a log entry may be proper if the exception is not expected:
    val = 0;
  }FINALLY{
    val = 1;
  }END_TRY;
  STACKTRC_LEAVE;
  return val;
}



/**It is a called routine from TRY level without catch.*/
float testTryLevel2(MyData* thiz, ThCxt* _thCxt) {
  STACKTRC_TENTRY("testTryLevel2");
  CALLINE; float val = testThrow(thiz, 10, 2.0f, _thCxt);
  STACKTRC_LEAVE;
  return val;
}



float testThrow(MyData* thiz, int ix, float val, ThCxt* _thCxt) {
  STACKTRC_TENTRY("testThrow");
  //TODO int stackSizeMax = getMaxStackDepth_ThreadContext_emC(_thCxt); //only for debug
  if (ix < 0 || ix >= ARRAYLEN_emC(thiz->array)) {
    char msg[40] = {0};
    //todo snprintf(msg, sizeof(msg), "faulty index:%d for value %f", ix, val);
    thiz->testThrowResult = -1;  //to document: invalid.
    THROW1_s0(IndexOutOfBoundsException, msg, ix);
    ix = ARRAYLEN_emC(thiz->array) -1;  //replacement on error: Set index to the last element.
    //TODO stackSizeMax = getMaxStackDepth_ThreadContext_emC(_thCxt); //only for debug
  }
  thiz->array[ix] = val;
  { int ix;
    thiz->testThrowResult = 0;
    for (ix = 0; ix < ARRAYLEN_emC(thiz->array); ++ix) {
      thiz->testThrowResult += thiz->array[ix]; 
    }
  }
  STACKTRC_LEAVE; return thiz->array[0];
}


