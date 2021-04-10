#include <emC_Test_Math/Test_Math_emC.h>
#include <emC/Base/Math_emC.h>
#include <applstdef_emC.h>
#include <math.h>
#include <stdio.h>

//Note: This second file is to prevent optimizing a whole sub routine 
//if the compiler detects with its optimizing level, that the result is contant. 
//Using another compilation unit, the compiler cannot detect this unexpected optimizing.

Results32_Test_Math_emC_s results = {0};

Test_Mult16_Math_emC_s val16[16] = 
 // a       b       int32 r     uint32 result
{ { 0x4000, 0xffff, 0xffffc000, 0x3fffc000 } //0
, { 0x7fff, 0xffff, 0xffff8001, 0x7ffe8001 } //1
, { 0xc000, 0xffff, 0x00004000, 0xbfff4000 } //2
, { 0x8000, 0xffff, 0x00008000, 0x7fff8000 } //3
, { 0x0001, 0xffff, 0xffffffff, 0x0000ffff } //4
, { 0xffff, 0xffff, 0x00000001, 0xfffe0001 } //5
, { 0x4000, 0x7fff, 0x1fffc000, 0x1fffc000 } //6
, { 0x7fff, 0x7fff, 0x3fff0001, 0x3fff0001 } //7
, { 0xc000, 0x7fff, 0xe0004000, 0x5fff4000 } //8
, { 0x8000, 0x7fff, 0xc0008000, 0x3fff8000 } //9
, { 0x0001, 0x7fff, 0x00007fff, 0x00007fff } //10
, { 0xffff, 0x7fff, 0xffff8001, 0x7ffe8001 } //11
, { 0x4000, 0x0001, 0x00004000, 0x00004000 } //12
, { 0xc000, 0x4000, 0xF0000000, 0x30000000 } //13
, { 0x4000, 0xc000, 0xF0000000, 0x30000000 } //14
, { 0x4000, 0x8000, 0xE0000000, 0x20000000 } //15
};

static struct Test_Mult32_Math_emC_T {
    uint32 a1;    uint32 a2;  uint32 rss; uint32 rsu; uint32 ruu; } values32[16] = 
{ { 0x40000000, 0xffffffff, 0xffffc000, 0x3fffc000, 0x3fffc000 } //0
, { 0x7fffffff, 0xffffffff, 0xffff8001, 0x7ffe8001, 0x7ffe8001 } //1
, { 0xc0000000, 0xffffffff, 0x00004000, 0xc0004000, 0xbfff4000 } //2
, { 0x80000000, 0xffffffff, 0x00008000, 0x80008000, 0x7fff8000 } //3
, { 0x00000001, 0xffffffff, 0xffffffff, 0x0000ffff, 0x0000ffff } //4
, { 0xffffffff, 0xffffffff, 0x00000001, 0xffff0001, 0xfffe0001 } //5
, { 0x40000000, 0x7fffffff, 0x1fffc000, 0x1fffc000, 0x1fffc000 } //6
, { 0x7fffffff, 0x7fffffff, 0x3fff0001, 0x3fff0001, 0x3fff0001 } //7
, { 0xc0000000, 0x7fffffff, 0xe0004000, 0xe0004000, 0x5fff4000 } //8
, { 0x80000000, 0x7fffffff, 0xc0008000, 0xc0008000, 0x3fff8000 } //9
, { 0x00000001, 0x7fffffff, 0x00007fff, 0x00007fff, 0x00007fff } //10
, { 0xffffffff, 0x7fffffff, 0xffff8001, 0xffff8001, 0x7ffe8001 } //11
, { 0x40000000, 0x00000001, 0x00004000, 0x00004000, 0x00004000 } //12
, { 0xc0000000, 0x40000000, 0xF0000000, 0xF0000000, 0x30000000 } //13
, { 0x40000000, 0xc0000000, 0xF0000000, 0x30000000, 0x30000000 } //14
, { 0x40000000, 0x80000000, 0xE0000000, 0x20000000, 0x20000000 } //15
};


static int testMult32_Math_emC ( ) {
  int err1 = 0, err2=0, err3=0;
  for(int ix=0; ix < ARRAYLEN_emC(values32); ++ix) {
    int32 as = values32[ix].a1;
    int32 bs = values32[ix].a2;
    int32 r1 =  0; //mul32sshi_emC(as, bs);
    uint32 bu = (uint32)bs;
    int32 r2 = 0; //mul32suhi_emC(as, bu);
    uint32 au = (uint32)as;
    uint32 r3 = 0; //mul32uuhi_emC(au, bu);
    if(r1 != values32[ix].rss) {
      err1 +=1;
    }
    if(r2 != values32[ix].rsu) {
      err2 +=1;
    }
    if(r3 != values32[ix].ruu) {
      err3 +=1;
    }
  }    
  int ret = err1 + err2 + err3;
  return ret;
}


int test_Math_emC ( ) {
  int err = 0;
  //test_sqrt16();
  //test_rsqrt2_32();
  test_Nom_int16_complex();
  //test_cos16(false);
  //test_sin16();
  //err += testMult16_Math_emC( val16, ARRAYLEN_emC(val16));
  //err += testMult32_Math_emC();
  return err;
}
