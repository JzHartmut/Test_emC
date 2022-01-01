#include <emC_StringTest/test_StringBase_emC.h>
#include <emC_StringTest/test_CharSeqJc.h>
#include <applstdef_emC.h>
#include <emC/Base/StringBase_emC.h>
#include <emC/Test/testAssert.h>
#include <string.h>



StringJc const sLit1 = INIZ_text_StringJc("String literal");  

char const* s0Lit2 = "other text";

//Next line is syntactically correct (only in C++ ?) but the size is faulty. 
//StringJc const sLit2 = INIZ_text_StringJc(s0Lit2);  



static void testSimple_StringJc ( void) {
  STACKTRC_ENTRY("testSimple_StringJc");
  TEST_START("testSimple_StringJc");

  CHECK_TRUE(length_StringJc(sLit1)==14, "correct length of INIZ_text_StringJc(...)");
  //CHECK_TRUE(length_StringJc(sLit2)==(sizeof(void*)-1), "INIZ_text_StringJc(ref) has length of a pointer, do not use this construct");


  TEST_END;
  STACKTRC_RETURN;

}



static char const* abcde = "abcde";
static char const* xbcde = "xbcde";
static char const* abcdx = "abcdx";

//static StringJc s1 = INIZ_StringJc("abcde", (int)(sizeof("abcde")));

//const int l1 = (int)(sizeof("xxx")-1);

static void test_StringCmp ( ) {
  STACKTRC_ENTRY("test_StringCmp");
  TEST_START("test_StringCmp");

  int cmp1 = strncmp(abcde, xbcde, 5);
  int cmp = strncmp_emC(abcde, xbcde, 5);
  int corrCmp = cmp1 * cmp;
  CHECK_TRUE(cmp == -1 && corrCmp >0, "first char different, return -1 if first char is lesser");

  cmp1 = strncmp(abcdx, abcde, 5);
  cmp = strncmp_emC(abcdx, abcde, 5);
  corrCmp = cmp1 * cmp;
  CHECK_TRUE(cmp == 5 && corrCmp >0, "5. char different, return 5 if 5. char is greater");

  cmp1 = strncmp(abcde, abcdx, INT_MAX_emC);
  cmp = strncmp_emC(abcde, abcdx, INT_MAX_emC);
  corrCmp = cmp1 * cmp;
  CHECK_TRUE(cmp == -5 && corrCmp >0, "5. char different, return -5 if t. char is lesser, nChars = INT_MAX");

  cmp1 = strncmp(abcde, abcde, INT_MAX_emC);
  cmp = strncmp_emC(abcde, abcde, INT_MAX_emC);
  corrCmp = cmp1 * cmp;
  CHECK_TRUE(cmp == 0 && corrCmp ==0, "All char are equal, return 0, nChars = INT_MAX");


  TEST_END;
  STACKTRC_RETURN;
}



static bool checkAll0(char const* buffer, int len) {
  while(--len >=0) {
    if(*buffer++ !=0) return false;
  }
  return true;
}



static void test_StringCpy ( ) {
  STACKTRC_ENTRY("test_StringCpy");
  TEST_START("test_StringCpy");
  
  char dst[40] = {0};  //initializes the whole content with 0
  CHECK_TRUE(checkAll0(dst, 40), "initially all buffer content is 0");

  #if defined(__COMPILER_IS_MSVC__) && defined(__cplusplus)
  int okMsc = strncpy_s(dst, abcde, 40);  //returns 0 as errno
  CHECK_TRUE(okMsc==0, "strncpy_s result ok");
  dst[6] = 'Q';
  okMsc = strncpy_s(dst, abcde, 5);
  CHECK_TRUE(dst[5]==0, "strncpy_s overrides the 5. position with 0-termination though number of chars is 5");
  #endif
  dst[5] = 'Q';
  char* dst1 = strncpy(dst, abcde, 5);
  CHECK_TRUE(dst1 == dst && dst[5]=='Q', "strncpy does not override the 5. position with 0-termination because number of chars is 5");
  //
  //Using strpncpy_emC:
  //
  int zDst = sizeof(dst);
  memset(dst, 0, zDst);  //clean from usage before.
  dst[5] = 'x';
  int posDst  = strpncpy_emC(dst, 0, zDst, abcde, -1);
  int cmpOk = strncmp_emC(dst, "abcde", zDst);
  CHECK_TRUE(posDst ==5 && cmpOk ==0 && dst[5] ==0, "does copy inclusively 0 if it fits in destination");
  posDst += strpncpy_emC(dst, posDst, zDst, abcde, 3);
  cmpOk += strncmp_emC(dst, "abcdeabc", zDst);
  CHECK_TRUE(posDst ==8 && cmpOk ==0, "copy 3 chars on source has 5 chars, 0-terminated");
  //
  posDst += toString_int32_emC(dst + posDst, zDst - posDst, -1234, 10, -1);
  cmpOk = strncmp_emC(dst, "abcdeabc-1234", zDst);
  CHECK_TRUE(posDst ==13 && cmpOk ==0, "write a number -1234");
  





  TEST_END;
  STACKTRC_RETURN;
}



#ifndef DEF_NO_StringUSAGE
static void test_StringScan ( ) {
  STACKTRC_ENTRY("test_StringScan");
  TEST_START("test_StringScan");
  int parsedChars = 0;
  //
  int res = parseIntRadix_emC("2", -1, 10, &parsedChars, null);
  CHECK_TRUE(res==2 && parsedChars==1, "2 as simple number");
  //
  res = parseIntRadix_emC("x", -1, 10, &parsedChars, null);
  CHECK_TRUE(res==0 && parsedChars==0, "no simple number found");
  //
  res = parseIntRadix_emC("23.3", -1, 10, &parsedChars, null);
  CHECK_TRUE(res=23 && parsedChars==2, "23 as simple number");
  //
  res = parseIntRadix_emC("cafe02", -1, 16, &parsedChars, null);
  CHECK_TRUE(res==0xcafe02 && parsedChars==6, "cafe02 as hex number");
  //
  res = parseIntRadix_emC("0x67cafe05", 10, 10, &parsedChars, "x");
  CHECK_TRUE(res==0x67cafe05 && parsedChars==10, "0xcafe02 as hex number");
  //
  res = parseIntRadix_emC("0234ca", -1, 10, &parsedChars, "x");
  CHECK_TRUE(res==234 && parsedChars==4, "0234ca not as hex number, only 0234");
  //
  res = parseIntRadix_emC(" 05 fe'33x", -1, 16, &parsedChars, " ' ");
  CHECK_TRUE(res==0x5fe33 && parsedChars==9, " 05 fe'33 hex number with separators");
  //
  res = parseIntRadix_emC("3b-2d-0x", -1, 16, &parsedChars, "0-");  //do not write "-" on first position
  CHECK_TRUE(res==0x3b2d0 && parsedChars==7, "3b-2d-0 hex number with - separation");
  //
  res = parseIntRadix_emC("-0x2345-45", -1, 10, &parsedChars, "-x");
  CHECK_TRUE(res==-0x2345 && parsedChars==7, "-0x2345-45 exclusively the -45, 7 chars");
  //
  res = parseIntRadix_emC(" - 2'123.01 ", -1, 10, &parsedChars, "- '");
  CHECK_TRUE(res==-2123 && parsedChars==8, " - 2'123.01 - 8 chars");
  //
  TEST_END;
  STACKTRC_RETURN;
}
#endif //DEF_NO_StringUSAGE




void test_getCharConst_StringJc() {
  STACKTRC_ENTRY("test_getCharConst_StringJc");
  TEST_START("test_getCharConst_StringJc");

  char const* scLit1 = getCharConst_StringJc(sLit1, null, 0);
  CHECK_TRUE(scLit1 == sLit1.addr.str, "getCharConst_StringJc(...) for a 0-terminated simple String does not need a buffer");

  #ifdef DEF_CharSeqJcCapabilities
  char buffer[100];                    // a buffer in stack for the 0-terminated String
  StringJc exampleCharSeq = getExample_CharSeqJc();
  char const* exampleCharSeq0 = getCharConst_StringJc(exampleCharSeq, buffer, sizeof(buffer));
  #endif

  TEST_END;
  STACKTRC_RETURN;
}



void test_StringBase_emC ( )
{

  testSimple_StringJc();
  #ifndef DEF_NO_StringUSAGE
  test_StringScan();
  #endif
  test_StringCmp();
  test_StringCpy();

}