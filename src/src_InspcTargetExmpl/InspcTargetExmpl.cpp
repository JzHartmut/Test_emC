/**This file offers a socmd.exe which sends a command via socket connection
 * and UDP telegram to a receiver.
 * The receiver is often a Java program which executes this cmd
 * for any desired control operation.
 * Such a socmd.exe helps to integrate a Java process in any desired environment
 * which can execute commands from the OS. That is true for many script base applications.
 * Made by Hartmut Schorrig, Germany, www.vishia.org
 * Copyright/left LPGL license.
 * This license remark also in the executable must not deleted.
 */
#include <InspcTargetExmpl.h>
#include <emC/Inspc/Srv/Service_Inspc.h>
#include <stdlib.h>
#include <stdio.h>
 
#ifdef DEF_REFLECTION_FULL
  #include <genRefl/InspcTargetExmpl.crefl>
#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_InspcTargetExmpl)
  //Not defined with DEF_REFLECTION_OFFS but necessary, only as type marker:
  ClassJc const refl_InspcTargetExmpl = INIZ_ClassJc(refl_InspcTargetExmpl, "InspcTargetExmpl");
#endif



char const* help = "\
";






//tag::InspcServiceData[]
/**The inspector service module. */
Inspector_Inspc_s theInspector = {0};
//end::InspcServiceData[]
InspcTargetExmpl_s maindata = {0};

 
//tag::InspcServiceInitStart[]
void main(int nArgs, char** argsCmd) {
  STACKTRC_ROOT_ENTRY("InspcTargetExmpl");
  int erret = 0;
  TRY {
    init_ObjectJc(&theInspector.base.object, sizeof(theInspector), 0);
    // =========== construct the inspector on target, 
    StringJc sIpPort = s0_StringJc("UDP:0.0.0.0:60092");   // IP address: any hardware adapter or also 
    //StringJc sIpPort = s0_StringJc("UDP:127.0.0.1:60092"); // IP address: only via local host access 
    ctorO_Inspector_Inspc(&theInspector.base.object, sIpPort, _thCxt);
    //
    //maybe further initializations, also a init loop
    //
    // =========== after all is initialized: start the inspector service
    MemSegmJc rootAddr = INIZ_MemSegmJc(&maindata.base.obj, 0);
    start_Inspector_Inspc_F(&theInspector, &refl_InspcTargetExmpl, rootAddr, _thCxt);
    //end::InspcServiceInitStart[]
    //
    //Example: Only a simple loop
    maindata.bRun =1;
    while(maindata.bRun) {
      maindata.y = maindata.x;
    }
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_Exception_emC(exc, _thCxt);
    erret = 255;
  }
  END_TRY
  exit(erret);
  //STACKTRC_RETURN;
}





void errorSystem_emC_  (  int errorCode, const char* description, int value1, int value2, char const* file, int line) {
  printf("ERROR SYSTEM: %d %s %d, %d @%s:%d", errorCode, description, value1, value2, file, line);
  exit(255);
}



//Note: The uncatched_Exception should be assigned to the application frame. It is not a part of a library.
//It should terminate the application, but some resources should be freed. The application frame may known which resources.
void uncatched_Exception_emC  (  Exception_emC* thiz, ThreadContext_emC_s* _thCxt) {
#ifdef DEF_NO_StringJcCapabilities
  printf("ERROR uncatched Exception @%s:%d", thiz->file, thiz->line);
#else
  char buffer[300] = { 0 };
  writeException(buffer, sizeof(buffer), thiz, __FILE__, __LINE__, _thCxt);
  printf(buffer);
  ERROR_SYSTEM_emC(thiz->exceptionNr, "System termination", 0,0);
#endif
}

