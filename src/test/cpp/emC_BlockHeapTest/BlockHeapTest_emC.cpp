#include <applstdef_emC.h>
#ifdef USE_BlockHeap_emC
#include "BlockHeapTest_emC.h"
#include <emC/Base/String_emC.h>

#include <emC/BlockHeap/BlockHeapJc_admin.h>
#include <emC/Test/testAssert.h>


BlockHeap_emC_s blockheap = INIZ_BlockHeap_emC(blockheap);

void testBlockHeap_emC(){
  STACKTRC_ENTRY("testBlockHeap_emC");
  TEST_START("BlockHeap_emC");
  ObjectJc* data1 = null;
  MemC memBh; 
  TRY {
    ALLOC_MemC(memBh, 0x2200);
    ctorO_BlockHeap_emC(&blockheap.base.object, memBh, 0x400, 0x40);

    int nrofFree1 = nrofFreeBlocks_BlockHeap_emC(&blockheap);
    //should be alloc in the standard heap, not in block heap, because startup mode:
    data1 = alloc_ObjectJc(100, 0, _thCxt);
    int nrofFree2 = nrofFreeBlocks_BlockHeap_emC(&blockheap);
    TEST_TRUE(nrofFree2 == nrofFree1, "has allocate in system heap on startup");
  

    setRunModeAll_BlockHeap_emC();
    ObjectJc* data2 = alloc_ObjectJc(100, 0, _thCxt);
    nrofFree2 = nrofFreeBlocks_BlockHeap_emC(&blockheap);
    TEST_TRUE(nrofFree2 == (nrofFree1-1), "has allocate in BlockHeap after setRunMode");

    free_MemC(data2);  //frees a block in blockheap
    nrofFree2 = nrofFreeBlocks_BlockHeap_emC(&blockheap);
    TEST_TRUE(nrofFree2 == nrofFree1, "all blocks are freed in BlockHeap");

  }_TRY
  CATCH(Exception, exc) {
    TEST_EXC(exc); // << getMessage_ExceptionJc(exc);
  }
  END_TRY;

  free_MemC(data1);  //frees allocated in heap
  FREE_MemC(memBh);  //frees the whole BlockHeap memory
  STACKTRC_LEAVE;
}
#else //not USE_BlockHeap_emC

void testBlockHeap_emC(){} //empty

#endif //USE_BlockHeap_emC
