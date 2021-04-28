#include <emC_Test_Math/Test_Math_emC.h>
#include <emC/Base/Math_emC.h>
#include <applstdef_emC.h>
#include <math.h>
#include <stdio.h>

//Note: This second file is to prevent optimizing a whole sub routine 
//if the compiler detects with its optimizing level, that the result is contant. 
//Using another compilation unit, the compiler cannot detect this unexpected optimizing.

//Results32_Test_Math_emC_s results = {0};

/**This table contains some 16 bit values to multiply 
 * and the signed and unsigned result in 32 bit.
 * It is used also to test mulx32hi_emC and mul32lo_emC.
 * The a, b values for mulx32hi are left shifted to the hi word (0x40000000 etc) 
 * The expected result in the hi part is the same as 16 * 16 bit to 32 bit.
 * The result for mul32lo_emC is the same as 16 * 16 bit 
 * if the inputs are expanded with the correct sign. 
 * For example as for the first line:
 * 0x00004000 * 0xffffffff => 0xffffc000 
 * 0x00004000 * 0x0000ffff => 0x3fffc000 
 * Note: The high part of mul32lo_emC is different, but it is not used. 
 */
static Test_Data16_Math_emC_s val16[] = 
 // a       b       int32 r     uint32     uint32lo result
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


Test_Data16_Math_emC_s addsat_data[] = {
                  // adds    addu    subu
  { 0x7ffe,      1, 0x7fff, 0x7fff, 0x7ffd }  //without sat 
, { 0x7ffe,      2, 0x7fff, 0x8000, 0x7ffc }  //sat for signed
, { 0x8001,      2, 0x8003, 0x8003, 0x7fff }  //sat for signed, but also sat for unsigned 
, { 0x8001, 0xfffe, 0x8000, 0xffff, 0      }  //sat for signed, but also sat for unsigned 
, { 0xffff,      2, 0x0001, 0xffff, 0xfffd }  //sat for signed, but also sat for unsigned 
, { 0xffff, 0xfffe, 0xfffd, 0xffff, 0x0001 }  //sat for signed, but also sat for unsigned 
, { 0x0001, 0x7fff, 0x7fff, 0x8000, 0x0    }  //sat for signed, but also sat for unsigned 
, { 0x0001,      2, 0x0003, 0x0003, 0x0    }  //sat for signed, but also sat for unsigned 
};

int test_Math_emC ( ) {
  int ret = 0;            //only given to prevent optimization because unused code
  ret += test_AddSat_Math_emC(addsat_data, ARRAYLEN_emC(addsat_data));
  ret += testMult16_Math_emC( val16, ARRAYLEN_emC(val16));
  ret += testMult32Lo_Math_emC( val16, ARRAYLEN_emC(val16));
  ret += testMult32_Math_emC(val16, ARRAYLEN_emC(val16));
  ret += test_sqrt16(false);
  ret += test_rsqrt2_32(false);
  ret += test_Nom_int16_complex();
  ret += test_cos16(false);
  ret += test_sin16();
  ret += test_atan2nom16_MathemC(false, 1);
  return ret;
}
