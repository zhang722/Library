#ifndef __BSP_GSM_BLUETOOTH_H
#define __BSP_GSM_BLUETOOTH_H

#include "stm32f10x.h"
#include "./systick/bsp_SysTick.h"
#include "./gsm_bluetooth/bsp_gsm_usart.h"

#include "ff.h"

typedef enum{
    GSM_TRUE,
    GSM_FALSE,
    
}gsm_res_e;

typedef struct {
  //0：无网络服务 ，1：有网络服务
  unsigned char service : 1;
  //0：无通话 ，1：有通话
  unsigned char call : 1;
  //0：通话被接听或者被拒绝 ，1：来电，2：去电，3：去电响铃
  unsigned int call_setup:3;
  //0：无保持通话 ，1：通话被保持或者激活和保持通话切换，2：通话被保持，无激活的通话
    unsigned int held:2;
  //0—5网络信号强度
  signed int signal;
  //0：本地 ，1：漫游
  signed int roam;
  //0—5电池电量
  signed int battchg;
} phoneData;

extern  uint8_t     gsm_cmd         	(char *cmd, char *reply,uint32_t waittime );
extern  uint8_t     gsm_cmd_check   	(char *reply);


#define     GSM_CLEAN_RX()              clean_rebuff()
#define     gsm_ate0()                  gsm_cmd("ATE0\r","OK",100)              //关闭回显
#define     GSM_TX(cmd)                	GSM_USART_printf("%s",cmd)
#define     GSM_IS_RX()                 (USART_GetFlagStatus(GSM_USARTx, USART_FLAG_RXNE) != RESET)
#define     GSM_RX(len)                 ((char *)get_rebuff(&(len)))
#define     GSM_DELAY(time)             Delay_ms(time)                 //延时
#define     GSM_SWAP16(data)    				 __REVSH(data)

/*************************** 蓝牙 功能 ***************************/
#define     HFP     0
#define     SPP     1

uint8_t gsm_bt_mode_config(uint8_t status);
void gsm_bt_hfp_test(void);
void get_phone_status(void);

/*调试用串口*/

#define GSM_DEBUG_ON         	0
#define GSM_DEBUG_ARRAY_ON    0
#define GSM_DEBUG_FUNC_ON   	0
// Log define
#define GSM_INFO(fmt,arg...)           printf("<<-GSM-INFO->> "fmt"\n",##arg)
#define GSM_ERROR(fmt,arg...)          printf("<<-GSM-ERROR->> "fmt"\n",##arg)
#define GSM_DEBUG(fmt,arg...)          do{\
                                         if(GSM_DEBUG_ON)\
                                         printf("<<-GSM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
																					}while(0)

#define GSM_DEBUG_ARRAY(array, num)    do{\
                                         int32_t i;\
                                         uint8_t* a = array;\
                                         if(GSM_DEBUG_ARRAY_ON)\
                                         {\
                                            printf("<<-GSM-DEBUG-ARRAY->> [%d]\n",__LINE__);\
                                            for (i = 0; i < (num); i++)\
                                            {\
                                                printf("%02x   ", (a)[i]);\
                                                if ((i + 1 ) %10 == 0)\
                                                {\
                                                    printf("\n");\
                                                }\
                                            }\
                                            printf("\n");\
                                        }\
                                       }while(0)

#define GSM_DEBUG_FUNC()               do{\
                                         if(GSM_DEBUG_FUNC_ON)\
                                         printf("<<-GSM-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
                                       }while(0)

#endif

