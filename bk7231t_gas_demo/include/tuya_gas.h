/**
 * @File: tuya_flame.h 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-05 
 * @Description: flame detection demo 
 */
#ifndef __TUYA_FLAME_H__
#define __TUYA_FLAME_H__

#include "tuya_cloud_types.h"
#include "tuya_gpio.h"

#define GAS_SENSOR_PIN    TY_GPIOA_8


VOID gas_sensor_init(VOID);
VOID check_gas_task(VOID);

#endif

