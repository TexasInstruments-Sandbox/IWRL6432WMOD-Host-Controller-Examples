/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0L222X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_SPI_0_init();
    SYSCFG_DL_CRCP_init();
    SYSCFG_DL_SYSTICK_init();
    SYSCFG_DL_LCD_init();
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_GPIO_reset(GPIOC);
    DL_UART_Main_reset(UART_0_INST);
    DL_SPI_reset(SPI_0_INST);
    DL_CRCP_reset(CRCP0);

    DL_LCD_reset(LCD);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_GPIO_enablePower(GPIOC);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_SPI_enablePower(SPI_0_INST);
    DL_CRCP_enablePower(CRCP0);

    DL_LCD_enablePower(LCD);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_0_IOMUX_PICO, GPIO_SPI_0_IOMUX_PICO_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_SPI_0_IOMUX_POCI, GPIO_SPI_0_IOMUX_POCI_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_0_IOMUX_CS0, GPIO_SPI_0_IOMUX_CS0_FUNC);
    
	DL_GPIO_initPeripheralOutputFunctionFeatures(
		 GPIO_SPI_0_IOMUX_SCLK, GPIO_SPI_0_IOMUX_SCLK_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_LEDS_LED3_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LEDS_LED1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LEDS_LED2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LEDS_LED4_IOMUX);

    DL_GPIO_initDigitalOutput(CFG_WAKE_UP_IOMUX);

    DL_GPIO_initDigitalInputFeatures(CFG_SPI_BUSY_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(CFG_PRESENCE_DET_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(CFG_nRESET_IOMUX);

    DL_GPIO_clearPins(GPIOA, GPIO_LEDS_LED4_PIN |
		CFG_WAKE_UP_PIN);
    DL_GPIO_setPins(GPIOA, GPIO_LEDS_LED3_PIN |
		GPIO_LEDS_LED1_PIN |
		GPIO_LEDS_LED2_PIN);
    DL_GPIO_enableOutput(GPIOA, GPIO_LEDS_LED3_PIN |
		GPIO_LEDS_LED1_PIN |
		GPIO_LEDS_LED2_PIN |
		GPIO_LEDS_LED4_PIN |
		CFG_WAKE_UP_PIN);
    DL_GPIO_clearPins(GPIOB, CFG_nRESET_PIN);
    DL_GPIO_enableOutput(GPIOB, CFG_nRESET_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOB, DL_GPIO_PIN_2_EDGE_RISE_FALL);
    DL_GPIO_clearInterruptStatus(GPIOB, CFG_PRESENCE_DET_PIN);
    DL_GPIO_enableInterrupt(GPIOB, CFG_PRESENCE_DET_PIN);

}


SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    DL_SYSCTL_setMCLKDivider(DL_SYSCTL_MCLK_DIVIDER_DISABLE);

}


static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.24
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_9600_BAUD, UART_0_FBRD_32_MHZ_9600_BAUD);


    /* Configure FIFOs */
    DL_UART_Main_enableFIFOs(UART_0_INST);
    DL_UART_Main_setTXFIFOThreshold(UART_0_INST, DL_UART_TX_FIFO_LEVEL_1_4_EMPTY);

    DL_UART_Main_enable(UART_0_INST);
}

static const DL_SPI_Config gSPI_0_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO4_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_16,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
    .chipSelectPin = DL_SPI_CHIP_SELECT_0,
};

static const DL_SPI_ClockConfig gSPI_0_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_SPI_0_init(void) {
    DL_SPI_setClockConfig(SPI_0_INST, (DL_SPI_ClockConfig *) &gSPI_0_clockConfig);

    DL_SPI_init(SPI_0_INST, (DL_SPI_Config *) &gSPI_0_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     1000000 = (32000000)/((1 + 15) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI_0_INST, 15);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI_0_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(SPI_0_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_CRCP_init(void)
{
    DL_CRCP_setPolynomial(CRCP0, DL_CRCP_CRCPOLY_POLYNOMIAL_32_JAMCRC);
    DL_CRCP_init(CRCP0, DL_CRCP_POLYNOMIAL_SIZE_32, DL_CRCP_BIT_REVERSED,
        DL_CRCP_INPUT_ENDIANESS_LITTLE_ENDIAN, DL_CRCP_OUTPUT_BYTESWAP_DISABLED);

    DL_CRCP_setSeed32(CRCP0, CRCP_SEED);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /* Initialize the period to 524.29 ms */
    DL_SYSTICK_init(16777215);
    /* Enable the SysTick and start counting */
    DL_SYSTICK_enable();
}

static const DL_LCD_Config gLCDConfig = {
    .frequencyDivider   = DL_LCD_FREQ_DIVIDE_4,
    .muxRate            = DL_LCD_MUX_RATE_4,
    .lowPowerWaveform   = DL_LCD_WAVEFORM_POWERMODE_STANDARD
};

SYSCONFIG_WEAK void SYSCFG_DL_LCD_init(void)
{
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_24);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_42);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_43);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_44);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_58);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_57);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_56);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_55);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_36);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_37);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_38);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_18);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_19);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_20);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_23);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_39);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_40);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_41);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_54);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_53);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_52);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_51);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_50);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_49);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_48);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_47);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_46);
    DL_LCD_setPinAsLCDFunction(LCD, DL_LCD_SEGMENT_LINE_45);
    DL_LCD_init(LCD, (DL_LCD_Config *) &gLCDConfig);
    DL_LCD_turnSegmentsOn(LCD);
    DL_LCD_setBiasVoltageSource(LCD, DL_LCD_BIAS_VOLTAGE_SOURCE_AVDD);
    DL_LCD_setR33source(LCD, DL_LCD_R33_SOURCE_EXTERNAL);
    DL_LCD_enableInternalBias(LCD);
    DL_LCD_setInternalBiasPowerMode(LCD, DL_LCD_POWER_MODE_LOW);

    DL_LCD_clearAllMemoryRegs(LCD); //
    DL_LCD_setPinAsCommon(LCD, DL_LCD_SEGMENT_LINE_24, DL_LCD_COM_0);
    DL_LCD_setPinAsCommon(LCD, DL_LCD_SEGMENT_LINE_42, DL_LCD_COM_1);
    DL_LCD_setPinAsCommon(LCD, DL_LCD_SEGMENT_LINE_43, DL_LCD_COM_2);
    DL_LCD_setPinAsCommon(LCD, DL_LCD_SEGMENT_LINE_44, DL_LCD_COM_3);
    DL_LCD_enable(LCD);
}

