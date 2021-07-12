#include <atmel_start.h>
#include <avr/sleep.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/* Check VBAT backup system flags */
	vbat_backup_system();
	
	/* Hello world */
	uint8_t tx_buf[] = "\n\rHello AVR world ! :";
	USART_0_write_block(tx_buf);
	if (get_mode()==0) USART_0_write_block("\n\rSlave\n\r");
	else USART_0_write_block("\n\rMaster\n\r");
	USART_0_write_number(get_address());
	/* Main loop */
	while (1) {
		USART_0_write_block("\n\rI go to sleep");
		sleep_cpu();
	}
}
