#ifndef HGUARD_Test_RingBuffer_emC
#define HGUARD_Test_RingBuffer_emC
#include <applstdef_emC.h>

extern_C void testRingBufferSimpleOneThread ( );

extern_C void testRingBufferMultiThread ( int delayTimeInRingBufferCmpAndSwap);

#endif //HGUARD_Test_RingBuffer_emC
