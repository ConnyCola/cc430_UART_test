#include "global.h"

//___GLOBAL VARIABLES___
volatile int vref_h;      	// Vref+ for ADC10 (calibrated sensor)
volatile int *ptr_vref_h; 	// Vref+ as raw
    
volatile int vref_l;       	// Vref- for ADC10 (calibrated sensor)
volatile int *ptr_vref_l;		// Vref- as raw

volatile int vref_vcc;        // VCC at Vref
volatile int *ptr_vref_vcc;	// Vcc as raw
