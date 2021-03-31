/**
 * @File: tuya_dp_process.c 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-05 
 * @Description: gas detection demo 
 */

#include "tuya_dp_process.h"
#include "tuya_iot_com_api.h"
#include "uni_log.h"
#include "soc_adc.h"
#include "tuya_cloud_wifi_defs.h"

#define DPID_STATE    2
#define DPID_VALUE    5
#define TEMP_ADC_DATA_LEN            (4)
char pin_state;
tuya_adc_dev_t tuya_adc;
INT_T gas_val;

 /***********************************************************
 *   Function:  dp_process
 *   Input:     none
 *   Output:    none
 *   Return:    none
 *   Notice:    处理 dp 数据 
 ***********************************************************/
VOID dp_process(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);

    return;
}

INT_T adc_value_get(VOID)
 {   
     INT_T value = 0;
     INT_T ret;
     tuya_adc.priv.pData = Malloc(TEMP_ADC_DATA_LEN * sizeof(USHORT_T));
     memset(tuya_adc.priv.pData, 0, TEMP_ADC_DATA_LEN*sizeof(USHORT_T));
     tuya_adc.priv.data_buff_size = TEMP_ADC_DATA_LEN; //设置数据缓存个数
     tuya_hal_adc_init(&tuya_adc); 
     ret = tuya_hal_adc_value_get(TEMP_ADC_DATA_LEN, &value);
     if(-1 == ret){
         PR_ERR("get adc value failed");
     }
     
     else{
         PR_NOTICE("gas_VCC_value = %d", value);
     }
     tuya_hal_adc_finalize(&tuya_adc); 
     Free(&tuya_adc);
 
     return value;
 
 }
 /***********************************************************
 *   Function:  updata_dp_all
 *   Input:     none
 *   Output:    none
 *   Return:    none
 *   Notice:    上报所有 dp 
 ***********************************************************/
VOID updata_dp_all(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    INT_T dp_cnt = 0;
    dp_cnt = 2;

    /* 没有连接到路由器，退出 */
    GW_WIFI_NW_STAT_E wifi_state = STAT_LOW_POWER;
    get_wf_gw_nw_status(&wifi_state);
    if (wifi_state <= STAT_AP_STA_DISC || wifi_state == STAT_STA_DISC) {
        return;
    }

    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));

    dp_arr[0].dpid = DPID_STATE;
    dp_arr[0].type = PROP_ENUM;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_enum = pin_state;

    dp_arr[1].dpid = DPID_VALUE;
    dp_arr[1].type = PROP_VALUE;
    dp_arr[1].time_stamp = 0;
    dp_arr[1].value.dp_value = gas_val;
    op_ret = dev_report_dp_json_async(NULL ,dp_arr,dp_cnt);
    Free(dp_arr);
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    
    return;
}




