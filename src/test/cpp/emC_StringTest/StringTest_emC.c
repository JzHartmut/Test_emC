#include <applstdef_emC.h>
#include "StringTest_emC.h"
#include <emC/Base/String_emC.h>
#include <emC/Test/testAssert.h>

extern const char4_emC sIdentification[];
const char4_emC sIdentification[] = { CHAR4_emC('I','d','e','n'), CHAR4_emC('t','\0','\0','\0')};


StringJc testStringRet_intern(){
  StringJc ret; // = INIZ_StringJc("Test", 4);
  ret.addr.str = "Test";
  ret.val = 4;
  return ret;
}


void testStringRet  (  ){
  StringJc s1 = testStringRet_intern();
  int length;
  char const* c1 = getCharsAndLength_StringJc(&s1, &length);
}



void test_searchChar ( ) {
  TEST_START("searchChar");
  char const* s1 = "abcdefg";
  int pos = searchCharBack_emC(s1, 'c', 6);
  TEST_TRUE(pos == 2, "searchCharBack_emC containing char fails");
  pos = searchCharBack_emC(s1, 'g', 6);
  TEST_TRUE(pos == 6, "searchCharBack_emC last char fails");
  pos = searchCharBack_emC(s1, 'g', -1);
  TEST_TRUE(pos == 6, "searchCharBack_emC last char from end fails");
  pos = searchCharBack_emC(s1, 'a', -1);
  TEST_TRUE(pos == 0, "searchCharBack_emC first char fails");
  pos = searchCharBack_emC(s1, 'X', 6);
  TEST_TRUE(pos == -1, "searchCharBack_emC non-containing char fails");
  TEST_END;
}




void testString_emC ( ){
  test_searchChar();
  //testStringRet();
}
