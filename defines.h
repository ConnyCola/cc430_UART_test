#ifndef _CONFIG_H_
#define _CONFIG_H_
//
#include <msp430.h>
//

//___PORT DEFINITIONS___                                            /* S_PORTDEF */

#define VERSION 0x0101
#define BUILD   0x0002


// calibration switch
#define CAL_SW BIT5
// SPI chip-select ports
#define CS1 BIT7
#define CS2 BIT7
#define CS3 BIT6
// user interface LEDs
#define LED_YE BIT4
#define LED_GR BIT3
// test signal on port 2.2 / pin10
#define TEST_TRIGGER BIT2
                                                                    /* E_PORTDEF */
//___DEVICE SETTINGS___                                              /* S_DEVSET */

// TEMPERATURE RANGE
#define TEMP_MIN -10            // min. measured temperature
#define TEMP_MAX 50             // max. measured temperature

// TEMPERATURE OUTPUT SETTINGS
#define V_REF 4.096             // DAC reference voltage
#define V_MAX 2.5               // max DAC output voltage

// PULSE SETTINGS
#define PULSE_PERIOD 21  //21       // length of pulse period
#define PULSE_WIDTH  10         // width of pulse

// DAC DEVICE IDs
#define DAC_VREF_H 0x00         // DAC ID for Vref+
#define DAC_VREF_L 0x01         // DAC ID for Vref-
#define DAC_OUT_MOIS 0x02       // DAC ID for moisture output
#define DAC_OUT_TEMP 0x03       // DAC ID for temperature output

// FLASH DESTINATION
#define FLASH_VREF_L 0x1880     // address of Vref- data
#define FLASH_VREF_H 0x1885     // address of Vref+ data
#define FLASH_VCC    0x1888     // address of absolute Vcc



// ADC DEVICE IDs
#define ADC_TEMP 0x0           // temperature measurement settings
#define ADC_MOIS 0x1           // moisture measurement settings
#define ADC_VCC  0x2           // supply voltage measurement settings
                                                                     /* E_DEVSET */

#define Baudrate 0x80          //0x680 for 9600; 0x80 for 115200
#define TxD BIT0
//temperature
// #define CAL_ADC_15T30 *(unsigned int *) (0x10E2)
// #define CAL_ADC_15T85 *(unsigned int *) (0x10E4)

//#define _UART

// UART commands
#define CMD_MOIS 'A'
#define CMD_VOLT 'B'
#define CMD_MIN  'C'
#define CMD_MAX  'D'
#define CMD_CALI 'E'
#define CMD_DRY  'F'
#define CMD_WET  'G'
#define CMD_FIN  'H'
#define CMD_TEST 'I'
#define CMD_VERS 'J'
#define CMD_ERROR 'Z'


//


#endif

