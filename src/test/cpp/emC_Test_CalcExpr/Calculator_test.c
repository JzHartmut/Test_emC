
#include <emC/Ctrl/CalcExpr.h>
#include <emC/Ctrl/CalcExpr_Parse.h>
#include <emC/Ctrl/T1_Ctrl_emC.h>

#include <emC/Base/String_emC.h>
#include <emC/Test/testAssert.h>

#include <stdio.h>

//Only examples for any variable anywhere in memory.
static float a = 8.2f;
static float b = 2.3f;
static float c = 3.0f;
static T1f_Ctrl_emC_s t1Filter = {0};

//any manual written RPN operations (revers polish notation) only for demonstration.
// it calcs (a + c ) / ( b + c )
static Operation_CalcExpr operations[] = {
  { setF_CalcExpr, &a}  //setF and and addF is a function
, { addF_CalcExpr, &c}  //a, c: addresses of variable in memory.
, { push_CalcExpr, null}
, { setF_CalcExpr , &b}
, { addF_CalcExpr, &c}
, {divFs_CalcExpr, null}
, {T1filterF_CalcExpr, &t1Filter}
};


//only a first demonstration example using the manual written RPN operations.
void test_CalcExpr() {
  TEST_START("test_CalcExpr");

  param_T1f_Ctrl_emC(&t1Filter, 0.0001f, 0.000005f);
  CalcExpr calc = {0};
  ctor_CalcExpr(&calc, 0);
  float result;
  for(int ix = 0; ix < 20; ++ix) {
    calc_CalcExpr(&calc, operations, ARRAYLEN_emC(operations));
    result = getFloat_CalcExpr(&calc);
    printf("test_CalcExpr result=%3.3f\n", result);
  }
  TEST_TRUE(check_testAssert(result, 1.335f, 0.01f), "calcExpr with T1");
  TEST_END;
}




//This routine should be written outside CalcExpr sources, due to variables of the user.
OS_PtrValue getVarAddrType_CalcExpr(char const* cvar){
  OS_PtrValue ret = {0};
  ret.val = 'F';  //type float
  if(*cvar == 'a'){ ret.addr = (Addr8_emC*)&a; }
  else if(*cvar == 'b'){ ret.addr = (Addr8_emC*)&b; }
  else if(*cvar == 'c'){ ret.addr = (Addr8_emC*)&c; }
  else { ret.addr = null; }
  return ret;
}



void test_ParseExpr ( ) {

#ifdef DEF_ObjectJcpp_REFLECTION  //only possible with reflection because Vtable is need

  STACKTRC_ENTRY("test_ParseExpr");
  StringJc expr = z_StringJc("a * sysclk() -b + c");

  Operation_CalcExpr operations[20] = {0};  //only for test in stack, should be static, allocated or in pool

  OperationList_CalcExpr operationList = {(PTR_Operation_CalcExpr_ARRAY20*)operations, 20};  //temporary used, stack is ok.

  //NOTE: uses try-throw-catch for C-style with longjmp yet, it is able to change for C++ throw style.
  TRY { 
    parse_CalcExpr(expr, &operationList,_thCxt);  //NOTE: "warning: missing initializer for field 'longjmpBuffer'" is a fake of compiler, see https://stackoverflow.com/questions/1538943/why-is-the-compiler-throwing-this-warning-missing-initializer-isnt-the-stru
  }_TRY
  CATCH(Exception, exc){
    printf("error in expression");
  }END_TRY


  int zOperations = operationList.ixOperation;


  CalcExpr calculator = {0};
  ctor_CalcExpr(&calculator, 0);


  calc_CalcExpr(&calculator, operations, zOperations);

  float result = getFloat_CalcExpr(&calculator);

  printf("result %+3.3f\n", result);

  STACKTRC_LEAVE;

#endif // DEF_ObjectJcpp_REFLECTION  //only possible with reflection because Vtable is need

}




int XXmain(){

  test_CalcExpr();
  test_ParseExpr();
  return 0;
}



