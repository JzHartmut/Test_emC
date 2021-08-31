#include <applstdef_emC.h>
#include <emC_StringTest/test_StringSpecials_emC.h>
#include <emC/Base/Time_emC.h>
#include <emC/Base/StringBase_emC.h>
#include <emC/Base/StringPacked_emC.h>
#include <emC/Test/testAssert.h>
#include <emC_StringTest/test_MemCpy_emC.h>
#include <stdio.h>
#include <string.h>  //memcpy

extern const char4_emC sIdentification[];
const char4_emC sIdentification[] = { CHAR4_emC('I','d','e','n'), CHAR4_emC('t','\0','\0','\0')};


StringJc testStringRet_intern(){
  StringJc ret; // = INIZ_StringJc("Test", 4);
  ret.addr.str = "Test";
  ret.val = 4;
  return ret;
}


int testStringRet  (  ){
  StringJc s1 = testStringRet_intern();
  int length;
  char const* c1 = getCharsAndLength_StringJc(&s1, &length);
  return *c1;
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


volatile TestMemCpy_s testMemCpy = {
  'd'
, { CHAR4_emC( 'a', 'a', 'b', 'b'), CHAR4_emC( 'c', 'c', 'd', 'd'), CHAR4_emC( 'e', 'e', 'f', 'f') }
, { 'd', 'd' }
, { CHAR4_emC( 'A', 'A', 'B', 'B'), CHAR4_emC( 'C', 'C', 'D', 'D'), CHAR4_emC( 'E', 'E', 'F', 'F'), CHAR4_emC( 'G', 'G', 'H', 'H'), CHAR4_emC( 'I', 'I', 'J', 'J') }
, 'x'
};




void testMemcpy() {
  
  TimeAbs_emC timeStart, timeEnd;

  setCurrent_TimeAbs_emC(&timeStart);
  int nLoop = 1000;
  for(int ix = 0; ix < nLoop; ++ix) {  //on PC, 3.2 GHz
    doMemcpy(&testMemCpy);  //It needs about 0.23 �s for 12000 Bytes, 20 ps per byte.
  }                         //no optimization because volatile, other source. Only possible with 
  setCurrent_TimeAbs_emC(&timeEnd);   //DMA access 160 ps = 0.16 ns for 64 bit in internal chached RAM. 
  float calctime = (float)diffMicroSec_TimeAbs_emC(&timeEnd, &timeStart);
  printf("memcpy %2.5f us\n", calctime / nLoop);

  setCurrent_TimeAbs_emC(&timeStart);
  nLoop = 1000;
  for(int ix = 0; ix < nLoop; ++ix) {  //it needs 20 �s for 12000 Bytes with 32-bit-access,
    doStringPackedCpy(&testMemCpy);    //6 ns to handle one Memory word.  
  }                                    //on embedded hardware doStringPackedCpy and memcpy may be more adequate.
  setCurrent_TimeAbs_emC(&timeEnd);
  calctime = (float)diffMicroSec_TimeAbs_emC(&timeEnd, &timeStart);
  printf("memcpy %2.5f us\n", calctime / nLoop);

}



//Note: This test runs only on a machine which can access bytes with one address in memory.
//Because it is especially for machines which accesses more as one byte in one memory,
//Test it under PC conditions and test the priciple in a more-byte-addressing machine.
void testStringPacked() {

  TEST_START("testStringPacked");                //initialize with a compact String
  int32 src[3] = { CHAR4_emC( 'a', 'a', 'b', 'b'), CHAR4_emC( 'c', 'c', 'd', 'd'), CHAR4_emC( 'e', 'e', 'f', 'f') };
  int32 dst[5];                                  //initialize with a compact String  
  int32 dstOrig[5] = { CHAR4_emC( 'A', 'A', 'B', 'B'), CHAR4_emC( 'C', 'C', 'D', 'D'), CHAR4_emC( 'E', 'E', 'F', 'F'), CHAR4_emC( 'G', 'G', 'H', 'H'), CHAR4_emC( 'I', 'I', 'J', '\0') }  ;

  char cmp[sizeof(int32)*5];
  char msgTest[40];

  char* dstc;
  int res;

  uint ixByteSrc =0;
  uint ixByteDst = 0;
  uint zBytes = 1;
  for(ixByteSrc = 0; ixByteSrc < 5; ++ixByteSrc) {
    for(ixByteDst = 0; ixByteDst < 5; ++ixByteDst) {
      for(zBytes = 0; zBytes < 5; ++zBytes) {
        if(  (ixByteSrc + zBytes) <= (sizeof(src)*BYTE_IN_MemUnit)
          && (ixByteDst + zBytes) <= (sizeof(dst)*BYTE_IN_MemUnit)
          ) {
            memcpy(dst, dstOrig, sizeof(dst));
            bytecpyPacked_emC(dst, ixByteDst, src, ixByteSrc, zBytes);
            memcpy(cmp, dstOrig, sizeof(cmp));
            memcpy(cmp+ixByteDst, ((char*)src) + ixByteSrc, zBytes);
            dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
            res = strncmpPacked_emC(dstc, cmp, sizeof(dst)*BYTE_IN_MemUnit);    //"aABBCCDDEEFFGGHHIIJJKKLL"
            if(res !=0) {
              res +=0;
              memcpy(dst, dstOrig, sizeof(dst));
              bytecpyPacked_emC(dst, ixByteDst, src, ixByteSrc, zBytes);
            }
            sprintf(msgTest, "dst:%d, src:%d, zChar:%d", ixByteSrc, ixByteDst, zBytes);
            CHECK_TRUE(res ==0, msgTest);
  } } } }
   
  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 0, src, 0, 2);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "aaBBCCDDEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:0, src:0, , dste:2, srce:2");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 0, src, 0, 4);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "aabbCCDDEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:0, src:0, , dste:4, srce:4");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 0, src, 0, 7);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "aabbccdDEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:0, src:0, , dste:7, srce:7");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 1, src, 0, 1);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "AaBBCCDDEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:1, src:0, , dste:2, srce:1");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 1, src, 0, 2);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "AaaBCCDDEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:1, src:0, , dste:3, srce:2");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 1, src, 0, 4);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "AaabbCDDEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:1, src:0, , dste:5, srce:4");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 1, src, 0, 7);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "AaabbccdEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:1, src:0, , dste:8, srce:7");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 4, src, 0, 7);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "AABBaabbccdFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:4, src:0, , dste:11, srce:7");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 2, src, 1, 9);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "AAabbccddeeFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:2, src:1, dste:9, srce:8");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 1, src, 2, 7);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "AbbccddeEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:1, src:2, dste:8, srce:9");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 0, src, 2, 7);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "bbccddeDEEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:0, src:2, dste:7, srce:9");

  memcpy(dst, dstOrig, sizeof(dst));
  bytecpyPacked_emC(dst, 1, src, 2, 8);
  dstc = (char*)dst;          //"AABBCCDDEEFFGGHHIIJJKKLL"
  res = strncmpPacked_emC(dstc, "AbbccddeeEFFGGHHIIJJKKLL", 16);
  CHECK_TRUE(res ==0, "dst:1, src:2, dste:8, srce:9");


  TEST_END;


}


void testStringSpecial_emC() {
  testMemcpy();
  testStringPacked();

}

void testString_emC ( ){
  test_searchChar();
  //testStringRet();
}
