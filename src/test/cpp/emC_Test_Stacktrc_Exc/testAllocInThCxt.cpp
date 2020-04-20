#include <applstdef_emC.h>
#include <stdio.h>
#include <emC/Base/MemC_emC.h>


#ifdef DEF_ThreadContextStracktrc_emC

static char const* prepareLog(int val) {
  STACKTRC_ENTRY("prepareLog");
  MemC mem = getUserBuffer_ThreadContext_emC(200, "prepareLog", _thCxt);
  char* buffer = PTR_MemC(mem, char);
  snprintf(buffer, size_MemC(mem), "The message: %d\n", val);
  STACKTRC_LEAVE; return buffer;
}

#else

static char const* prepareLog(int val) {
  return "";
}

#endif //DEF_ThreadContextStracktrc_emC

void testAllocInThCxt() {
  STACKTRC_ENTRY("logger");
  char const* msg = prepareLog(123);
  //printf(msg);
  free_MemC(msg);
  STACKTRC_LEAVE; return;
}

