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

/*------------------------------------------------------------------------------
 * include
 *-----------------------------------------------------------------------------*/
#include "cts.h" 


/*-------------------------------------------------------------------------------
                              structure declaration
---------------------------------------------------------------------------------*/
/**
  * @brief   : Timer task structure definition
  */
typedef struct
{
    CTSTaskFunc       *task;
    UINT8             id;
	UINT16            delay;
    UINT16            period;
}CTSTaskTypeDef;
static CTSTaskTypeDef    CTSTask[CTS_TASK_SIZE];

/**
  * @brief  : Timer task index structure definition
  */
typedef struct
{
             UINT8       id[CTS_TASKINDEX_SIZE];
	volatile UINT8       head;
	volatile UINT8       tail;
}CTSTaskIndexTypeDef;
static CTSTaskIndexTypeDef    CTSTaskIndex;

/**
  * @brief    Event task  structure definition
  */
typedef struct
{
    CTSEvTaskFunc  *evtask;
	UINT8          delaycycle;
	UINT8          periodcycle;
}CTSEvTaskTypeDef;
static CTSEvTaskTypeDef    CTSEvTaskList[CTS_EV_TASK_SIZE];

typedef enum
{
    CTS_OK               = 0,
    CTS_ERR_INDEX_FLOW   = 1,
	CTS_ERR_TASK_FLOW    = 2,
	CTS_ERR_TASK_EXIST   = 3,
    CTS_ERR_EVTASK_FLOW  = 4,
	CTS_ERR_EVTASK_EXIST = 5
}CTSErrTypeDef;
typedef struct
{
    UINT8                   flag;
	UINT8                   cnt;
    CTSErrTypeDef           List[CTS_ERR_SIZE];
}CTSErrTrpeTypeDef;
static CTSErrTrpeTypeDef    CTSTrap;


/*-------------------------------------------------------------------------------
                              Function declaration
---------------------------------------------------------------------------------*/

    #if CTS_CPU_HARDWARE_DRV == 1
static void CTSStatusRunLEDInit(void);
static void CTSStatusRunLed(void);
    #endif

static void CTSTrapCode(CTSErrTypeDef code);

static BOOL CTSTaskCheckId(CTSTaskID id);
static BOOL CTSTaskCheckReCeate(CTSTaskID id);
static BOOL CTSEvTaskCheckId(CTSEvTaskID id);
static BOOL CTSEvTaskCheckReCeate(CTSEvTaskID id);


/*-------------------------------------------------------------------------------
                                  Function
---------------------------------------------------------------------------------*/
/**
  * @brief  : Initialize the Timer Task structure
  * @param  : None
  * @retval : None
  */
static void CTSTaskInit(void)
{
    UINT8 i;

	for(i = 0; i < CTS_TASK_SIZE; i++)
	{
	    CTSTask[i].task   = CTS_NULL;
		CTSTask[i].id     = CTS_ID_INVAILD;
		CTSTask[i].delay  = CTS_NUL;
		CTSTask[i].period = CTS_NUL;
	}
}
/**
  * @brief  : Initialize the Timer Index queue
  * @param  : None
  * @retval : None
  */
static void CTSTaskIndexInit(void)
{
    UINT8 i;

	for(i = 0; i < CTS_TASK_SIZE; i++)
	{
	    CTSTaskIndex.id[i] = CTS_ID_INVAILD;
	}
    CTSTaskIndex.head = CTS_NUL;
	CTSTaskIndex.tail = CTS_NUL;
}
/**
  * @brief  : Initialize the Event Task structure
  * @param  : None
  * @retval : None
  */
static void CTSEvTaskInit(void)
{
    UINT8 i;

	for(i = 0; i < CTS_EV_TASK_SIZE; i++)
	{
	    CTSEvTaskList[i].evtask      = CTS_NULL;
		CTSEvTaskList[i].evtask      = CTS_NUL;
		CTSEvTaskList[i].periodcycle = CTS_NUL;
	}
}
static void CTSTrapInit(void)
{
    UINT8 i;

    CTSTrap.cnt  = 0;
    CTSTrap.flag = CTS_FALSE;
	for(i = 0; i < CTS_ERR_SIZE; i++)
	{
		CTSTrap.List[i] = CTS_OK;
	}
}
/**
  * @brief  : Initialize the CTS
  *           CTSTaskInit();
  *	          CTSTaskIndexInit();
  *	          CTSEvTaskInit();
  *           CTSTrapInit();
  * @param  : None
  * @retval : None
  */

void CTSInit(void)
{
    CTSTaskInit();
	CTSTaskIndexInit();
	CTSEvTaskInit();
	CTSTrapInit();
	    #if CTS_CPU_HARDWARE_DRV == 1
	CTSStatusRunLEDInit();
        #endif
}

/**
  * @brief  : Add a new timer task
  * @param  : id :
              task:
              delay:
			  period:
  * @retval : None
  */
void CTSGreateTask(CTSTaskID id, CTSTaskFunc * task, UINT16 delay, UINT16 period)
{
    UINT8 a;
	CTSTaskTypeDef * p;
	CTS_CPU_SR();

	if(CTSTaskCheckId(id) && CTSTaskCheckReCeate(id))
	{
        CTS_ENTER_CRITICAL();
	    a = (UINT8)id;
        p = & CTSTask[a];
	    p -> task   = task;
	    p -> id     = a;
	    p -> delay  = delay;
	    p -> period = period;
 	    CTS_EXIT_CRITICAL();
	}
}
/**
  * @brief  : Delete a timer task
  * @param  : id :
  * @retval : None
  */
void CTSDeleteTask(CTSTaskID id)
{
    UINT8 a;
	CTSTaskTypeDef * p;
	CTS_CPU_SR();

    if(CTSTaskCheckId(id))
	{
        CTS_ENTER_CRITICAL();
	    a = (UINT8)id;
        p = & CTSTask[a];
	    p -> task   = CTS_NULL;
	    p -> id     = a;
	    p -> delay  = CTS_NUL;
	    p -> period = CTS_NUL;
	    CTS_EXIT_CRITICAL();
	}
}
/**
  * @brief  : Change task delay
  * @param  : id :
  * @retval : None
  */
void CTSChangeTaskDelay(CTSTaskID id,UINT16 delay)
{
    UINT8 a;
	CTSTaskTypeDef * p;
	CTS_CPU_SR();

	if(CTSTaskCheckId(id))
	{
        CTS_ENTER_CRITICAL();
	    a = (UINT8)id;
	    p = & CTSTask[a];
	    p -> delay  = delay;
	    CTS_EXIT_CRITICAL();
	}
}
/**
  * @brief  : Change task period
  * @param  : id :
  * @retval : None
  */
void CTSChangeTaskPeriod(CTSTaskID id,UINT16 period)
{
    UINT8 a;
	CTSTaskTypeDef * p;
	CTS_CPU_SR();

	if(CTSTaskCheckId(id))
	{
	    CTS_ENTER_CRITICAL();
	    a = (UINT8)id;
	    p = & CTSTask[a];
	    p -> period  = period;
	    CTS_EXIT_CRITICAL();
	}
}
/**
  * @brief  : Add a new Event Task
  * @param  : id :
  *           evtask
  *           delaycycle
  *           periodcycle
  * @retval : None
  */
void CTSGreateEvTask(CTSEvTaskID id, CTSEvTaskFunc * evtask, UINT8 delaycycle, UINT8 periodcycle)
{
    UINT8 a;
    CTS_CPU_SR();

    if(CTSEvTaskCheckId(id) && CTSEvTaskCheckReCeate(id))
	{
        CTS_ENTER_CRITICAL();
	    a = (UINT8)id;
	    CTSEvTaskList[a].evtask      = evtask;
	    CTSEvTaskList[a].delaycycle  = delaycycle;
	    CTSEvTaskList[a].periodcycle = periodcycle;
	    CTS_EXIT_CRITICAL();
	}
}
/**
  * @brief  : Delay Event Task
  * @param  : id :
  * @retval : None
  */
void CTSDeleteEvTask(CTSEvTaskID id)
{
    UINT8 a;
	CTS_CPU_SR();
    if(CTSEvTaskCheckId(id))
	{
        CTS_ENTER_CRITICAL();
	    a = (UINT8)id;
        CTSEvTaskList[a].evtask      = CTS_NULL;
        CTSEvTaskList[a].delaycycle  = CTS_NUL;
        CTSEvTaskList[a].periodcycle = CTS_NUL;
	    CTS_EXIT_CRITICAL();
	}
}
/**
  * @brief  : Check the task id
  * @param  : id :
  * @retval : None
  */
static BOOL CTSTaskCheckId(CTSTaskID id)
{
    if((UINT8)id > CTS_TASK_SIZE)
	{
	    CTSTrapCode(CTS_ERR_TASK_FLOW);
	    return CTS_FALSE;
	}
	else
	{
	    return CTS_TURE;
	}
}
/**
  * @brief  : Check the task recreat
  * @param  : id :
  * @retval : None
  */
static BOOL CTSTaskCheckReCeate(CTSTaskID id)
{
    UINT8 a;

	a = (UINT8)id;
    if(CTSTask[a].task != CTS_NULL)
	{
	    CTSTrapCode(CTS_ERR_TASK_EXIST);
	    return CTS_FALSE;
	}
	else
	{
	    return CTS_TURE;
	}
}
static BOOL CTSEvTaskCheckId(CTSEvTaskID id)
{
    if((UINT8)id > CTS_TASK_SIZE)
	{
	    CTSTrapCode(CTS_ERR_EVTASK_FLOW);
	    return CTS_FALSE;
	}
	else
	{
	    return CTS_TURE;
	}
}
static BOOL CTSEvTaskCheckReCeate(CTSEvTaskID id)
{
    UINT8 a;

	a = (UINT8)id;
    if(CTSEvTaskList[a].evtask != CTS_NULL)
	{
	    CTSTrapCode(CTS_ERR_EVTASK_EXIST);
	    return CTS_FALSE;
	}
	else
	{
	    return CTS_TURE;
	}
}

static void CTSTrapCode(CTSErrTypeDef code)
{
    CTSTrap.flag = CTS_TURE;

    if(CTSTrap.cnt >= CTS_ERR_SIZE)
	{
	    UINT8 i = CTS_ERR_SIZE - 1;
		do
		{
		    CTSTrap.List[i - 1] = CTSTrap.List[i];
		}while(i--);
	    CTSTrap.cnt++;
        CTSTrap.List[CTS_ERR_SIZE - 1] = code;

	}
	else
	{
	    CTSTrap.List[CTSTrap.cnt++] = code;
	}
}

/**
  * @brief  : CPU hardware drive ---LED
  *
  */
    #if CTS_CPU_HARDWARE_DRV == 1

#define CTS_LED_NORMAL_PROIDE                CTS_TIME_1S/10
#define CTS_LED_ERR_PROIDE                   CTS_TIME_1S*2
#define CTSStatusRunLEDPinInit()             CTSSCpuHardwareDriveInit()
#define CTSStatusRunLEDNormal()              CTSSCpuHardwareDriveRun()
static CTSTaskFunc CTSStatusRunLed ;
static void CTSStatusRunLEDInit(void)
{
    CTSStatusRunLEDPinInit();
	CTSGreateTask(CTS_ID_LED_RUN,CTSStatusRunLed,0,CTS_LED_NORMAL_PROIDE);
}
static void CTSStatusRunLed(void)
{
    CTSStatusRunLEDNormal();
	if(CTSTrap.flag == CTS_TURE)
	{
	    CTSDeleteTask(CTS_ID_LED_RUN);
        CTSGreateTask(CTS_ID_LED_RUN,CTSStatusRunLed,0,CTS_LED_ERR_PROIDE);
	}
}
	#endif


/**
  * @brief  : CTS run
  *
  */
void CTSStart(void)
{
	UINT8 i;
	CTSTimerStart();
    for(; ;)
	{
	    if(CTSTaskIndex.head != CTSTaskIndex.tail)
		{
		    if( CTSTask[CTSTaskIndex.id[CTSTaskIndex.tail]].task != CTS_NULL)
			{
				(* CTSTask[CTSTaskIndex.id[CTSTaskIndex.tail]].task)();
		        CTSTaskIndex.tail = (CTSTaskIndex.tail + 1) % CTS_TASKINDEX_SIZE;
			}
		}
		for(i = 0; i < CTS_EV_TASK_SIZE; i++)
		{
		    if(CTSEvTaskList[i].evtask != CTS_NULL)
			{
			    if(CTSEvTaskList[i].delaycycle == 0)
				{
				    (* CTSEvTaskList[i].evtask)();
				    CTSEvTaskList[i].delaycycle = CTSEvTaskList[i].periodcycle;
				}
				else
				{
				    CTSEvTaskList[i].delaycycle--;
				}
			}
		}
	}
}
/**
  * @brief  : Tick ISR -- 1ms
  *
  */
CTS_TICK_ISR
{
    UINT8 i;

	for(i = 0; i < CTS_TASK_SIZE; i++)
	{
	    if(CTSTask[i].task != CTS_NULL)
		{
		     if(CTSTask[i].delay <= 1)
			 {
			     CTSTaskIndex.id[CTSTaskIndex.head] = i;
				 CTSTaskIndex.head = (CTSTaskIndex.head + 1) % CTS_TASKINDEX_SIZE;
				 CTSTask[i].delay  = CTSTask[i].period;
			 }
			 else
			 {
			     CTSTask[i].delay--;
			 }
		}
	}
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/********************************* End of file *********************************/
