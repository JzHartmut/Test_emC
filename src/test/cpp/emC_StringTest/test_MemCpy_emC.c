#include <emC_StringTest/test_MemCpy_emC.h>
#include <emC/Base/StringPacked_emC.h>

#include <string.h>  //memcpy


void doMemcpy(volatile TestMemCpy_s* data) {
  memcpy((void*)&data->dst[1], (void*)data->src, sizeof(data->src));
}

void doStringPackedCpy(volatile TestMemCpy_s* data) {
  bytecpyPacked_emC((int*)&data->dst[1], 0, (int*)data->src, 0, sizeof(data->src));

}