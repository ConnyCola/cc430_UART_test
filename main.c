#include "mrfi.h"
#include "serial/serial.h"

#include "defines.h"
#include "init.h"
#include "global.h"
#include "flash.h"
#include "spi.h"
#include "adc.h"
#include "data_proc.h"
#include "pulse.h"
#include "user_interf.h"
#include "measure.h"
#include "serial/serial.h"



#define VERSION_test 1001
#define BUILD   3


mrfiPacket_t packet;

volatile int temperature;			// temperature for compensation
volatile int *ptr_temperature;

volatile int temp_raw;				// temperature for compensation
volatile int *ptr_temp_raw;

volatile int moisture;          	// relative moisture
volatile int *ptr_mois_perc;		// mois in %

volatile char spi_data;				// converted data for SPI message
volatile char *ptr_spi_data;		// 0 - 255

unsigned int meas_mois_raw;
unsigned int *ptr_mois_raw;			// raw mois 0 - 1024


//chat
void main (void){
	WDTCTL = WDTPW+WDTHOLD;		// Stop watchdog timer
	P1OUT  = BIT0;				// P1.0 input+pullup
    P1REN |= BIT0;				// P1.0 input+pullup
    P1IE  |= BIT0;				// P1.0 interrupt enable
    P1IES |= BIT0;				// P1.0 Hi/Lo edge
    P1IFG &= ~BIT0;
    // P1.0 IFG Flag cleared

    ptr_temp_raw = &temp_raw;		// pointer allocations
    ptr_temperature = &temperature;

    ptr_mois_raw = &meas_mois_raw;
    ptr_mois_perc = &moisture;
    ptr_spi_data = &spi_data;

    ptr_vref_h = &vref_h;
    ptr_vref_l = &vref_l;
    ptr_vref_vcc = &vref_vcc;

    load_cal();

	initSerial();				// init Serial interface
	//printf("\r\n\r\n!!!      app start      !!!\r\n\r\n");

	__bis_SR_register(LPM0_bits + GIE);    // Enter LPM0, interrupts enabled
}

void MRFI_RxCompleteISR_new()	// in Components/mrfi/radios/family5/mrfi_radio.c
{
}

#define _UART

#ifndef _UART
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{	static int8_t inCnt = 0;
	if(__even_in_range(UCA0IV,4) == 2){
		if(UCA0RXBUF != 0x0D){

			while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
			char rx = UCA0RXBUF;
			printf("%c",rx);
			packet.frame[9+inCnt++]= rx;
		}
	}
}

#endif

#ifdef _UART
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR2(void)
{
	//TEST structure
	*ptr_mois_perc = *ptr_mois_perc < 100 ? *ptr_mois_perc+1 : 0;

	static int cmdMode = 0;
	CMD cmd;
	while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
	char in_key = UCA0RXBUF;                  // TX -> RXed character

	cmd.cmd = in_key;
	cmd.val1 = 0x00;
	cmd.val2 = 0x00;

	switch (cmd.cmd) {
	case CMD_MOIS:
		cmd.val1 = *ptr_mois_perc;
		break;
	case CMD_VOLT:
		cmd.val1 = (*ptr_mois_perc*25);
		break;
	case CMD_MIN:
		cmd.val1 = *ptr_vref_l;
		break;
	case CMD_MAX:
		cmd.val1 = *ptr_vref_h;
		break;
	case CMD_CALI:
		cmd.val1 = 1;
		break;
	case CMD_DRY:
		*ptr_vref_l = 330; //*ptr_mois_raw;
		cmd.val1 = *ptr_vref_l;
		break;
	case CMD_WET:
		*ptr_vref_h = 970; //*ptr_mois_raw;
		cmd.val1 = *ptr_vref_h;
		break;
	case CMD_FIN:
		cmd.val1 = 1;
        erase_flash(FLASH_VREF_L);
        write_flash_Vref(*ptr_vref_l, *ptr_vref_h, *ptr_vref_vcc); 	// write config values to info flash
		break;
	case CMD_TEST:
		*ptr_vref_l = 450;
		*ptr_vref_h = 1033;
		break;
	case CMD_VERS:
		cmd.val1 = VERSION_test;
		cmd.val2 = BUILD;
		break;
	default:
		cmd.cmd = CMD_ERROR;
		break;
	}

	send_CMD(cmd);

}
#endif

