#include "StringTest_emC.h"
#include <applstdef_emC.h>
#include <emC/Base/String_emC.h>

extern const char4_emC sIdentification[];
const char4_emC sIdentification[] = { CHAR4_emC('I','d','e','n'), CHAR4_emC('t','\0','\0','\0')};


StringJc testStringRet(){
  StringJc ret; // = INIZ_StringJc("Test", 4);
  ret.addr.str = "Test";
  ret.val = 4;
  return ret;
}





void testString_emC(){
  StringJc s1 = testStringRet();
  int length;
  char const* c1 = getCharsAndLength_StringJc(&s1, &length);

}
