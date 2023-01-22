#include "emC_Test_Ctrl/test_Ctrl_emC.h"
#include <emC/Ctrl/PIDf_Ctrl_emC.h>
#include <emC/Ctrl/PIDi_Ctrl_emC.h>
#include <emC/Ctrl/T1_Ctrl_emC.h>
#include <emC/OSAL/os_file.h>
#include <emC/Base/MemC_emC.h>
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
  STACKTRC_ENTRY("calcSomePIDiParam");
  TRY {
    int sizeData = sizeof(Data_s);
    Data_s* thiz = ctor_Data(alloc_MemC(sizeData), sizeData);
    ASSERT_emC(sizeof(thiz->pid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
    ASSERT_emC(sizeof(thiz->parPid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
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
    //, { 32767.0f, 16}    //?? think about
    , { 32767.0f, 32}
    , { 100000.0f, 32} 
    #endif
    };
    for(uint ixrange = 0; ixrange < ARRAYLEN_emC(valrangeBitsiA); ++ixrange) {
      TRY {
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
          TRY {
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
          }_TRY
          CATCH(Exception, exc) {
            fprintf(fout, "error\n");
          }
          END_TRY;
        }
        fclose(fout);
      }_TRY
      CATCH(Exception, exc) {
        char buffer[300] = { 0 };
        writeException(buffer, sizeof(buffer), exc, __FILE__, __LINE__, _thCxt);
        printf(buffer);
      }
      END_TRY;
    }
  }_TRY
  CATCH(Exception, exc) {
    char buffer[300] = { 0 };
    writeException(buffer, sizeof(buffer), exc, __FILE__, __LINE__, _thCxt);
    printf(buffer);
  }
  END_TRY;
  STACKTRC_LEAVE;
}
//end::calcSomePIDiParam[]


typedef struct Param_Test_PID_T {
  float valrange;
  float xquant;  // build input signal with this ADC resolution (quantization)
  int ndxDelay;         // 0: smooth D-part, 1..31 use delayed values  
  //float kP = 6.0f, Tn = 0.005f, Td = 0.001f; ndxDelay = 15;
  float kP, Tn, Td;
  //float kP = 4.0f, Tn = 0.004f, Td = 0;
  float dt;
  int dti;
  float Tsd1, Tsd2;    //time only for smoothed D-input 
  float fT1, fT2, fT3;  //Ts = 5 ms, 1 ms, 0.5 ms
  int bonly_xdx;        // select, use x or w-x for D-part.
} Param_Test_PID;



static void testLim_PIDf ( char const* sFile, Param_Test_PID* param ) {
  STACKTRC_ENTRY("testLim_PIDf");
  int nStep = 0;
  char path[120] = {0};
    TRY {
    int pathix = strcpy_emC(path, "$TMP/curveViewData/", 120);
    strcpy_emC(path + pathix, sFile, 120 - pathix); 
    OS_HandleFile hcsv = os_fopenToWrite(path, false);
    ASSERT_emC(hcsv !=null, "File error $TMP/curveViewData/data2.csv", 0, 0);
    FILE* fval = getFILE_os_file_emC(hcsv); //fopen("d:\\vishia\\Java\\cmpnJava_vishiaGui\\src\\appl\\CurveView\\data2.csv", "wb");
    fprintf(fval, "timesh; time_ms; x; y; yp; yi; yd; x16; y16; yp16; yi16; yd16; x32; y32; yp32; yi32; yd32;\n");
    //Data_s datalocal = INIZ_Data(datalocal);
    //Data_s* thiz = &datalocal;
    int sizeData = sizeof(Data_s);
    Data_s* thiz = ctor_Data(alloc_MemC(sizeData), sizeData);
    ASSERT_emC(sizeof(thiz->pid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
    ASSERT_emC(sizeof(thiz->parPid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
    float Tctrl = 0.000050f;
    ctor_Par_PIDf_Ctrl_emC(&thiz->parPid.base.obj, 0.002f);
    ctor_PIDf_Ctrl_emC(&thiz->pid.base.obj, Tctrl);
    ctor_T2f_Ctrl_emC(&thiz->dxs);
    ctor_Delayf_Ctrl_emC(&thiz->delayx.base.obj, 20, sizeof(thiz->delayx) + sizeof(thiz->_delayxValues));
    ctor_SmoothGainf_Ctrl_emC(&thiz->gains_dx.base.obj, 0.005f, 0, Tctrl);

    init_Par_PIDf_Ctrl_emC(&thiz->parPid, 0.000050f, param->valrange, param->kP, param->Tn, param->Td, param->dt, false, false);
    init_PIDf_Ctrl_emC(&thiz->pid, &thiz->parPid);
    //Calculate some more variants with Tn
    init_Par_PIDi_Ctrl_emC(&thiz->parPid16, 0.000050f, (int)param->valrange, 16, param->kP, param->Tn, param->Td, param->dti, false, false);
    init_Par_PIDi_Ctrl_emC(&thiz->parPid32, 0.000050f, (int)param->valrange, 32, param->kP, param->Tn, param->Td, param->dti, false, false);
    //
    init_PIDi_Ctrl_emC(&thiz->pid16, &thiz->parPid16);
    init_PIDi_Ctrl_emC(&thiz->pid32, &thiz->parPid32);
    param_T2f_Ctrl_emC(&thiz->dxs, param->Tsd1, param->Tsd2, Tctrl);
    setLim_PIDf_Ctrl_emC(&thiz->pid, param->valrange);
    float xEnv[3][3] = {0};
    float ypid[3];
    float wCtrl = 0; 
    while(++nStep <2500) {
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
      float xEnvADCf = ((int)(param->xquant*(xEnv[0][0])/param->valrange + 0.5f ) / param->xquant ) * param->valrange;
      int xEnvADC16 = (int)(((int)(param->xquant*(xEnv[1][0])/param->valrange + 0.5f ) / param->xquant ) * param->valrange);
      int xEnvADC32 = (int)(((int)(param->xquant*(xEnv[2][0])/param->valrange + 0.5f ) / param->xquant ) * param->valrange);
      float wx = wCtrl - xEnvADCf;
      float dx;
      float xdx = param->bonly_xdx ? xEnvADCf : wx;
      if(param->ndxDelay >0) {
        float xdxz = step_Delayf_Ctrl_emC(&thiz->delayx, param->ndxDelay, xdx);
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
        xEnv[ix][1] += param->fT1 * (ypid[ix] - xEnv[ix][1]);
        xEnv[ix][2] += param->fT2 * (xEnv[ix][1] - xEnv[ix][2]);
        xEnv[ix][0] += param->fT3 * (xEnv[ix][2] - xEnv[ix][0]);
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
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_Exception_emC(exc, _thCxt);
  }
  END_TRY;
  STACKTRC_RETURN;
}

PIDf_Ctrl_emC pid(0, 0.000050f);


static void test_PIDf(){

  float Tctrl = 0.000050f;
  Param_Test_PID param = {0};
  
  param.valrange = 2000.0f;
  param.xquant = 2000.0f;  // build input signal with this ADC resolution (quantization)
  param.ndxDelay = 0;         // 0: smooth D-part, 1..31 use delayed values  
  //param.kP = 6.0f, Tn = 0.005f, Td = 0.001f; ndxDelay = 15;
  param.kP = 30.0f, param.Tn = 0.005f, param.Td = 0.001f; 
  param.ndxDelay = 1;
  //param.kP = 4.0f, Tn = 0.004f, Td = 0;
  param.dt = param.ndxDelay ==0 ? Tctrl : param.ndxDelay * Tctrl;
  param.dti = param.ndxDelay ==0 ? 1 : param.ndxDelay;
  param.Tsd1 = 0.000000f, param.Tsd2 = 0.0f;    //time only for smoothed D-input 
  param.fT1 = 0.01f, param.fT2 = 0.05f, param.fT3 = 0.1f;  //Ts = 5 ms, 1 ms, 0.5 ms
  param.bonly_xdx = 0;        // select, use x or w-x for D-part.

  testLim_PIDf("test1.csv", &param);

  param.Td = 0.0002f; 
  param.kP = 20.0f;
  testLim_PIDf("pid1_kP=20_T2=0.2ms.csv", &param);

  param.Td = 0.0f; 
  param.kP = 5.0f; 
  testLim_PIDf("pid1_kP=5_Td=0.csv", &param);

  param.Td = 0.0005f; 
  param.kP = 10.0f;
  param.ndxDelay = 5;
  testLim_PIDf("pid1_kP=20_T2=0.5ms_td=5.csv", &param);

  param.Td = 0.0005f; 
  param.kP = 10.0f;
  param.ndxDelay = 0;
  param.Tsd2 = 0.0002f;  
  testLim_PIDf("pid1_kP=20_T2=1ms_tsd2=0.5.csv", &param);

}


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
  test_PIDf();

}


