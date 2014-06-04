/**
  ******************* (C) COPYRIGHT 2014 YKLE **********************************
  * @file      main.c
  * @author    Mr.Marvel
  * @version   V1.0.0
  * @date      2014/5/12
  * @brief     
  ******************************************************************************
  * @copy


  ****************************************************************************** 
  * Hardware:          :  TM320F28335
  * Compiler:          :  CCS3.3
  */
/* include -------------------------------------------------------------------*/
#include "cts.h"

#define FLASH   0

    #if FLASH == 1
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
    #endif

void main(void)
{
    CTSCPUInit();
	    #if  FLASH == 1
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
    InitFlash();
        #endif
	CTSTimerInit();
    CTSInit();
    CTSStart();
}


/********************************* End of file *********************************/
