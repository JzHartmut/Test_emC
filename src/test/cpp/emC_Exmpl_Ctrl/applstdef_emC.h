
//#define DEF_REFLECTION_OFFS
#define SIZEBLOCK_BlockHeap_emC 0x400
#if defined(DEF_REFLECTION_OFFS)
#include <emC_inclApplSpec/TargetNumericSimple/applstdef_emC.h>
#elif defined(DEF_REFLECTION_FULL)
#include <emC_inclApplSpec/applC32_emC/applstdef_emC.h>
#else
#error undefined
#endif
