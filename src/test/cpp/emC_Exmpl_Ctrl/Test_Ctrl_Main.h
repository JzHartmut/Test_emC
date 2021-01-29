#include <applstdef_emC.h>
#include "Test_Ctrl.h"

/**Instantiates and tests a controller till reaching end value, check the end value. */
extern_C void test_Test_Ctrl(uint maxStep, uint stepusec);

#if defined(__cplusplus) && defined(DEF_cplusplus_emC)
/**
 */
class Test_Ctrl_Main : public Test_Ctrl {
  /**This is an additional private variable, only to show difference in reflection generation. */
  private: int32 stepCt;

  #ifndef NO_PARSE_ZbnfCheader  //it is only for parsing for reflection, see Cheader.zbnf
  public: Test_Ctrl_Main(ObjectJc* othiz);

  /**Step routine for the cyclically controller functionality. */
  public: void step ( ) { Test_Ctrl::step(); }  //hint: calls the C routine. 
  #endif//NO_PARSE_ZbnfCheader  //Note: write exactly without spaces after endif

};
#endif
