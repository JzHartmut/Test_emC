#include "test_ObjectJc_Mutex.h"
#include <applstdef_emC.h>
#include <emC/Test/testAssert.h>

void test_ObjectJc_SimpleLock(void) {
  STACKTRC_ENTRY("test_ObjectJc");
  TEST_START("test_ObjectJc");
  TRY {
    ObjectJc obj = INIZ_ObjectJc(obj, refl_ObjectJc, 0);

    lock_ObjectJc(&obj);
    bool isLocked = isLocked_ObjectJc(&obj);
    TEST_TRUE(isLocked, "Object is locked");
    unlock_ObjectJc(&obj);
    isLocked = isLocked_ObjectJc(&obj);
    TEST_TRUE(!isLocked, "Object is not locked");
  }_TRY
  CATCH(Exception, exc) {
    TEST_EXC(exc);
  }
  END_TRY
  TEST_END;
  STACKTRC_RETURN;
}