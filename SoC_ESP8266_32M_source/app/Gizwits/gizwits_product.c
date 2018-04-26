/**
************************************************************
* @file         gizwits_product.c
* @brief        Control protocol processing, and platform-related hardware initialization
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         鏈烘櫤浜�.鍙负鏅鸿兘纭欢鑰岀敓
*               Gizwits Smart Cloud  for Smart Products
*               閾炬帴|澧炲�贾祙寮�鏀緗涓珛|瀹夊叏|鑷湁|鑷敱|鐢熸��
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "driver/hal_key.h"
#include "gpio.h"
#include "eagle_soc.h"


/** User area The current device state structure */
dataPoint_t currentDataPoint;

/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t ICACHE_FLASH_ATTR gizwitsEventProcess(eventInfo_t *info, uint8_t *data, uint32_t len)
{
    uint8_t i = 0;
    dataPoint_t * dataPointPtr = (dataPoint_t *)data;
    moduleStatusInfo_t * wifiData = (moduleStatusInfo_t *)data;

    if((NULL == info) || (NULL == data))
    {
        GIZWITS_LOG("!!! gizwitsEventProcess Error \n");
        return -1;
    }

    for(i = 0; i < info->num; i++)
    {
        switch(info->event[i])
        {
        case EVENT_LampSwitch :
            currentDataPoint.valueLampSwitch = dataPointPtr->valueLampSwitch;
            GIZWITS_LOG("Evt: EVENT_LampSwitch %d \n", currentDataPoint.valueLampSwitch);
            if(0x01 == currentDataPoint.valueLampSwitch)
            {
            	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO5);
            	gpio_output_set(BIT5, 0, BIT5, 0);//user handle
            }
            else
            {
            	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO5);
            	gpio_output_set(0, BIT5, BIT5, 0);//user handle
            }
            break;



        case WIFI_SOFTAP:
            break;
        case WIFI_AIRLINK:
            break;
        case WIFI_STATION:
            break;
        case WIFI_CON_ROUTER:
            GIZWITS_LOG("@@@@ connected router\n");
 
            break;
        case WIFI_DISCON_ROUTER:
            GIZWITS_LOG("@@@@ disconnected router\n");
 
            break;
        case WIFI_CON_M2M:
            GIZWITS_LOG("@@@@ connected m2m\n");
			setConnectM2MStatus(0x01);
 
            break;
        case WIFI_DISCON_M2M:
            GIZWITS_LOG("@@@@ disconnected m2m\n");
			setConnectM2MStatus(0x00);
 
            break;
        case WIFI_RSSI:
            GIZWITS_LOG("@@@@ RSSI %d\n", wifiData->rssi);
            break;
        case TRANSPARENT_DATA:
            GIZWITS_LOG("TRANSPARENT_DATA \n");
            //user handle , Fetch data from [data] , size is [len]
            break;
        case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
            break;
            
        default:
            break;
        }
    }
    system_os_post(USER_TASK_PRIO_2, SIG_UPGRADE_DATA, 0);
    
    return 0; 
}


/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void ICACHE_FLASH_ATTR userHandle(void)
{
    /*

    */
	 
    system_os_post(USER_TASK_PRIO_2, SIG_UPGRADE_DATA, 0);
}


/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void ICACHE_FLASH_ATTR userInit(void)
{
    gizMemset((uint8_t *)&currentDataPoint, 0, sizeof(dataPoint_t));

 	/** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
   		currentDataPoint.valueLampSwitch = ;
    */
}


