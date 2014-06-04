/**
  ******************************************************************************
  * @file      cts.c
  * @author    Mr.Marvel
  * @version   V1.0.0
  * @date      2014/5/12
  * @brief     Cooperative task scheduler 
  ******************************************************************************
  * @copy
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef _CTS_H_
#define _CTS_H_

/* include -------------------------------------------------------------------*/

#include "cts_cpu.h"     
#include "lib_def.h"

/**
  * @brief     
  */
#define CTS_TASK_SIZE          10
#define CTS_TASKINDEX_SIZE     CTS_TASK_SIZE
#define CTS_EV_TASK_SIZE       10
#define CTS_ERR_SIZE           5


#define CTS_NULL               ((void *)0)
#define CTS_NUL                0x00
#define CTS_ID_INVAILD         0xff
#define CTS_TURE               0x01
#define CTS_FALSE              0x00


#define CTS_TIME_1S            1000u


typedef void  CTSTaskFunc(void);
typedef void  CTSEvTaskFunc(void);
/**
  * @brief  : Task ID type definition
  */
typedef enum
{
    User1,
	User2,
    User3,
    CTS_ID_LED_RUN
}CTSTaskID;

/**
  * @brief  : Event task ID type definition
  */
typedef enum
{
    User4,
	User5
}CTSEvTaskID;

/**
  * @brief  : Task Function access
  */
void CTSGreateTask(CTSTaskID id ,CTSTaskFunc * task, UINT16 delay, UINT16 period);
void CTSDeleteTask(CTSTaskID id);
void CTSChangeTaskDelay(CTSTaskID id,UINT16 delay);
void CTSChangeTaskPeriod(CTSTaskID id,UINT16 period);
/**
  * @brief  : Event Task Function access
  */
void CTSGreateEvTask(CTSEvTaskID id, CTSEvTaskFunc * evtask, UINT8 delaycycle, UINT8 periodcycle);
void CTSDeleteEvTask(CTSEvTaskID id);

void CTSInit(void);
void CTSStart(void);

#endif
