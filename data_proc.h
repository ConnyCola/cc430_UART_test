#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

unsigned char conv_temp(unsigned int adc_value);
float conv_vcc(unsigned int adc_value);
unsigned char conv_mois(unsigned int adc_value);
unsigned char conv_dac(float voltage);
unsigned char conv_mois_dac(int raw);
int calc_mois_perc(long raw);
#endif
