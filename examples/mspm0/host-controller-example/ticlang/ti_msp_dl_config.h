/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0L222X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0L222X
#define CONFIG_MSPM0L2228

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           32000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM25)
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM25_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_0_FBRD_32_MHZ_9600_BAUD                                        (21)




/* Defines for SPI_0 */
#define SPI_0_INST                                                         SPI1
#define SPI_0_INST_IRQHandler                                   SPI1_IRQHandler
#define SPI_0_INST_INT_IRQN                                       SPI1_INT_IRQn
#define GPIO_SPI_0_PICO_PORT                                              GPIOB
#define GPIO_SPI_0_PICO_PIN                                       DL_GPIO_PIN_8
#define GPIO_SPI_0_IOMUX_PICO                                   (IOMUX_PINCM29)
#define GPIO_SPI_0_IOMUX_PICO_FUNC                   IOMUX_PINCM29_PF_SPI1_PICO
#define GPIO_SPI_0_POCI_PORT                                              GPIOB
#define GPIO_SPI_0_POCI_PIN                                       DL_GPIO_PIN_7
#define GPIO_SPI_0_IOMUX_POCI                                   (IOMUX_PINCM28)
#define GPIO_SPI_0_IOMUX_POCI_FUNC                   IOMUX_PINCM28_PF_SPI1_POCI
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT                                              GPIOA
#define GPIO_SPI_0_SCLK_PIN                                      DL_GPIO_PIN_17
#define GPIO_SPI_0_IOMUX_SCLK                                   (IOMUX_PINCM49)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC                   IOMUX_PINCM49_PF_SPI1_SCLK
#define GPIO_SPI_0_CS0_PORT                                               GPIOB
#define GPIO_SPI_0_CS0_PIN                                        DL_GPIO_PIN_6
#define GPIO_SPI_0_IOMUX_CS0                                    (IOMUX_PINCM27)
#define GPIO_SPI_0_IOMUX_CS0_FUNC                     IOMUX_PINCM27_PF_SPI1_CS0



/* Port definition for Pin Group GPIO_LEDS */
#define GPIO_LEDS_PORT                                                   (GPIOA)

/* Defines for LED3: GPIOA.0 with pinCMx 1 on package pin 1 */
#define GPIO_LEDS_LED3_PIN                                       (DL_GPIO_PIN_0)
#define GPIO_LEDS_LED3_IOMUX                                      (IOMUX_PINCM1)
/* Defines for LED1: GPIOA.28 with pinCMx 3 on package pin 3 */
#define GPIO_LEDS_LED1_PIN                                      (DL_GPIO_PIN_28)
#define GPIO_LEDS_LED1_IOMUX                                      (IOMUX_PINCM3)
/* Defines for LED2: GPIOA.29 with pinCMx 4 on package pin 4 */
#define GPIO_LEDS_LED2_PIN                                      (DL_GPIO_PIN_29)
#define GPIO_LEDS_LED2_IOMUX                                      (IOMUX_PINCM4)
/* Defines for LED4: GPIOA.16 with pinCMx 42 on package pin 45 */
#define GPIO_LEDS_LED4_PIN                                      (DL_GPIO_PIN_16)
#define GPIO_LEDS_LED4_IOMUX                                     (IOMUX_PINCM42)
/* Defines for WAKE_UP: GPIOA.30 with pinCMx 5 on package pin 5 */
#define CFG_WAKE_UP_PORT                                                 (GPIOA)
#define CFG_WAKE_UP_PIN                                         (DL_GPIO_PIN_30)
#define CFG_WAKE_UP_IOMUX                                         (IOMUX_PINCM5)
/* Defines for SPI_BUSY: GPIOB.3 with pinCMx 16 on package pin 19 */
#define CFG_SPI_BUSY_PORT                                                (GPIOB)
#define CFG_SPI_BUSY_PIN                                         (DL_GPIO_PIN_3)
#define CFG_SPI_BUSY_IOMUX                                       (IOMUX_PINCM16)
/* Defines for PRESENCE_DET: GPIOB.2 with pinCMx 15 on package pin 18 */
#define CFG_PRESENCE_DET_PORT                                            (GPIOB)
// pins affected by this interrupt request:["PRESENCE_DET"]
#define CFG_INT_IRQN                                            (GPIOB_INT_IRQn)
#define CFG_INT_IIDX                            (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define CFG_PRESENCE_DET_IIDX                                (DL_GPIO_IIDX_DIO2)
#define CFG_PRESENCE_DET_PIN                                     (DL_GPIO_PIN_2)
#define CFG_PRESENCE_DET_IOMUX                                   (IOMUX_PINCM15)
/* Defines for nRESET: GPIOB.1 with pinCMx 13 on package pin 16 */
#define CFG_nRESET_PORT                                                  (GPIOB)
#define CFG_nRESET_PIN                                           (DL_GPIO_PIN_1)
#define CFG_nRESET_IOMUX                                         (IOMUX_PINCM13)


/* Defines for CRC */
#define CRCP_SEED                                                   (0xFFFFFFFF)
/* Redirects to CRCP_SEED for compatibility between CRC and CRCP modules */
#define CRC_SEED                                                       CRCP_SEED









/* Defines for LCD */
#define LCD_IRQHandler                                            LCD_IRQHandler
#define LCD_INT_IRQN                                                LCD_INT_IRQn


/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_0_init(void);

void SYSCFG_DL_CRCP_init(void);
void SYSCFG_DL_SYSTICK_init(void);
void SYSCFG_DL_LCD_init(void);


#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
