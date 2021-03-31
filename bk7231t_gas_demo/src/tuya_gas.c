/**
 * @File: tuya_gas.c 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-05 
 * @Description: gas detection demo 
 */

#include "tuya_dp_process.h"
#include "tuya_gas.h"
#include "tuya_iot_com_api.h"
#include "uni_log.h"

#include "FreeRTOS.h"
#include "task.h"
#include "uni_thread.h"
#include "tuya_cloud_types.h"

#define ALARM       0
#define NORMAL      1
extern bool pin_state;
extern INT_T gas_val;
VOID check_gas_task(VOID);

VOID gas_sensor_init(VOID)
{
    tuya_gpio_inout_set(GAS_SENSOR_PIN, TRUE);

    tuya_hal_thread_create(NULL, "check_gas", 512 * 4, TRD_PRIO_4, check_gas_task, NULL);
}

VOID check_gas_task(VOID)
{
    while (1) {
        if (FALSE == tuya_gpio_read(GAS_SENSOR_PIN)) {
            pin_state = NORMAL;
        } else {
            pin_state = ALARM;
        }
        gas_val = adc_value_get() / 10;
        updata_dp_all();
        tuya_hal_system_sleep(1000);
    }
}

