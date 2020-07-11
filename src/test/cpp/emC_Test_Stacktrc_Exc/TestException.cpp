#include "TestException.h"

#include <emC/OSAL/os_time.h>


#include <stdio.h>
#include <signal.h>
#include <emC/Test/testAssert.h>

#ifdef DEF_NO_REFLECTION
//  char const refl_MyData[] = "REFLMyData";
#else
//  #include "../genRefl/TestExcReflVariants.crefl"
#endif

ClassJc const refl_MyData = INIZ_ClassJc(refl_MyData, "MyData");


//Hint: CONST_MyData is a define which follows with { { ....} ...} the typedef of Mydata.
//The using of the macor of user level should present only the important things.
static MyData dataTestException = INIZ_MyData(dataTestException, refl_MyData);



void segmSignal(int signal2){
  STACKTRC_ENTRY("MemorySegmentationViolation");
  THROW_s0(Exception, "memory", 0, 0);
  STACKTRC_LEAVE;
}



float testThrow(MyData* thiz, uint ix, float val, ThCxt* _thCxt) {
  STACKTRC_TENTRY("testThrow");
  //TODO int stackSizeMax = getMaxStackDepth_ThreadContext_emC(_thCxt); //only for debug
  if (ix >= ARRAYLEN_emC(thiz->array)) {
    char msg[40] = {0};  //prepare a message in stack area, will be copied in ThreadContext
    snprintf(msg, sizeof(msg), "faulty index:%d for value %f", ix, val);
    StringJc sMsg = z_StringJc(msg);
    thiz->testThrowResult = -1;  //to document: invalid.
    THROW(IndexOutOfBoundsException, sMsg, ix,0);
    ix = ARRAYLEN_emC(thiz->array) -1;  //replacement on error: Set index to the last element.
                                        //TODO stackSizeMax = getMaxStackDepth_ThreadContext_emC(_thCxt); //only for debug
  }
  thiz->array[ix] = val;
  { uint ix;
    thiz->testThrowResult = 0;
    for (ix = 0; ix < ARRAYLEN_emC(thiz->array); ++ix) {
      thiz->testThrowResult += thiz->array[ix]; 
    }
  }
  STACKTRC_LEAVE; return thiz->array[0];
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
  } END_TRY
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







int test_Exception ( ) {
  STACKTRC_ENTRY("test_Exception");
  TEST_START("test_Exception");
  MyData* thiz = ctor_MyData(&dataTestException);
  thiz->base.super.bRun = 1;
  signal(SIGSEGV, segmSignal );
  //
  bool bHasCatched = false;  
  bool bHasFinally = false;  
  TRY{
    //raise(SIGSEGV);
    bHasCatched = false;
  }_TRY
  CATCH(Exception, exc) {
    bHasCatched = true;
  }
  FINALLY {
    bHasFinally = true;
  } END_TRY
  TEST_TRUE(!bHasCatched && bHasFinally, "TRY without THROW with FINALLY is ok ");

  bHasCatched = false;  
  bHasFinally = false;  
  TRY{
    //raise(SIGSEGV);
    CALLINE; float val = testThrow(thiz, 10, 2.0f, _thCxt);
    printf("val=%f\n", val);
  }_TRY
  CATCH(Exception, exc) {
    CHECK_TRUE(exc->line == 41, "faulty line for THROW");
    int posFile = searchString_emC(exc->file, -1000, "TestException.cpp", -100);
    TEST_TRUE(posFile > 0, "File hint found in Exception");
    #ifndef DEF_NO_StringJcCapabilities
      char buffer[115] = "Exceptiontext: ";
      int z = writeException(buffer+15, sizeof(buffer)-16, exc, __FILE__, __LINE__, _thCxt);
      char const* stringCmp = "Exceptiontext: faulty index:10 for value 2.000000(10, 0) in: src/test/cpp/emC_Test_Stacktrc_Exc/TestException.cpp@41, oper: testThrow(@34), detect in: src/test/cpp/emC_Test_Stacktrc_Exc/TestException.cpp@127 (emC_Test_Stacktrc_Exc/TestException.cpp@131)";
      int nEquals = strncmp_emC(buffer, stringCmp,z);
      //first 70 chararcter are equal, after them some line numbers may be different.
      TEST_TRUE(nEquals == 0 || nEquals < 62 || nEquals > -62, buffer);  //Note: from "src/test" the outputs are different because __FILE__ macro.
      printf(buffer);
      printStackTrace_ExceptionJc(exc, _thCxt);
    #endif
    bHasCatched = true;
    thiz->testThrowResult = 0;  //falback strategy: This calculation may faulty.
  }  
  FINALLY {
    bHasFinally = true;
  } END_TRY;
  TEST_TRUE(bHasCatched && bHasFinally, "simple THROW is catched. ");

  bHasCatched = false;  
  bHasFinally = false;  
  TRY{
    //raise(SIGSEGV);
    bHasCatched = false;
  }_TRY
    CATCH(Exception, exc) {
    bHasCatched = true;
  } END_TRY
  TEST_TRUE(!bHasCatched, "TRY without THROW after an Exception before has not entered CATCH BLOCK ");
  //
  bHasCatched = false;  
  bHasFinally = false;  
  TRY{
    //raise(SIGSEGV);
    testTry(thiz);
  }_TRY
  CATCH(Exception, exc) {
    #ifndef NoStringJcCapabilities_emC
    char buffer[1000] = "\nException: ";
    writeException(buffer+12, sizeof(buffer)-12, exc, __FILE__, __LINE__, _thCxt);
    printf(buffer);
    printStackTrace_ExceptionJc(exc, _thCxt);
    #endif
    bHasCatched = true;
    thiz->testThrowResult = 0;  //falback strategy: This calculation may faulty.
  } 
  FINALLY {
    bHasFinally = true;
  } END_TRY
  TEST_TRUE(bHasCatched && bHasFinally, "THROW over 2 levels is catched. ");
  //
  #if defined DEF_Exception_TRYCpp 
  //Test of null pointer exception, or memory segmentation violation
  bHasCatched = false;
  bool bExecuted = true;
  TRY{
    test_MyData(thiz, 124.7f); //forces a null-pointer exception in C++
    bExecuted = false;    //memory segmentation was not executed.
  }_TRY
    CATCH(Exception, exc) {
    #ifndef NoStringJcCapabilities_emC
    printStackTrace_ExceptionJc(exc, _thCxt);
    char buffer[1000] = { 0 };
    writeException(buffer, sizeof(buffer), exc, __FILE__, __LINE__, _thCxt);
    printf(buffer);
    #endif
    bHasCatched = true;
    thiz->testThrowResult = 0;  //falback strategy: This calculation may faulty.
  } END_TRY
  if(bExecuted) {
    TEST_TRUE(bHasCatched , "THROW on memory segmentation violation is catched. ");
  } else {
    printf("    memory segmentation fault not executed, detenction not supported\n");
  }
  #endif 
  //
  TEST_END;
  STACKTRC_LEAVE; return 0;
}


MyData* ctor_MyData(MyData* thiz) {
  CTOR_ObjectJc(&thiz->base.object, thiz, sizeof(MyData), refl_MyData, 0);
  return thiz;
}





bool test_MyData ( MyData* thiz, float val){
  STACKTRC_ENTRY("test_MyData");
  bool bOk;
  thiz->array[0] = val;
  float* array1 = thiz->array; //not recommended, size is unknown.
  bOk = *array1 >=0;  //prevent warning only.
  CALLINE;
  #if defined(DEF_Exception_TRYCpp) && defined(DEF_MS_VISUAL_STUDIO)  //only visual studio can this feature.
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
  STACKTRC_RETURN bOk;
}



