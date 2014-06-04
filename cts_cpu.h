/**
  ******************************************************************************
  * @file      cts_cpu.h
  * @author    Mr.Marvel
  * @version   V1.0.0
  * @date      2014/5/11
  * @brief     for DSP28xxx
  ******************************************************************************
  * @copy
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef _CTS_CPU_H_
#define _CTS_CPU_H_

/* include -------------------------------------------------------------------*/

#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File

/** 
  * @brief    Type define 
  */
typedef unsigned char                BOOL;
typedef char                         INT8;
typedef int                          INT16;
typedef long                         INT32;
typedef long long                    INT64;
typedef unsigned char                UINT8;
typedef unsigned int                 UINT16;
typedef unsigned long                UINT32;
typedef unsigned long long           UINT64;
typedef float                        FLOAT32;
typedef long double                  FLOAT64;

/** 
  * @brief   CPU Configuration  
  */
// Cpu operating frequency and tick
#define CTS_CPU_FREQ                 150                     /** 150MHZ */
#define CTS_TICK                     1000                    /** us     */
// Cpu hardware drive
#define CTS_CPU_HARDWARE_DRV         1


/** 
  * @brief    Save status seg
  *           disable interrupt
  *           restore status
  */
#define CTS_CPU_SR()                 UINT16 cpu_sr
#define CTS_ENTER_CRITICAL()         cpu_sr = __disable_interrupts()
#define CTS_EXIT_CRITICAL()          __restore_interrupts(cpu_sr)

//#define CTS_ENTER_CRITICAL()   asm(" push ST1");asm(" setc INTM");asm(" pop @_cpu_st1")
//#define CTS_EXIT_CRITICAL()    asm(" pop ST1")


/** 
  * @brief   Function access
  */
void CTSCPUInit(void);
void CTSTimerInit(void);
void CTSTimerStop(void);
void CTSTimerStart(void);
    #if CTS_CPU_HARDWARE_DRV == 1
void CTSSCpuHardwareDriveInit(void);
void CTSSCpuHardwareDriveRun(void);
    #endif
/** 
  * @brief    tick ISR 
  */

#define CTS_TICK_ISR       interrupt void cpu_timer0_isr(void)


/** 
  * @brief   Board Configuration  
  */
    #if DSP28_28335 
#define DSP2833X_EPWM1                 0
#define DSP2833X_EPWM2                 0
#define DSP2833x_EPWM3                 0
#define DSP2833X_EPWM4                 0
#define DSP2833X_EPWM5                 0
#define DSP2833X_EPWM6                 0
#define DSP2833X_ECAP1                 0
#define DSP2833X_ECAP2                 0
#define DSP2833X_ECAP3                 0
#define DSP2833X_ECAP4                 0
#define DSP2833X_ECAP5                 0
#define DSP2833X_ECAP6                 0
#define DSP2833X_EQEP1                 0
#define DSP2833X_EQEP2                 0
#define DSP2833X_ECANA                 0
#define DSP2833X_ECANB                 0
#define DSP2833X_MCBSPA                0
#define DSP2833X_MCBSPB                0
#define DSP2833X_SPIA                  0
#define DSP2833X_SCIA                  0
#define DSP2833X_SCIB                  0
#define DSP2833X_SCIC                  0
#define DSP2833X_I2CA                  0
#define DSP2833X_CPUTIMER0             1
#define DSP2833X_CPUTIMER1             0
#define DSP2833X_CPUTIMER2             0
#define DSP2833X_DMA                   0
#define DSP2833X_XINTF                 0
#define DSP2833X_GPIOIN                1
#define DSP2833X_ADC                   0
    #endif          

#endif

/********************************* End of file *****************************************/
