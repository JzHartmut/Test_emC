

#include <org/vishia/emC/Base/test_Stacktrc_Exc/testLongJmp.h>

#include <setjmp.h>
#include <stdio.h>

static jmp_buf jmp1;


static void subroutine2(){

  longjmp(jmp1, 12);

}

static void subroutine1(){

  subroutine2();

}



void testLongjmp() {
  int jmpresult; 
  if( (jmpresult = setjmp(jmp1))==0) {
    printf("continue\n");
    subroutine1();
    printf("not continue\n");
  } else {
    printf("after longjmp: %d\n", jmpresult);
  }
}

