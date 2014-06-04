/**
  ******************************************************************************
  * @file      cts_cpu.c
  * @author    Mr.Marvel
  * @version   V1.0.0
  * @date      2014/5/11
  * @brief     for DSP28xxx
  ******************************************************************************
  * @copy
  */ 

/* include -------------------------------------------------------------------*/

#include "cts_cpu.h"

/* function declaration ------------------------------------------------------*/
interrupt void cpu_timer0_isr(void);

/* function  -----------------------------------------------------------------*/
/**
  * @brief  : Setup the microcontroller system
  *           Initialize the Embedded Flash Interface  
  *           Initialize the PLL and update th SystemFrequency variable
  *           Initialize the pie vect table
  *		        close cpu interrupt
  * @note   : This function should be used only after reset.
  * @param  : None
  * @retval : None
  */
void CTSCPUInit(void)
{
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    EINT;   
    ERTM;   
}

/**
  * @brief  : Initialize the timer
  *           Configures the timer clock frequencys
  * @param  : None
  * @retval : None
  */
void CTSTimerInit(void)
{
    EALLOW; 
    PieVectTable.TINT0 = &cpu_timer0_isr;
    EDIS;
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, CTS_CPU_FREQ, CTS_TICK);
    IER |= M_INT1;	
}
/**
  * @brief  : Start timer
  * @param  : None
  * @retval : None
  */
void CTSTimerStart(void)
{
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    CpuTimer0Regs.TCR.all = 0x4001;
}
/**
  * @brief  : close timer
  * @param  : None
  * @retval : None
  */
void CTSTimerStop(void)
{  
    CpuTimer0Regs.TCR.all = 0x0000;
}

/**
  * @brief  : Hardware drive
  */
    #if CTS_CPU_HARDWARE_DRV  == 1
void CTSSCpuHardwareDriveInit(void)
{
    EALLOW;
    GpioCtrlRegs.GPCMUX2.bit.GPIO82 = 0;
    GpioCtrlRegs.GPCDIR.bit.GPIO82 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO82 = 0;
    EDIS;
}
void CTSSCpuHardwareDriveRun(void)
{
    GpioDataRegs.GPCTOGGLE.bit.GPIO82 = 1;
}
    #endif
/********************************* End of file *********************************/
