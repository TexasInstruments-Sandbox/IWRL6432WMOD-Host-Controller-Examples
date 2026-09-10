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
#include "ti_msp_dl_config.h"

SINT32 HAL_Delay(UINT32 w_delayInP1Us);
SINT32 HAL_Print(const char format[], ...);
void HAL_configLCD_Pin(void);
void HAL_enableLCD(void);
void HAL_disableLCD(void);

#define SYSTICK_100_NS (3.2)
#define ASCII_DIGIT_OFFSET (48)
#define ASCII_LETTER_OFFSET (65)

typedef struct {
  uint32_t pin1;
  uint32_t pin2;
  uint32_t pin3;
  uint32_t pin4;
} LCD_pin;

typedef enum {
  GPIO_LOW = 0,
  GPIO_HIGH = 1,
} GPIOLevel;

/* Onboard LCD positions 1-6 */
LCD_pin gLCDPinPosition1;
LCD_pin gLCDPinPosition2;
LCD_pin gLCDPinPosition3;
LCD_pin gLCDPinPosition4;
LCD_pin gLCDPinPosition5;
LCD_pin gLCDPinPosition6;

/* LCD memory map for numeric digits */
const char digit[10][4] = {
    {0x07, 0x09, 0x08, 0x0A}, /* "0" LCD segments a+b+c+d+e+f+k+q */
    {0x00, 0x00, 0x00, 0x0A}, /* "1" */
    {0x03, 0x0A, 0x00, 0x0C}, /* "2" */
    {0x01, 0x0A, 0x00, 0x0E}, /* "3" */
    {0x04, 0x02, 0x00, 0x0E}, /* "4" */
    {0x05, 0x0A, 0x01, 0x00}, /* "5" */
    {0x07, 0x0A, 0x00, 0x06}, /* "6" */
    {0x00, 0x08, 0x00, 0x0A}, /* "7" */
    {0x07, 0x0A, 0x00, 0x0E}, /* "8" */
    {0x05, 0x0A, 0x00, 0x0E}  /* "9" */
};

/* LCD memory map for uppercase letters */
const char alphabetUpper[26][4] = {
    {0x06, 0x0A, 0x00, 0x0E}, /* "A" LCD segments a+b+c+e+f+g+m */
    {0x01, 0x08, 0x06, 0x0E}, /* "B" */
    {0x07, 0x08, 0x00, 0x00}, /* "C" */
    {0x01, 0x08, 0x06, 0x0A}, /* "D" */
    {0x07, 0x0A, 0x00, 0x00}, /* "E" */
    {0x06, 0x0A, 0x00, 0x00}, /* "F" */
    {0x07, 0x08, 0x00, 0x06}, /* "G" */
    {0x06, 0x02, 0x00, 0x0E}, /* "H" */
    {0x01, 0x08, 0x06, 0x00}, /* "I" */
    {0x03, 0x00, 0x00, 0x0A}, /* "J" */
    {0x06, 0x02, 0x09, 0x00}, /* "K" */
    {0x07, 0x00, 0x00, 0x00}, /* "L" */
    {0x06, 0x04, 0x08, 0x0A}, /* "M" */
    {0x06, 0x04, 0x01, 0x0A}, /* "N" */
    {0x07, 0x08, 0x00, 0x0A}, /* "O" */
    {0x06, 0x0A, 0x00, 0x0C}, /* "P" */
    {0x07, 0x08, 0x01, 0x0A}, /* "Q" */
    {0x06, 0x0A, 0x01, 0x0C}, /* "R" */
    {0x05, 0x0A, 0x00, 0x06}, /* "S" */
    {0x00, 0x08, 0x06, 0x00}, /* "T" */
    {0x07, 0x00, 0x00, 0x0A}, /* "U" */
    {0x06, 0x01, 0x08, 0x00}, /* "V" */
    {0x06, 0x01, 0x01, 0x0A}, /* "W" */
    {0x00, 0x05, 0x09, 0x00}, /* "X" */
    {0x05, 0x02, 0x00, 0x0E}, /* "Y" */
    {0x01, 0x09, 0x08, 0x00}  /* "Z" */
};

/**
 * @brief Print a formatted string to the console through UART.
 *
 * @param[in] format - The format string.
 * @param[in] ... - The arguments.
 *
 * @return SINT32 - The return status.
 *
 */
SINT32 HAL_Print(const char format[], ...) {
  // char buffer[256];

  // va_list args;
  // va_start(args,format);
  // vsprintf((char*)buffer, format, args);
  // va_end(args);
  // char *bufferPtr = (char*)buffer;

  // while (*bufferPtr) {
  //     DL_UART_transmitDataBlocking(UART_0_INST, *bufferPtr++);
  // }

  return 1;
}

/**
 * @brief Delay function
 *
 * @param[in] w_delayInP1Us - Delay in 0.1 us
 *
 * @return T_RETURNTYPE - Signed Return status, Success - 0, Failure - Error
 * code
 */
SINT32 HAL_Delay(UINT32 w_delayInP1Us) {
  const uint32_t maxChunk =
      5000000u; /* 500ms max per chunk (24-bit SYSTICK limit) */
  while (w_delayInP1Us > maxChunk) {
    uint32_t counts = (uint32_t)(SYSTICK_100_NS * (float)maxChunk);
    uint32_t start = DL_SYSTICK_getValue();
    while (((start - DL_SYSTICK_getValue()) & 0x00FFFFFF) < counts) {
    };
    w_delayInP1Us -= maxChunk;
  }
  uint32_t counts = (uint32_t)(SYSTICK_100_NS * (float)w_delayInP1Us);
  uint32_t start = DL_SYSTICK_getValue();
  while (((start - DL_SYSTICK_getValue()) & 0x00FFFFFF) < counts) {
  };
  return 0;
}

/**
 * @brief Get the current timestamp in microseconds.
 *
 * @return UINT32 - The current timestamp in microseconds.
 */
SINT64 HAL_TimeStamp(void) {
  return ((DL_SYSTICK_getPeriod() - DL_SYSTICK_getValue()) / 32);
}

/**
 * @brief Get the SPI_BUSY status of the target device
 *
 * @param[in] c_devIndex - Device Index
 *
 * @return UINT32 - The SPI_BUSY status of the device (1 - Busy, 0 - Not Busy)
 */
SINT32 HAL_GetSPIBusySts(UINT8 c_devIndex) {
  return (DL_GPIO_readPins(CFG_SPI_BUSY_PORT, CFG_SPI_BUSY_PIN) ? 1 : 0);
}

/**
 * @brief Compute the CRC of given data
 *
 * @param[in] c_data - pointer to data
 * @param[in] w_dataLength - length of data buffer
 * @param[in] crcType - CRC Type
 * @param[out] crc - computed CRC
 *
 * @return int Success - 0, Failure - Error Code
 */
SINT32 HAL_CRCCompute(UINT8 *c_data, UINT32 w_dataLength, UINT8 crcType,
                      UINT8 *crc) {
  DL_CRCP_setSeed32(CRCP0, 0xFFFFFFFF);

  for (int i = 0; i < w_dataLength; i++) {
    DL_CRCP_feedData8(CRCP0, c_data[i]);
  }

  uint32_t crcResult = (DL_CRCP_getResult32(CRCP0) ^
                        (0xFFFFFFFF)); // computeCRC(c_data,w_dataLength,32);

  crc[0] = crcResult & 0xFF;
  crc[1] = (crcResult & 0xFF00) >> 8;
  crc[2] = (crcResult & 0xFF0000) >> 16;
  crc[3] = (crcResult & 0xFF000000) >> 24;

  return 0;
}

/**
 * @brief Open the communication interface
 *
 * @param[in] c_deviceIndex - Device Index
 * @param[in] w_flags - Flags
 *
 */
void *HAL_ComIfOpen(UINT8 c_deviceIndex, UINT32 w_flags) {
  /* Enable module */
  DL_SPI_enable(SPI_0_INST);

  return SPI_0_INST;
}

/**
 * @brief Close the communication interface
 *
 * @param[in] c_deviceIndex - Device Index
 * @param[in] w_flags - Flags
 *
 */
SINT32 HAL_ComIfClose(T_ML_COMIF_HDL p_fd) {
  DL_SPI_disable((SPI_Regs *)p_fd);

  return 0;
}

/**
 * @brief Read data from the communication interface
 *
 * @param[in] p_fd - Handle to access the communication interface
 * @param[out] p_rxBuffer - Address of RX read Buffer
 * @param[in] p_txBuffer - Address of TX Pattern buffer (optional)
 * @param[in] w_len - Read size in bytes
 *
 * @return SINT32 Length of received data
 */
SINT32 HAL_ComIfRead(T_ML_COMIF_HDL p_fd, UINT8 *p_rxBuffer, UINT8 *p_txBuffer,
                     UINT32 w_len) {
  SPI_Regs *SPI_INST = (SPI_Regs *)p_fd;

  uint16_t dummyBuffer[4];
  /* Flush Rx FIFO */
  DL_SPI_drainRXFIFO16(SPI_INST, dummyBuffer, 4);

  SINT32 respLen = 0;
  uint16_t *tempRxPtr;
  tempRxPtr = (uint16_t *)p_rxBuffer;
  uint16_t *tempTxPtr;
  tempTxPtr = (uint16_t *)p_txBuffer;

  /* Divide length by 2 as word size is 16 bits */
  w_len = w_len / 2;

  while (w_len--) {
    DL_SPI_fillTXFIFO16(SPI_INST, tempTxPtr++, 1);

    while (DL_SPI_isBusy(SPI_INST)) {
    };

    *tempRxPtr++ = DL_SPI_receiveDataBlocking16(SPI_INST);
    respLen++;
  }

  /* Return number of bytes read */
  return 2 * respLen;
}

/**
 * @brief Write Data to Communication interface
 *
 * @b Description @n
 * This is a function can be used to write to communication interface
 *
 * @param[in] p_fd - Handle to access the communication interface
 * @param[out] p_rxBuffer - Address of RX Pattern buffer (optional)
 * @param[in] p_txBuffer - Address of TX write Buffer
 * @param[in] w_len - Read size in bytes
 *
 * @return SINT32 Length of data transmitted
 */
SINT32 HAL_ComIfWrite(T_ML_COMIF_HDL p_fd, UINT8 *p_rxBuffer, UINT8 *p_txBuffer,
                      UINT32 w_len) {

  SPI_Regs *SPI_INST = (SPI_Regs *)p_fd;

  SINT32 respLen = 0;

  uint16_t *tempRxPtr;
  tempRxPtr = (uint16_t *)p_rxBuffer;
  uint16_t *tempTxPtr;
  tempTxPtr = (uint16_t *)p_txBuffer;

  /* Divide length by 2 as word size is 16 bits */
  w_len = w_len / 2;

  while (w_len--) {
    DL_SPI_fillTXFIFO16(SPI_INST, tempTxPtr++, 1);

    while (DL_SPI_isBusy(SPI_INST)) {
    };

    *tempRxPtr++ = DL_SPI_receiveDataBlocking16(SPI_INST);
    respLen++;
  }

  return 2 * respLen;
}

/**
 * @brief Get the status of device's PRESENCE_DETECT GPIO
 *
 * @param[in] c_devIndex - Device Index
 *
 * @return UINT32 - Value 0 - PRESENCE_DETECT LOW, 1 - PRESENCE_DETECT HIGH
 */
SINT32 HAL_GetPresDetSts(UINT8 c_devIndex) {
  return (DL_GPIO_readPins(CFG_PRESENCE_DET_PORT, CFG_PRESENCE_DET_PIN) ? 1
                                                                        : 0);
}

/* Dummy Definitions */
SINT32 HAL_OsiMutexCreate(T_ML_OSI_MUTEX_HDL *p_mutexHdl, SINT8 *p_name) {
  return 0;
}

SINT32 HAL_OsiMutexDelete(T_ML_OSI_MUTEX_HDL p_mutexHdl) { return 0; }

SINT32 HAL_OsiMutexLock(T_ML_OSI_MUTEX_HDL p_mutexHdl, UINT32 w_timeoutUs) {
  return 0;
}

SINT32 HAL_OsiMutexUnLock(T_ML_OSI_MUTEX_HDL p_mutexHdl) { return 0; }

SINT32 HAL_OsiSemCreate(T_ML_OSI_SEM_HDL *p_semHdl, UINT8 *p_name) { return 0; }

SINT32 HAL_OsiSemDelete(T_ML_OSI_SEM_HDL p_semHdl) { return 0; }

SINT32 HAL_OsiSemSignal(T_ML_OSI_SEM_HDL p_semHdl) { return 0; }

SINT32 HAL_OsiSemWait(T_ML_OSI_SEM_HDL p_semHdl, UINT32 w_timeoutUs) {
  return 0;
}

SINT32 HAL_CfgDevicePins(UINT8 c_devIndex, UINT8 c_powerCfg) {
  if (c_powerCfg == 0) {
    DL_GPIO_clearPins(CFG_nRESET_PORT, CFG_nRESET_PIN);
  }

  else if (c_powerCfg == 1) {
    DL_GPIO_setPins(CFG_nRESET_PORT, CFG_nRESET_PIN);
  }

  else if (c_powerCfg == 2) {
    DL_GPIO_clearPins(CFG_WAKE_UP_PORT, CFG_WAKE_UP_PIN);
  }

  else if (c_powerCfg == 3) {
    DL_GPIO_setPins(CFG_WAKE_UP_PORT, CFG_WAKE_UP_PIN);
  }

  return 0;
}

SINT32 HAL_MemCpy(T_ML_PLT_HDL p_destPtr, T_ML_PLT_HDL p_srcPtr,
                  UINT32 w_numBytes) {
  return 0;
}

SINT32 HAL_MaskPresDet(UINT8 c_devIndex) { return 0; }

SINT32 HAL_UnMaskPresDet(UINT8 c_devIndex) { return 0; }

void MSPM0HAL_initCbkFunctions(T_ML_CLIENT_CALLBACK_DATA_STRUCT *pCbk) {
  pCbk->z_DbgCb.p_Print = &HAL_Print;

  pCbk->z_PltfCb.p_Delay = &HAL_Delay;
  pCbk->z_PltfCb.p_TimeStamp = &HAL_TimeStamp;
  pCbk->z_PltfCb.p_GetSPIBusySts = &HAL_GetSPIBusySts;
  pCbk->z_PltfCb.p_CRCCompute = &HAL_CRCCompute;
  pCbk->z_PltfCb.p_GetPresDetSts = &HAL_GetPresDetSts;

  pCbk->z_ComIfCb.p_ComIfOpen = &HAL_ComIfOpen;
  pCbk->z_ComIfCb.p_ComIfClose = &HAL_ComIfClose;
  pCbk->z_ComIfCb.p_ComIfRead = &HAL_ComIfRead;
  pCbk->z_ComIfCb.p_ComIfWrite = &HAL_ComIfWrite;

  pCbk->z_OsiCb.z_Mutex.p_OsiMutexCreate = &HAL_OsiMutexCreate;
  pCbk->z_OsiCb.z_Mutex.p_OsiMutexDelete = &HAL_OsiMutexDelete;
  pCbk->z_OsiCb.z_Mutex.p_OsiMutexLock = &HAL_OsiMutexLock;
  pCbk->z_OsiCb.z_Mutex.p_OsiMutexUnLock = &HAL_OsiMutexUnLock;

  pCbk->z_OsiCb.z_Semp.p_OsiSemCreate = &HAL_OsiSemCreate;
  pCbk->z_OsiCb.z_Semp.p_OsiSemDelete = &HAL_OsiSemDelete;
  pCbk->z_OsiCb.z_Semp.p_OsiSemSignal = &HAL_OsiSemSignal;
  pCbk->z_OsiCb.z_Semp.p_OsiSemWait = &HAL_OsiSemWait;

  pCbk->z_PltfCb.p_MaskPresDet = &HAL_MaskPresDet;
  pCbk->z_PltfCb.p_UnMaskPresDet = &HAL_UnMaskPresDet;
  pCbk->z_PltfCb.p_MemCpy = &HAL_MemCpy;
  pCbk->z_PltfCb.p_CfgDevicePins = &HAL_CfgDevicePins;
}

void HAL_LCDshowChar(LCD_Regs *lcd, char ch, LCD_pin lcdPinPosition) {
  uint32_t pin1 = lcdPinPosition.pin1;
  uint32_t pin2 = lcdPinPosition.pin2;
  uint32_t pin3 = lcdPinPosition.pin3;
  uint32_t pin4 = lcdPinPosition.pin4;

  /* Divide by 2 because mux rate < 5 */
  uint32_t pin1memIdx = pin1 / 2;
  uint32_t pin2memIdx = pin2 / 2;
  uint32_t pin3memIdx = pin3 / 2;
  uint32_t pin4memIdx = pin4 / 2;

  uint8_t mem;
  uint32_t memMask;

  if (ch >= '0' && ch <= '9') {
    /* Write digits */
    if (pin1 % 2) {
      /* Even memory location */
      mem = DL_LCD_getMemory(LCD, pin1memIdx) & 0x0F;
      memMask = (mem | digit[ch - ASCII_DIGIT_OFFSET][0] << 4);
    } else {
      /* Odd memory location */
      mem = DL_LCD_getMemory(LCD, pin1memIdx) & 0xF0;
      memMask = (mem | digit[ch - ASCII_DIGIT_OFFSET][0]);
    }
    DL_LCD_writeMemory(LCD, pin1memIdx, memMask);

    if (pin2 % 2) {
      mem = DL_LCD_getMemory(LCD, pin2memIdx) & 0x0F;
      memMask = (mem | digit[ch - ASCII_DIGIT_OFFSET][1] << 4);
    } else {
      mem = DL_LCD_getMemory(LCD, pin2memIdx) & 0xF0;
      memMask = (mem | digit[ch - ASCII_DIGIT_OFFSET][1]);
    }
    DL_LCD_writeMemory(LCD, pin2memIdx, memMask);

    if (pin3 % 2) {
      mem = DL_LCD_getMemory(LCD, pin3memIdx) & 0x0F;
      memMask = (mem | digit[ch - ASCII_DIGIT_OFFSET][2] << 4);
    } else {
      mem = DL_LCD_getMemory(LCD, pin3memIdx) & 0xF0;
      memMask = (mem | digit[ch - ASCII_DIGIT_OFFSET][2]);
    }
    DL_LCD_writeMemory(LCD, pin3memIdx, memMask);

    if (pin4 % 2) {
      mem = DL_LCD_getMemory(LCD, pin4memIdx) & 0x0F;
      memMask = (mem | digit[ch - ASCII_DIGIT_OFFSET][3] << 4);
    } else {
      mem = DL_LCD_getMemory(LCD, pin4memIdx) & 0xF0;
      memMask = (mem | digit[ch - ASCII_DIGIT_OFFSET][3]);
    }
    DL_LCD_writeMemory(LCD, pin4memIdx, memMask);

  } else if (ch >= 'A' && ch <= 'Z') {
    /* Write letters */
    if (pin1 % 2) {
      /* Even memory location */
      mem = DL_LCD_getMemory(LCD, pin1memIdx) & 0x0F;
      memMask = (mem | alphabetUpper[ch - ASCII_LETTER_OFFSET][0] << 4);
    } else {
      /* Odd memory location */
      mem = DL_LCD_getMemory(LCD, pin1memIdx) & 0xF0;
      memMask = (mem | alphabetUpper[ch - ASCII_LETTER_OFFSET][0]);
    }
    DL_LCD_writeMemory(LCD, pin1memIdx, memMask);

    if (pin2 % 2) {
      mem = DL_LCD_getMemory(LCD, pin2memIdx) & 0x0F;
      memMask = (mem | alphabetUpper[ch - ASCII_LETTER_OFFSET][1] << 4);
    } else {
      mem = DL_LCD_getMemory(LCD, pin2memIdx) & 0xF0;
      memMask = (mem | alphabetUpper[ch - ASCII_LETTER_OFFSET][1]);
    }
    DL_LCD_writeMemory(LCD, pin2memIdx, memMask);

    if (pin3 % 2) {
      mem = DL_LCD_getMemory(LCD, pin3memIdx) & 0x0F;
      memMask = (mem | alphabetUpper[ch - ASCII_LETTER_OFFSET][2] << 4);
    } else {
      mem = DL_LCD_getMemory(LCD, pin3memIdx) & 0xF0;
      memMask = (mem | alphabetUpper[ch - ASCII_LETTER_OFFSET][2]);
    }
    DL_LCD_writeMemory(LCD, pin3memIdx, memMask);

    if (pin4 % 2) {
      mem = DL_LCD_getMemory(LCD, pin4memIdx) & 0x0F;
      memMask = (mem | alphabetUpper[ch - ASCII_LETTER_OFFSET][3] << 4);
    } else {
      mem = DL_LCD_getMemory(LCD, pin4memIdx) & 0xF0;
      memMask = (mem | alphabetUpper[ch - ASCII_LETTER_OFFSET][3]);
    }
    DL_LCD_writeMemory(LCD, pin4memIdx, memMask);
  }
}

void HAL_configLCD_Pin() {
  /* Map LCD segments to position on onboard LCD (1-6) */
  gLCDPinPosition1.pin1 = DL_LCD_SEGMENT_LINE_58;
  gLCDPinPosition1.pin2 = DL_LCD_SEGMENT_LINE_57;
  gLCDPinPosition1.pin3 = DL_LCD_SEGMENT_LINE_56;
  gLCDPinPosition1.pin4 = DL_LCD_SEGMENT_LINE_55;

  gLCDPinPosition2.pin1 = DL_LCD_SEGMENT_LINE_36;
  gLCDPinPosition2.pin2 = DL_LCD_SEGMENT_LINE_37;
  gLCDPinPosition2.pin3 = DL_LCD_SEGMENT_LINE_38;
  gLCDPinPosition2.pin4 = DL_LCD_SEGMENT_LINE_18;

  gLCDPinPosition3.pin1 = DL_LCD_SEGMENT_LINE_19;
  gLCDPinPosition3.pin2 = DL_LCD_SEGMENT_LINE_20;
  gLCDPinPosition3.pin3 = DL_LCD_SEGMENT_LINE_23;
  gLCDPinPosition3.pin4 = DL_LCD_SEGMENT_LINE_39;

  gLCDPinPosition4.pin1 = DL_LCD_SEGMENT_LINE_40;
  gLCDPinPosition4.pin2 = DL_LCD_SEGMENT_LINE_41;
  gLCDPinPosition4.pin3 = DL_LCD_SEGMENT_LINE_54;
  gLCDPinPosition4.pin4 = DL_LCD_SEGMENT_LINE_53;

  gLCDPinPosition5.pin1 = DL_LCD_SEGMENT_LINE_52;
  gLCDPinPosition5.pin2 = DL_LCD_SEGMENT_LINE_51;
  gLCDPinPosition5.pin3 = DL_LCD_SEGMENT_LINE_50;
  gLCDPinPosition5.pin4 = DL_LCD_SEGMENT_LINE_49;

  gLCDPinPosition6.pin1 = DL_LCD_SEGMENT_LINE_48;
  gLCDPinPosition6.pin2 = DL_LCD_SEGMENT_LINE_47;
  gLCDPinPosition6.pin3 = DL_LCD_SEGMENT_LINE_46;
  gLCDPinPosition6.pin4 = DL_LCD_SEGMENT_LINE_45;

  HAL_LCDshowChar(LCD, 'D', gLCDPinPosition1);
  HAL_LCDshowChar(LCD, 'E', gLCDPinPosition2);
  HAL_LCDshowChar(LCD, 'T', gLCDPinPosition3);
  HAL_LCDshowChar(LCD, 'E', gLCDPinPosition4);
  HAL_LCDshowChar(LCD, 'C', gLCDPinPosition5);
  HAL_LCDshowChar(LCD, 'T', gLCDPinPosition6);

  DL_LCD_disable(LCD);
}

void HAL_enableLCD(void) { DL_LCD_enable(LCD); }

void HAL_disableLCD(void) { DL_LCD_disable(LCD); }
