#include <applstdef_emC.h>
#include <stdio.h>
#include <stdlib.h>

#if 0  //see emC_srcApplSpec/applConv/fatalError_printf_exitMain.c 
void errorSystem_emC_  (  int errorCode, const char* description, int value1, int value2, char const* file, int line) {
  printf("ERROR SYSTEM: %d %s %d, %d @%s:%d", errorCode, description, value1, value2, file, line);
  exit(255);
}


#ifdef DEFINED_Exception_emC
//Note: The uncatched_Exception should be assigned to the application frame. It is not a part of a library.
//It should terminate the application, but some resources should be freed. The application frame may known which resources.
void uncatched_Exception_emC  (  Exception_emC* thiz, ThreadContext_emC_s* _thCxt) {
#ifdef DEF_NO_StringUSAGE
  printf("ERROR uncatched Exception @%s:%d", thiz->file, thiz->line);
#else
  char buffer[300] = { 0 };
  writeException(buffer, sizeof(buffer), thiz, __FILE__, __LINE__, _thCxt);
  printf(buffer);
#endif
}
#endif

#endif

ObjectJc* alloc_ObjectJc_verySimple_emC(int size, int id) {
  ObjectJc* othiz = (ObjectJc*)malloc(size);
  othiz->id = id;
  return othiz;
}
