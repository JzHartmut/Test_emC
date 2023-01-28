/**This file offers a socmd.exe which sends a command via socket connection
 * and UDP telegram to a receiver.
 * The receiver is often a Java program which executes this cmd
 * for any desired control operation.
 * Such a socmd.exe helps to integrate a Java process in any desired environment
 * which can execute commands from the OS. That is true for many script base applications.
 * Made by Hartmut Schorrig, Germany, www.vishia.org
 * Copyright/left LPGL license.
 * This license remark also in the executable must not deleted.
 */
#include <applstdef_emC.h>
#include <emC/OSAL/os_socket.h>
#include <emC/J1c/StringPartScanJc.h>
#include <emC/Base/Time_emC.h>
#include <emC/Base/StringNum_emC.h>
#include <stdio.h>
#include <stdlib.h>
 
/**The data of args: */


typedef struct SocketCmd_T {
  
  /**A socket for tx and rx. */
  OS_DatagramSocket soOwn;
  
  /**The own socket address (IP v4 and port)*/
  OS_SOCKADDR addrOwn;

  /**The partner socket address (IP v4 and port)*/
  OS_SOCKADDR addrDst;

  /**The sender socket address (IP v4 and port) for received message*/
  OS_SOCKADDR addrRx;

  /**The string given own address as cmdline argument. */
  char const* sAddrOwn;
  
  /**The string given destination address as cmdline argument. */
  char const* sAddrDst;
  

  int timeoutAfterError;

  /**False then should write infos only on error.*/
  bool bInfo;


  /**True than should transmit a message.*/
  bool bShouldTx;

  /**True than should receive a message.*/
  bool bShouldRx;

  int zToken;
  char const* tokens[20];

  int zTxArgs;
  char txArgs[1400];  //the command line which should be transmitted.
} SocketCmd_s;

SocketCmd_s dataAppl = {0};


int stop(){ return 0;}

char const* help = "\
socketcmd -own:127.0.0.1:12345 -dst:0x7f000001:0xaff1 [-cmd cmd {args}] [-info] [-to:1000] [-rx [{token}]]\n\
  transmits and receives strings via socket possible to use as cmd line \n\
  made by Hartmut Schorrig, www.vishia.org\n\
* -own and -dst are the ip addresses (IP V4) with port.\n\
  ip address and port are possible also in hexa form, as shown for dst.\n\
* -cmd if given, the command and some arguments are following. \n\
  in the transmitted string the args are wrapped with \"arg\" if necessary\n\
  proper for immediately use as cmd string.\n\
* -info then should write some infos on transmitting, for debug, \n\
  don't set it if a cmd is expected on stdout.\n\
  NOTE: error messages are always written on stderr. \n\
* -to: timeout after an error, or only one wait time if no cmd is given. \n\
* -rx if given then waits for a received string and writes it to stdout. \n\
* token if given then it checks the receive string and builds a exit level number\n\
   starting from 0 for the first token. It helps to evaluate short received messages\n\
";


void prepAddr(char const* sAddr, OS_SOCKADDR* soAddr) {
  STACKTRC_ENTRY("prepDstAddr");
  StringJc sIp = INIZ_z_StringJc(sAddr);
  StringPartScanJc spIp(sIp);
  bool bOk = true; 
  int32 ipAddr, port;
  if(spIp.scanInteger().scanChar('.').scanOk()) {
    int32 n1, n2, n3, n4;
    n1 = (int32)spIp.getLastScannedIntegerNumber();
    bOk = spIp.scanInteger().scanChar('.').scanOk();
    if(bOk) {
      n2 = (int32)spIp.getLastScannedIntegerNumber();
      bOk = spIp.scanInteger().scanChar('.').scanOk();
      if(bOk) {
        n3 = (int32)spIp.getLastScannedIntegerNumber();
        bOk = spIp.scanInteger().scanOk();
        if(bOk) {
          n4 = (int32)spIp.getLastScannedIntegerNumber();
          ipAddr = (n1<<24) | (n2 <<16) | (n3<<8) | n4;
        }
      }
    }
  }
  else if(spIp.scan("0x").scanHex(8).scanOk()) {
    port = (int32)spIp.getLastScannedIntegerNumber();
  } else {
    bOk = false;
  }
  if(bOk && spIp.scanChar(':').scanHexOrDecimal(8).scanOk()) {
    port = (int32)spIp.getLastScannedIntegerNumber();  //portnr
  } else {
    bOk = false;
  }
  if(bOk) {
    set_OS_SOCKADDR(soAddr, ipAddr, port);
  } 
  else { 
    THROW_s0(IllegalArgumentException, "error ip syntax, \"UDP:127.0.0.1:12345\"", 0, 0);
  }
  
  STACKTRC_RETURN;
}



void openSocket(SocketCmd_s* thiz) {
  STACKTRC_ENTRY("openSocket");
  int ok = os_createDatagramSocket(&thiz->soOwn);
  if(ok !=0) THROW_s0(IllegalArgumentException, "open own socket fails", ok, 0);
  ok = os_bind(thiz->soOwn.socket, &thiz->addrOwn);
  if(ok !=0) THROW_s0(IllegalArgumentException, "bind own socket fails", ok, 0);
  STACKTRC_RETURN;
}



void txCmd(SocketCmd_s* thiz) {
  STACKTRC_ENTRY("txCmd");
  
  int ok = os_sendto(thiz->soOwn, thiz->txArgs, thiz->zTxArgs, 0, &thiz->addrDst);
  if(ok <0) THROW_s0(IllegalArgumentException, "tx fails", ok & ~0x80000000, 0);
  
  STACKTRC_RETURN;
}



int rxCmd(SocketCmd_s* thiz) {
  STACKTRC_ENTRY("rxCmd");
  int ret = 0; //thiz->zToken ==0 ? 0: 99;
  //note: reuse the txArgs, it is transmitted already.
  while(true) {
    int lenTxArgs = ARRAYLEN_emC(thiz->txArgs);
    memset(thiz->txArgs, 0, lenTxArgs);
    //reuse
    int ok = os_recvfrom(thiz->soOwn, thiz->txArgs, lenTxArgs, 0, &thiz->addrRx);
    if(ok <0) {
      ok &= ~0x80000000;  //convention, set MSB for error
      if(ok == 10054){    //This is, partner is not ready, it is only detect if somewhat was transmitted
        if(thiz->bInfo) {
          printf("on tx it was detected that the partner is not existing (error 10054), sleep %d ms, exit with 254\n", thiz->timeoutAfterError);
        }
        if(thiz->timeoutAfterError >0) {
          sleep_Time_emC(thiz->timeoutAfterError);  //sleep till repeating, to prevent too many cpu load for spinning. 
        }
        ret = 254;
      } else {
        THROW_s0(IllegalArgumentException, "rx fails", ok, 0);
      }
    }
    else {
    
      printf(".");
      stop();   //view with debugger
    }
  }//while
  STACKTRC_RETURN ret;
}






 
void main(int nArgs, char** argsCmd) {
  STACKTRC_ROOT_ENTRY("socketcmd");
  SocketCmd_s* thiz = &dataAppl;
  int erret = 0;
  TRY {
    bool gatherCmd = false;
    bool gatherToken = false;
    if(nArgs == 1) {
      printf(help);
    } else {
      for(int ixArg = 1; ixArg < nArgs; ++ixArg) {           // == evaluate cmd args
        char const* argCmd = argsCmd[ixArg];
        if(strncmp(argCmd, "-dst", 4)==0) {                   // store the dst address -ip:192.168.3.4:12345
          gatherCmd = gatherToken = false;
          if(strnlen_emC(argCmd, 30) >4) {                   // either with this argument
            thiz->sAddrDst = argCmd+5;  //after separator char
          } else {
            thiz->sAddrDst = argsCmd[++ixArg];               // or from next arg
          }
        }
        else if(strncmp(argCmd, "-own", 4)==0) {                   // store the dst address -ip:192.168.3.4:12345
          gatherCmd = gatherToken = false;
          if(strnlen_emC(argCmd, 30) >4) {                   // either with this argument
            thiz->sAddrOwn = argCmd+5;  //after separator char
          } else {
            thiz->sAddrOwn = argsCmd[++ixArg];               // or from next arg
          }
        }
        else if(strncmp(argCmd, "-info", 4)==0) {
          thiz->bInfo = true;
        }
        else if(strncmp(argCmd, "-rx", 3)==0) {
          gatherCmd = false;
          gatherToken = true;
          thiz->bShouldRx = true;
        }
        else if(strncmp(argCmd, "-to", 3)==0) {
          thiz->timeoutAfterError = parseIntRadix_emC(argCmd+4, 20, 10, null, null);
          if(thiz->bInfo) { printf("  timeout=%d\n", thiz->timeoutAfterError); } 
        }
        else if(strncmp(argCmd, "-cmd", 4)==0) {
          gatherCmd = true;
          gatherToken = false;
          thiz->bShouldTx = true;
        }
        else if(gatherCmd) {
          //                                                 // it is an argument to forward to dst
          if(thiz->zTxArgs < sizeof(thiz->addrDst)-4) {      // copy as one string, 
            if(thiz->zTxArgs >0) {
              thiz->txArgs[thiz->zTxArgs++] = ' ';          //separator space between
            }
            bool addQuotion = searchAnyChar_emC(argCmd, -100, " =:>;\"\'\t")>=0;  //if contains one of this chars
            if(addQuotion) { thiz->txArgs[thiz->zTxArgs++] = '\"'; }         //surrounded with "arg", maybe necessary.
            thiz->zTxArgs += strpncpy_emC(thiz->txArgs, thiz->zTxArgs, sizeof(thiz->addrDst)-2, argCmd, -1);
            if(addQuotion) { thiz->txArgs[thiz->zTxArgs++] = '\"'; }
          }
        }
        else if(gatherToken) {
          if(thiz->zToken < ARRAYLEN_emC(thiz->tokens)) {
            thiz->tokens[thiz->zToken] = argCmd;
            thiz->zToken +=1;
          } else {
            printf("warning, too many token after -rx, not used: ");
            printf(argCmd); printf("\n");
          }
        }
        else {
          printf("unexpected:"); printf(argCmd);
          printf("\nforgotten -cmd ?\n"); 
          printf(help);
        }
      }
    }
    bool bDoneAny = false;
    if(thiz->sAddrOwn !=null) {
      prepAddr(thiz->sAddrOwn, &thiz->addrOwn);
      prepAddr(thiz->sAddrDst, &thiz->addrDst);
      openSocket(thiz);
      if(thiz->bInfo) { printf("ok open socket %s\n", thiz->sAddrOwn); }
      if(thiz->bShouldTx) {
        bDoneAny = true;
        txCmd(thiz);
        if(thiz->bInfo) { printf("ok tx to %s: %s\n", thiz->sAddrDst, thiz->txArgs); }
      }
      if(thiz->bShouldRx) {
        bDoneAny = true;
        erret = rxCmd(thiz);
      }
    }
    if(!bDoneAny && thiz->timeoutAfterError >0) {
      if(thiz->bInfo) {
        printf("sleep for %d ms\n", thiz->timeoutAfterError);
      }
      sleep_Time_emC(thiz->timeoutAfterError);
    }
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_Exception_emC(exc, _thCxt);
    if(thiz->timeoutAfterError >0) {
      printf("sleep for %d ms\n", thiz->timeoutAfterError);
      sleep_Time_emC(thiz->timeoutAfterError);
    }
    erret = 255;
  }
  END_TRY
  exit(erret);
  //STACKTRC_RETURN;
}





void errorSystem_emC_  (  int errorCode, const char* description, int value1, int value2, char const* file, int line) {
  printf("ERROR SYSTEM: %d %s %d, %d @%s:%d", errorCode, description, value1, value2, file, line);
  exit(255);
}



//Note: The uncatched_Exception should be assigned to the application frame. It is not a part of a library.
//It should terminate the application, but some resources should be freed. The application frame may known which resources.
void uncatched_Exception_emC  (  Exception_emC* thiz, ThreadContext_emC_s* _thCxt) {
#ifdef DEF_NO_StringJcCapabilities
  printf("ERROR uncatched Exception @%s:%d", thiz->file, thiz->line);
#else
  char buffer[300] = { 0 };
  writeException(buffer, sizeof(buffer), thiz, __FILE__, __LINE__, _thCxt);
  printf(buffer);
#endif
}

