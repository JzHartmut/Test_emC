/*
 * main_test_C_Cpp.c
 *
 *  Created on: 09.04.2020
 *      Author: hartmut
 */

#include "emc_Test_C_Cpp/test_C_Cpp_TestemC.h"

#include "emc_Test_C_Cpp/TestVtblExplicit.h"



void main_test_C_Cpp ( ){
  MAYBE_UNUSED_emC float f = 0;
  testVtbl_virtual();
  test_TestVtblExplicit();
  //float f = getData_const();
 
}

