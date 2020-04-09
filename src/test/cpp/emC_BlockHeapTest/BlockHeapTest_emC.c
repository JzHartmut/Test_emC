#include "BlockHeapTest_emC.h"
#include <applstdef_emC.h>
#include <emC/Base/String_emC.h>

#include <emC/BlockHeap/BlockHeapJc_admin.h>

BlockHeap_emC blockheap = INIZ_BlockHeap_emC(&blockheap);

void testBlockHeap_emC(){
  STACKTRC_ENTRY("testBlockHeap_emC");
  MemC memBh; ALLOC_MemC(memBh, 0x2200);
  ctorO_BlockHeap_emC(&blockheap.base.object, memBh, 0x400, 0x40);



  ObjectJc* data1 = alloc_ObjectJc(100, 0, _thCxt);
  

  setRunModeAll_BlockHeap_emC();
  ObjectJc* data2 = alloc_ObjectJc(100, 0, _thCxt);

  free_MemC(data1);
  free_MemC(data2);

  STACKTRC_LEAVE;
}
