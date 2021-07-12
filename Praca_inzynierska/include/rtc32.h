/**
 * \file
 *
 * \brief RTC32 related functionality declaration.
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

#ifndef RTC32_H_INCLUDED
#define RTC32_H_INCLUDED

#include <compiler.h>
#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif
//! \name Battery backup system status macros
//@{
/**
 * \brief Everything works as expected.
 *
 * The backup system is configured and had no issues while main power was
 * lost. Because of that all data stored in the backup domain is valid.
 */
#define VBAT_STATUS_OK          0

/**
 *  \brief No power detected on VBAT.
 *
 * The backup system is not operational and all data within the backup system
 * will be lost when main power is lost.
 */
#define VBAT_STATUS_NO_POWER    1

/**
 *  \brief The backup system must be initialized.
 *
 * A POR was detected on VBAT input which indicates that a supply was connected
 * to the backup system. Since this is also the first start-up of the device we
 * then need to initialize the backup system.
 */
#define VBAT_STATUS_INIT        2

/**
 *  \brief A POR was detected on the VBAT input.
 *
 * This means the backup system is in an unkonw state.
 */
#define VBAT_STATUS_BBPOR       3

/**
 * \brief A brown-out was detected on the VBAT input.
 *
 * The backup system is in a unkown state and must be reset.
 */
#define VBAT_STATUS_BBBOD       4
/**
 * \brief A failure was detected on the oscillator.
 *
 * The oscillator stopped for at least TBD period of time and because of that
 * we can not rely on the RTC time any more.
 */
#define VBAT_STATUS_XOSCFAIL    5
//@}

/**
* \brief Check battery backup system status.
*
* \param first_time_startup When this is the first time the system starts then
* this is false otherwise true.
* \returns Backup system status.
*/
void vbat_init();

int8_t RTC_0_init();

extern uint8_t vbat_system_check(bool first_time_init);

void vbat_backup_system();

#ifdef __cplusplus
}
#endif

#endif /* RTC32_H_INCLUDED */
