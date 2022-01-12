#include "emC_Test_Ctrl/test_Ctrl_emC.h"
#include <emC/Ctrl/PIDf_Ctrl_emC.h>
#include <emC/Ctrl/PIDi_Ctrl_emC.h>
#include <emC/Ctrl/T1_Ctrl_emC.h>
#include <emC/OSAL/os_file.h>
#include <stdio.h>


template<class PIDxCtrl> class Test_PIDxCtrl {

  PIDxCtrl pid = 0;
};


#define INIZ_DEFemC(NAME) INIZ_##NAME

#define PIDx_Ctrl_emC PIDf_Ctrl_emC
#define PIDx_Ctrl_emC_s PIDf_Ctrl_emC_s 
#define INIZ_PIDx_Ctrl_emC INIZ_DEFemC(PIDf_Ctrl_emC)


typedef struct Data_T {
  Par_PIDf_Ctrl_emC_s parPid;
  PIDf_Ctrl_emC_s pid;
  Par_PIDi_Ctrl_emC_s parPid16, parPid32;
  PIDi_Ctrl_emC_s pid16, pid32;


  /**A smoothing block for the D-part*/
  T2f_Ctrl_emC_s dxs;

  /**A delay FBlock. Note: The float array should follow immediately. See ctor_Delayf_Ctrl_emC. */
  Delayf_Ctrl_emC_s delayx; float _delayxValues[18];

  SmoothGainf_Ctrl_emC_s gains_dx;
} Data_s;

#define INIZ_Data(THIZ) { \
  INIZ_Par_PIDf_Ctrl_emC(THIZ.parPid, 0) \
, INIZ_PIDf_Ctrl_emC(THIZ.pid, 0) \
, INIZ_Par_PIDi_Ctrl_emC(THIZ.parPid, 0) \
, INIZ_Par_PIDi_Ctrl_emC(THIZ.parPid, 0) \
, INIZ_PIDi_Ctrl_emC(THIZ.pid, 0) \
, INIZ_PIDi_Ctrl_emC(THIZ.pid, 0) \
, {0} \
, INIZ_Delayf_Ctrl_emC(THIZ.delayx, 0) \
, INIZ_SmoothGainf_Ctrl_emC(THIZ.delayx, 0) \
}

static Data_s* ctor_Data(void* ram, uint size) {
  ASSERT_emC(size >= (uint)sizeof(Data_s), "size faulty", size, sizeof(Data_s));
  Data_s* thiz = C_CAST(Data_s* ,ram);          //== Initialize the members:
  CTOR_ObjectJc( &thiz->parPid.base.obj, &thiz->parPid, sizeof(thiz->parPid), refl_Par_PIDf_Ctrl_emC, 0);
  CTOR_ObjectJc( &thiz->pid.base.obj, &thiz->pid, sizeof(thiz->pid), refl_PIDf_Ctrl_emC, 0);
  return thiz;
}


//tag::calcSomePIDiParam[]
/**This routine prints some results for kI and fI for the integer PID integrator. */
static void calcSomePIDiParam ( ) {
  //Note: current dir is the IDE project dir
  int sizeData = sizeof(Data_s);
  Data_s* thiz = ctor_Data(alloc_MemC(sizeData), sizeData);
  ASSERTs_emC(sizeof(thiz->pid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
  ASSERTs_emC(sizeof(thiz->parPid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
  float Tctrl = 0.001f;
  ctor_Par_PIDf_Ctrl_emC(&thiz->parPid.base.obj, 0.002f);
  ctor_PIDf_Ctrl_emC(&thiz->pid.base.obj, Tctrl);
  ctor_T2f_Ctrl_emC(&thiz->dxs);
  ctor_Delayf_Ctrl_emC(&thiz->delayx.base.obj, 20, sizeof(thiz->delayx) + sizeof(thiz->_delayxValues));
  ctor_SmoothGainf_Ctrl_emC(&thiz->gains_dx.base.obj, 0.005f, 0, Tctrl);

  float valrangeBitsiA[][2] = 
  { { 1000.0f, 16}
  , { 1000.0f, 32}
  , { 10000.0f, 16}
  , { 10000.0f, 32}
  #if (INT_NUM_NROFBITS ==32)
  , { 32767.0f, 16}
  , { 32767.0f, 32}
  , { 100000.0f, 32} 
  #endif
  };
  for(uint ixrange = 0; ixrange < ARRAYLEN_emC(valrangeBitsiA); ++ixrange) {
    float valrange = valrangeBitsiA[ixrange][0];
    int bitsi = (int)valrangeBitsiA[ixrange][1];
    #if (INT_NUM_NROFBITS ==16)
      char const* sfoutm = "../../../src/test/out/Test_Ctrl/pidiParam16_%d_%3.0f.csv"; //"$TMP/pidiParam.csv";
    #else
      char const* sfoutm = "../../../src/test/out/Test_Ctrl/pidiParam32_%d_%3.0f.csv"; //"$TMP/pidiParam.csv";
    #endif
    char sfout[100]; sprintf(sfout, sfoutm, bitsi, valrange);  //build file name 
    OS_HandleFile hcsv = os_fopenToWrite(sfout, false);
    ASSERT_emC(hcsv !=null, sfout, 0, 0);
    FILE* fout = getFILE_os_file_emC(hcsv); //fopen("d:\\vishia\\Java\\cmpnJava_vishiaGui\\src\\appl\\CurveView\\data2.csv", "wb");

    float Td = 0;
    int dti = 1;

    float param[][2] = {
      // kP        Tn [ms] for Tctrl = 1 ms
      { 0.1f     , 0.016f   }
    , { 0.2f     , 0.016f   }
    , { 0.5f     , 0.016f   }
    , { 1.0f     , 0.016f   }
    , { 1.1f     , 0.016f   }
    , { 2.0f     , 0.016f   }
    , { 5.0f     , 0.016f   }
    , { 10.0f    , 0.016f   }
    , { 20.0f    , 0.016f   }
    , { 1.0f     , 0.001f   }
    , { 1.0f     , 0.002f   }
    , { 1.0f     , 0.003f   }
    , { 1.0f     , 0.005f   }
    , { 1.0f     , 0.020f   }
    , { 1.0f     , 0.021f   }
    , { 1.0f     , 0.022f   }
    , { 1.0f     , 0.100f   }
    , { 1.0f     , 1.0f     }
    , { 1.0f     , 2.0f     }
    , { 1.0f     , 10.0f    }
    , { 1.0f     , 90.0f    }
    , { 0.2f     , 0.05f    }
    , { 10.0f    , 0.05f    }
    , { 0.2f     , 50.0f    }
    , { 10.0f    , 50.0f    }
    };
    init_Par_PIDi_Ctrl_emC(&thiz->parPid32, Tctrl, (int)valrange, bitsi, 1.0f, 0.1f, Td, dti, false, false);
    init_PIDi_Ctrl_emC(&thiz->pid32, &thiz->parPid32);
    fprintf(fout, "bits numeric:%d; bits intermediate:%d; value range Y:%d= %8.8X, nShy=%d\n"
          , INT_NUM_NROFBITS, bitsi, (int32)(valrange), thiz->pid32.yLim, thiz->parPid32.f12[0].nShy);
    for(uint ix = 0; ix < ARRAYLEN_emC(param); ++ix) {
      float kP = param[ix][0];
      float Tn = param[ix][1];
      set_Par_PIDi_Ctrl_emC(&thiz->parPid32, kP, Tn, Td, dti, false);
      reset_Par_PIDi_Ctrl_emC(&thiz->parPid32, true);
      if (bitsi==16) {                      //cannot run step16 on 32 bit type
        step16_PIDi_Ctrl_emC(&thiz->pid32, 1, 0x0);
      } else {
        step32_PIDi_Ctrl_emC(&thiz->pid32, 1, 0x0);
      }
      reset_Par_PIDi_Ctrl_emC(&thiz->parPid32, false);
      if (bitsi==16) {                      //cannot run step16 on 32 bit type
        step16_PIDi_Ctrl_emC(&thiz->pid32, 1, 0x0);
      } else {
        step32_PIDi_Ctrl_emC(&thiz->pid32, 1, 0x0);
      }
      //int fI16 = thiz->parPid16.f->fI;
      //int fI32 = thiz->parPid32.f->fI;
      fprintf(fout, "kP=%4.1f; Tn=%6.3f; nShP=%2d; kP=%4.4X; wxLim=%4.8X; shI=%2d; fI=%8.8X;"
       , kP, Tn, thiz->parPid32.f->nShP, thiz->parPid32.f->fP, thiz->parPid32.f->wxlim
       , thiz->parPid32.f->nShKI, thiz->parPid32.f->fI); 
      fprintf(fout, "P=%4.4X; I=%8.8X;\n"
             , thiz->pid32.wxP, thiz->pid32.qI);
    }
    fclose(fout);
  }
}
//end::calcSomePIDiParam[]






static void testLim_PIDf ( ) {

  OS_HandleFile hcsv = os_fopenToWrite("$TMP/curvieViewData/data2.csv", false);
  ASSERT_emC(hcsv !=null, "File error $TMP/curvieViewData/data2.csv", 0, 0);
  FILE* fval = getFILE_os_file_emC(hcsv); //fopen("d:\\vishia\\Java\\cmpnJava_vishiaGui\\src\\appl\\CurveView\\data2.csv", "wb");
  fprintf(fval, "timesh; time_ms; x; y; yp; yi; yd; x16; y16; yp16; yi16; yd16; x32; y32; yp32; yi32; yd32;\n");
  //Data_s datalocal = INIZ_Data(datalocal);
  //Data_s* thiz = &datalocal;
  int sizeData = sizeof(Data_s);
  Data_s* thiz = ctor_Data(alloc_MemC(sizeData), sizeData);
  ASSERTs_emC(sizeof(thiz->pid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
  ASSERTs_emC(sizeof(thiz->parPid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
  float Tctrl = 0.000050f;
  ctor_Par_PIDf_Ctrl_emC(&thiz->parPid.base.obj, 0.002f);
  ctor_PIDf_Ctrl_emC(&thiz->pid.base.obj, Tctrl);
  ctor_T2f_Ctrl_emC(&thiz->dxs);
  ctor_Delayf_Ctrl_emC(&thiz->delayx.base.obj, 20, sizeof(thiz->delayx) + sizeof(thiz->_delayxValues));
  ctor_SmoothGainf_Ctrl_emC(&thiz->gains_dx.base.obj, 0.005f, 0, Tctrl);

  float valrange = 1000.0f;
  float xquant = 2000.0f;  // build input signal with this ADC resolution (quantization)
  int ndxDelay = 0;         // 0: smooth D-part, 1..31 use delayed values  
  //float kP = 6.0f, Tn = 0.005f, Td = 0.001f; ndxDelay = 15;
  float kP = 30.0f, Tn = 0.005f, Td = 0.001f; ndxDelay = 1;
  //float kP = 4.0f, Tn = 0.004f, Td = 0;
  float dt = ndxDelay ==0 ? Tctrl : ndxDelay * Tctrl;
  int dti = ndxDelay ==0 ? 1 : ndxDelay;
  float Tsd1 = 0.000000f, Tsd2 = 0.000450f;    //time only for smoothed D-input 
  float fT1 = 0.01f, fT2 = 0.05f, fT3 = 0.1f;  //Ts = 5 ms, 1 ms, 0.5 ms
  int bonly_xdx = 0;        // select, use x or w-x for D-part.
  init_Par_PIDf_Ctrl_emC(&thiz->parPid, 0.000050f, valrange, kP, Tn, Td, dt, false, false);
  init_PIDf_Ctrl_emC(&thiz->pid, &thiz->parPid);
  //Calculate some more variants with Tn
  init_Par_PIDi_Ctrl_emC(&thiz->parPid16, 0.000050f, (int)valrange, 16, kP, Tn, Td, dti, false, false);
  init_Par_PIDi_Ctrl_emC(&thiz->parPid32, 0.000050f, (int)valrange, 32, kP, Tn, Td, dti, false, false);
  //
  init_PIDi_Ctrl_emC(&thiz->pid16, &thiz->parPid16);
  init_PIDi_Ctrl_emC(&thiz->pid32, &thiz->parPid32);
  param_T2f_Ctrl_emC(&thiz->dxs, Tsd1, Tsd2, Tctrl);
  setLim_PIDf_Ctrl_emC(&thiz->pid, valrange);
  int nStep = 0;
  float xEnv[3][3] = {0};
  float ypid[3];
  float wCtrl = 0; 
  while(++nStep <1600) {
    //float wx = 0.1f; 
    if(nStep == 50) { 
      wCtrl = 950; 
    }
    else if(nStep == 1200) { 
      memset(xEnv, 0, sizeof(xEnv)); //cause a terrible disturbation, look what's happen
      //wCtrl = 950; 
    }
    else if(nStep == 390) { 
      wCtrl += 0; 
    }
    float xEnvADCf = ((int)(xquant*(xEnv[0][0])/valrange + 0.5f ) / xquant ) * valrange;
    int xEnvADC16 = (int)(((int)(xquant*(xEnv[1][0])/valrange + 0.5f ) / xquant ) * valrange);
    int xEnvADC32 = (int)(((int)(xquant*(xEnv[2][0])/valrange + 0.5f ) / xquant ) * valrange);
    float wx = wCtrl - xEnvADCf;
    float dx;
    float xdx = bonly_xdx ? xEnvADCf : wx;
    if(ndxDelay >0) {
      float xdxz = step_Delayf_Ctrl_emC(&thiz->delayx, ndxDelay, xdx);
      dx = xdx - xdxz;                           // dx from delayed input
    } else {
      step_T2f_Ctrl_emC(&thiz->dxs, xdx);        // smooth the input for D
      dx = thiz->dxs.dx;
    }
    //dx = step_SmoothGainf_Ctrl_emC(&thiz->gains_dx, dx, 1.0f, 0.0f, 1.5f * valrange/xquant);
    ypid[0] = step_PIDf_Ctrl_emC(&thiz->pid, wx, dx);
    int wx16 = (int)wCtrl - xEnvADC16;
    ypid[1] = (float)step16_PIDi_Ctrl_emC(&thiz->pid16, (int)wx16, (int)(dx));
    int wx32 = (int)wCtrl - xEnvADC32;
    ypid[2] = (float)step32_PIDi_Ctrl_emC(&thiz->pid32, (int)wx32, (int)(dx));
    
    for(int ix = 0; ix <3; ++ix) {
      xEnv[ix][1] += fT1 * (ypid[ix] - xEnv[ix][1]);
      xEnv[ix][2] += fT2 * (xEnv[ix][1] - xEnv[ix][2]);
      xEnv[ix][0] += fT3 * (xEnv[ix][2] - xEnv[ix][0]);
    }
    printf("%d y=%1.5f yp=%1.5f yi=%1.5f yd=%1.5f\n"
    , nStep, ypid[0]
    , thiz->pid.wxP
    , thiz->pid.yIntg
    , thiz->pid.dxP);  

    int nShwxP = 3 + (INT_NUM_NROFBITS -16);
    fprintf(fval, "%5d; %2.3f; %3.3f; %3.3f; %3.3f; %3.3f; %3.5f; %3.5f; %d; %d; %d; %d; %3.5f; %d; %d; %d; %d; \n"
    , nStep, nStep*0.05f
    , xEnv[0][0], ypid[0], thiz->pid.wxP, thiz->pid.yIntg, thiz->pid.dxP
    , xEnv[1][0], thiz->pid16.y, thiz->pid16.wxP>>3, thiz->pid16.qI >>19, thiz->pid16.dxP>>3
    , xEnv[2][0], thiz->pid32.y, thiz->pid32.wxP>>nShwxP, thiz->pid32.qI >>19, thiz->pid32.dxP>>nShwxP
    );
  }
  fclose(fval);
  free_MemC(thiz);
}

PIDf_Ctrl_emC pid(0, 0.000050f);


class DataCpp {
  PIDf_Ctrl_emC pid;
  Par_PIDf_Ctrl_emC parPid;

  public: DataCpp(); 
};


DataCpp::DataCpp() 
: pid(123, 0.000050f)
, parPid(122, 0.001f, 12.0f)
{
}

DataCpp myDataCpp();

DataCpp* myDataRef;




void testCpp ( ) {

  myDataRef = new DataCpp();
}




void test_PIDf_Ctrl_emC ( ) {
  calcSomePIDiParam();
  testLim_PIDf();

}


