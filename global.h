#ifndef GLOBAL_H
#define GLOBAL_H

extern volatile int vref_h;       // Vref+ for ADC10 (calibrated sensor)
extern volatile int *ptr_vref_h;

extern volatile int vref_l;       // Vref- for ADC10 (calibrated sensor)
extern volatile int *ptr_vref_l;

extern volatile int vref_vcc;     // VCC at Vref
extern volatile int *ptr_vref_vcc;

typedef struct {
	char cmd;
	int val1;
	int val2;
} CMD;

#endif
