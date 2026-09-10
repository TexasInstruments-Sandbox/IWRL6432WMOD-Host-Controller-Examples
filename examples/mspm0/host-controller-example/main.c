/*
 * Copyright (c) 2025-2026, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mspm0_hal.h"
#include "radarlink.h"
#include "ti_msp_dl_config.h"
#include <stdio.h>

T_RETURNTYPE res = 0;
UINT32 error = 0;

M_ML_UDFP_STATUS_GET_RESP_DATA status;
M_ML_UDFP_VERS_GET_RESP_DATA version;
M_ML_SENS_INFO_GET_RSP_DATA sensorInfoData;

volatile uint8_t isPresenceDetected = 0;

char point_cloud_terminal[256];

void print_point_cloud(uint8_t numPoints) {
  char testnl[1] = {'\n'};
  char pcStr[100];
  uint8_t i = 0;
  for (i = 0; i < numPoints; ++i) {
    snprintf(pcStr, sizeof(pcStr), "%d %u %d %d %d %d %c",
             sensorInfoData.z_SensorInfoDataPoint[i].xh_PointCloudX,
             sensorInfoData.z_SensorInfoDataPoint[i].h_PointCloudY,
             sensorInfoData.z_SensorInfoDataPoint[i].xh_PointCloudZ,
             sensorInfoData.z_SensorInfoDataPoint[i].xh_velocity,
             sensorInfoData.z_SensorInfoDataPoint[i].xh_snr,
             sensorInfoData.z_SensorInfoDataPoint[i].xh_noise, '\n');

    HAL_Print((const char *)pcStr);
    HAL_Print((const char *)testnl);
  }
}

void print_error_message(SINT32 result, const char *apiName) {
  if (result != 0) {
    char errMsg[64];
    snprintf(errMsg, sizeof(errMsg), "Error %d in %s\n", (int)result, apiName);
    HAL_Print(errMsg);
  }
}

void GROUP1_IRQHandler(void) {
  uint32_t gpioB =
      DL_GPIO_getEnabledInterruptStatus(GPIOB, CFG_PRESENCE_DET_PIN);

  if (gpioB & CFG_PRESENCE_DET_PIN) {
    isPresenceDetected = ml_presDetStatusGetApi(0);
    DL_GPIO_clearInterruptStatus(GPIOB, CFG_PRESENCE_DET_PIN);

    /* Glow LED and enable LCD if Presence is detected */
    if (isPresenceDetected) {
      HAL_enableLCD();
      DL_LCD_enable(LCD);
      DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_LED3_PIN);
    }

    else {
      HAL_disableLCD();
      DL_LCD_disable(LCD);
      DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_LED3_PIN);
    }
  }
}

int main(void) {

  T_ML_CLIENT_CALLBACK_DATA_STRUCT mspm0callbacks;

  SYSCFG_DL_init();

  NVIC_EnableIRQ(CFG_INT_IRQN);

  HAL_configLCD_Pin();

  MSPM0HAL_initCbkFunctions(&mspm0callbacks);

  // initialize device params for WMOD

  // set to WMOD device
  mspm0callbacks.c_DeviceType = 0;
  // set interface type to SPI
  mspm0callbacks.c_DeviceIfType = 0;
  // enable api error check
  mspm0callbacks.c_ApiErrChkDis = 0;
  // disable debug logging
  mspm0callbacks.c_ApiDbglogEn = 0;
  /* Set Timeout for 10ms */
  mspm0callbacks.h_ApiRespTimeoutMs = 2000;

  res = ml_mmWaveULinkInit(1, &mspm0callbacks);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_mmWaveLinkInit");
    exit(1);
  }

  M_ML_DEVICE_CONFIG_DATA_STRUCT powerCfg;
  powerCfg.c_SopConfig = 1;
  powerCfg.c_PowerCfg = 0; // pull reset low
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  HAL_Delay(10000);

  powerCfg.c_PowerCfg = 1; // pull reset high
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  HAL_Delay(1250000); // 125ms: WMOD cold-boot time after nRESET release

  /* Send Get Status Comand */
  powerCfg.c_PowerCfg = 3; // set wake up high
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  res = ml_uDFPStatusGetApi(0, &status, &error);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_uDFPStatusGetApi");
    exit(1);
  }

  powerCfg.c_PowerCfg = 2; // set wake up low
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  HAL_Delay(40000);

  /* Send Get Version Command */
  powerCfg.c_PowerCfg = 3; // set wake up high
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  res = ml_uDFPVersionGetApi(0, &version, &error);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_uDFPVersionGetApi");
    exit(1);
  }

  powerCfg.c_PowerCfg = 2; // set wake up low
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  /* Stop the Sensor */
  M_ML_SENS_START_STOP_CMD_DATA sensorStartStop;
  sensorStartStop.h_SensStartStopCfg.c_SensorStartFeMode.bits.b2_DevOpMode =
      2;                                                        // verbose mode
  sensorStartStop.h_SensStartStopCfg.c_SensorStartStopMode = 0; // stop

  HAL_Delay(15000000);

  powerCfg.c_PowerCfg = 3; // set wake up high
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  res = ml_sensorStartStopApi(0, &sensorStartStop, &error);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_sensorStartStopApi");
    exit(1);
  }

  powerCfg.c_PowerCfg = 2; // set wake up low
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  HAL_Delay(10000000);

  /* Configure the Sensor */
  M_ML_SENS_CFG_CMD_DATA sensorConfig;

  /* --- Basic mode configuration --- */
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b8_DevSleepHoldTime_ms =
      20; // 10 ms
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b1_StoreCfgToFlashForAutoMode =
      0; // DO NOT store config to flash
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b1_RunBootCalib =
      0; // read factory calibration data from flash
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b4_UpdateRate =
      5; // 5hz update rate
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b1_StaticObjRemovalDisable =
      0; // enable static object removal
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b4_DetectionSensitivity = 5;
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b3_MotionSensitivity = 0;
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b1_HighPowerMode =
      0; // high power boost mode disabled
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b4_MaxRange = 15;
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b1_SensorLocation =
      1;                                                       // outdoor sensor
  sensorConfig.z_SensorModeCfg.w_BasicConf.bits.b1_Region = 0; // FCC/CE region

  /* --- Advanced mode configuration --- */
  sensorConfig.z_SensorModeCfg.h_AdvanceConf.b16_Conf = 0;
  sensorConfig.z_SensorModeCfg.h_AdvanceConf.bits.b1_GpioMode = 1; // pulse mode

  /* --- Sensor mount configuration --- */
  sensorConfig.z_SensorMountCfg.h_SensPosOffsetX = 0;
  sensorConfig.z_SensorMountCfg.h_SensPosOffsetY = 0;
  sensorConfig.z_SensorMountCfg.h_SensPosOffsetZ = 0;
  sensorConfig.z_SensorMountCfg.c_SensTiltAzimuth = 0;
  sensorConfig.z_SensorMountCfg.c_SensTiltElevation = 0;
  sensorConfig.z_SensorMountCfg.c_NumSensorRegions = 0x01;
  sensorConfig.z_SensorMountCfg.c_SensorRegionTypeSel.b8_Conf = 0;

  /* --- Sensor plane region configuration --- */
  sensorConfig.z_SensorPlaneRegionCfg[0].z_SensorXYZPlaneRegionCfg.xh_RegXMin =
      -50;
  sensorConfig.z_SensorPlaneRegionCfg[0].z_SensorXYZPlaneRegionCfg.xh_RegXMax =
      50;
  sensorConfig.z_SensorPlaneRegionCfg[0].z_SensorXYZPlaneRegionCfg.h_RegYMin =
      1;
  sensorConfig.z_SensorPlaneRegionCfg[0].z_SensorXYZPlaneRegionCfg.h_RegYMax =
      100;
  sensorConfig.z_SensorPlaneRegionCfg[0].z_SensorXYZPlaneRegionCfg.h_RegZMin =
      1;
  sensorConfig.z_SensorPlaneRegionCfg[0].z_SensorXYZPlaneRegionCfg.h_RegZMax =
      100;

  /* Send Sensor Configuration Command */
  powerCfg.c_PowerCfg = 3; // set wake up high
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  res = ml_sensorConfigApi(0, &sensorConfig, &error);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_sensorConfigApi");
    exit(1);
  }

  powerCfg.c_PowerCfg = 2; // set wake up low
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  /* Start the Sensor */
  sensorStartStop.h_SensStartStopCfg.c_SensorStartStopMode = 1; // start

  powerCfg.c_PowerCfg = 3; // set wake up high
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  res = ml_sensorStartStopApi(0, &sensorStartStop, &error);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_sensorStartStopApi");
    exit(1);
  }

  powerCfg.c_PowerCfg = 2; // set wake up low
  res = ml_devicePowerCtrlApi(0, &powerCfg);

  if (res != M_RL_RET_CODE_OK) {
    print_error_message(res, "ml_devicePowerCtrlApi");
    exit(1);
  }

  while (1) {

    /*When Presence is detected, Send Get Sensor Info Command */
    if (isPresenceDetected) {
      isPresenceDetected = 0;
      powerCfg.c_PowerCfg = 3; // set wake up high
      res = ml_devicePowerCtrlApi(0, &powerCfg);

      if (res != M_RL_RET_CODE_OK) {
        print_error_message(res, "ml_devicePowerCtrlApi");
        exit(1);
      }

      res = ml_sensorInfoGetApi(0, &sensorInfoData, &error);

      if (res != M_RL_RET_CODE_OK) {
        print_error_message(res, "ml_sensorInfoGetApi");
        exit(1);
      }

      if (sensorInfoData.c_ZoneOccupancy & 1)
        DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_LED4_PIN);

      powerCfg.c_PowerCfg = 2; // set wake up low
      res = ml_devicePowerCtrlApi(0, &powerCfg);

      if (res != M_RL_RET_CODE_OK) {
        print_error_message(res, "ml_devicePowerCtrlApi");
        exit(1);
      }
    }
  }
}
