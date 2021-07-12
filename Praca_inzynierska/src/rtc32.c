/**
 * \file
 *
 * \brief RTC32 related functionality implementation.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_rtc32_init RTC32 Init Driver
 * \ingroup doc_driver_rtc32
 *
 * \section doc_driver_rtc32_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

#include <rtc32.h>
#include "config/clock_config.h"
#include "util/delay.h"
#include "ccp.h"
#include "dipswitch.h"
/**
 * \brief Initialize rtc32 interface
 * \return Initialization status.
 */
int8_t RTC_0_init()
{
	VBAT.CTRL = 1 << 1; /* Module Access Enable: enabled */

	ccp_write_io((void *)&(VBAT.CTRL), 1 << 0 /* Reset: enabled */);

	VBAT.CTRL = 1 << 2; /* Crystal Oscillator Failure Detection Enable: enabled */

	/* This delay is needed to give the voltage in the backup system some
	 * time to stabilize before we turn on the oscillator. If we do not
	 * have this delay we may get a failure detection.
	 */
	_delay_us(200);

	VBAT.CTRL = 1 << 3; /* Crystal Oscillator Enable: enabled */

	// VBAT.CTRL = 0 << 4; /* Crystal Oscillator Output Selection: disabled */

	VBAT.CTRL = 1 << 5; /* High ESR Mode: enabled */

	while (!(VBAT.STATUS & VBAT_XOSCRDY_bm))
		;

	// Disable the RTC32 module before setting it up
	RTC32.CTRL = 0;

	RTC32.PER = get_address()*5; /* Period Register: is like address */

	// RTC32.COMP = 0; /* Compare Register: 0 */

	// RTC32.CNT = 0; /* Count Register: 0 */

	while (RTC32.SYNCCTRL > 0)
		;

	RTC32.INTCTRL = RTC32_COMPINTLVL_OFF_gc  /* Interrupt Disabled */
	                | RTC32_OVFINTLVL_HI_gc; /* High Level */

	RTC32.CTRL = 1 << RTC32_ENABLE_bp; /* Enable: enabled */

	while (RTC32.SYNCCTRL > 0)
		;

	return 0;
}


uint8_t vbat_system_check(bool first_time_startup)
{
	uint8_t vbat_status;
	/*
	 * Check if sufficient power was detected on the VBAT input. The brown-
	 * out detector (BBBOD) will be sampled once when the device starts up
	 * and the result is visible as the BBPWR flag.
	 */
	if (VBAT.STATUS & VBAT_BBPWR_bm)
		vbat_status = VBAT_STATUS_NO_POWER;
	else {
		/*
		 * We hav sufficient power, now we check if a power-on-reset
		 * (BBPOR) was detected on VBAT. This is visible from the BBPORF
		 * flag which is also only updated once when the device starts.
		 */
		if (VBAT.STATUS & VBAT_BBPORF_bm) {
			if (first_time_startup)
				vbat_status = VBAT_STATUS_INIT;
			else
				vbat_status = VBAT_STATUS_BBPOR;
		}
		else if (VBAT.STATUS & VBAT_BBBORF_bm)
			vbat_status = VBAT_STATUS_BBBOD;
		else {
			VBAT.CTRL = VBAT_ACCEN_bm;
			if (VBAT.STATUS & VBAT_XOSCFAIL_bm)
				vbat_status = VBAT_STATUS_XOSCFAIL;
			else
				vbat_status = VBAT_STATUS_OK;
		}
	}
	return vbat_status;
}

void vbat_backup_system()
{
	uint8_t vbat_status;
	vbat_status = vbat_system_check(true);
	/* 
	* Depending on the VBAT system check appropriate actions need to 
	* be taken.
	* In this version we re-initialize the VBAT and RTC32 system in all
	* error cases.
	*/
	switch (vbat_status)
	{
	case VBAT_STATUS_OK:
		break;
	case VBAT_STATUS_NO_POWER: // fall through
		{
			USART_0_write_block("\n\r No power error");
			RTC_0_init();
			break;
		}
	case VBAT_STATUS_BBPOR: // fall through
		{
			USART_0_write_block("\n\r BBPOR error");
			RTC_0_init();
			break;
		}
	case VBAT_STATUS_BBBOD: // fall through
		{
			USART_0_write_block("\n\r BBBOD error");
			RTC_0_init();
			break;
		}
	case VBAT_STATUS_XOSCFAIL: // fall through
		{
			USART_0_write_block("\n\r XOSCFAIL error");
			RTC_0_init();
			break;
		}
	default:
		{
			RTC_0_init();
			break;
		}
	}
}
