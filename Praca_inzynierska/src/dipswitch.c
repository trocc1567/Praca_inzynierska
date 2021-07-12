#include <dipswitch.h>

/**
 * \brief Initialize USART interface
 * If module is configured to disabled state, the clock to the USART is disabled
 * if this is supported by the device's clock system.
 *
 * \return Nothing
 */

void dipswitch_init()
{
	PORTA_set_port_dir(0xff, PORT_DIR_IN);
}

/*
Get the value of pins which represent adress of node
return Number od adress which is chosen on diswitch
*/

uint8_t get_address()
{
	uint8_t mask=1;
	uint8_t i;
	for (i=0; i<ADDRESS_BITS; i++)
	{
		mask*=2;
	}
	mask--;
	
	return (PORTA_get_port_level() & mask);
}

/*
 * \brief Get the value of pins which represent adress of node
 *
 * \return Initialization status.
 * \retval 0 Slave Mode
 * \retval 1 Master Mode
 */

uint8_t get_mode()
{
	return PORTA_get_pin_level(MODE_BIT-1);
}