/**
 * @File: tuya_dp_process.h 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-05 
 * @Description: gas detection demo 
 */
#ifndef __TUYA_DP_PROCESS_H_
#define __TUYA_DP_PROCESS_H_

#include "tuya_cloud_com_defs.h"
#include "tuya_cloud_types.h"


VOID updata_dp_all(VOID);
VOID dp_process(IN CONST TY_OBJ_DP_S *root);
INT_T adc_value_get(VOID);


#endif

