/*
 * main_test_C_Cpp.c
 *
 *  Created on: 09.04.2020
 *      Author: hartmut
 */

#include "test_C_Cpp_TestemC.h"

#include "TestVtblExplicit.h"



void main_test_C_Cpp ( ){
  float f = 0;
  testVtbl_virtual();
  test_TestVtblExplicit();
  //float f = getData_const();
 
}
