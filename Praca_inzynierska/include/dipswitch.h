#ifndef DIPSWITCH_INCLUDED
#define DIPSWITCH_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
	#endif
	#include <port.h>
	
	#define ADDRESS_BITS 5
	#define MODE_BIT 6
	
	void dipswitch_init();
	uint8_t get_address();		//get value from 0-4 pins
	uint8_t get_mode();			//get value from 5 pin

	#ifdef __cplusplus
}
#endif
#endif /* DIPSWITCH_INCLUDED */
