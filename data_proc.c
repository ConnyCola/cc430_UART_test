#include "global.h"
#include "data_proc.h"
//---------------------------------------DATA CONVERSIONS--------------------------

//___TEMPERATURE VALUE CONVERSION___                                /* S_TEMPCON */
unsigned char conv_temp(unsigned int adc_value)
  {
    unsigned char temperature = (unsigned char)(adc_value * 1.70620438 - 1113.062693);
    return temperature;
  }
                                                                    /* E_TEMPCON */
//___SUPPLY VOLTAGE VALUE CONVERSION___
float conv_vcc(unsigned int adc_value)
  {
    float vcc = adc_value * 0.00366211;  //convert to absolute voltage
    return vcc;
  }

//___RETURN MOISTURE VALUE IN % value___
unsigned char conv_mois(unsigned int v)
  {
    unsigned char m = (char)(100 - (0.09765625 * (v)));
    return m;
  }

//___RAW TO DAC (0-255)___
unsigned char conv_mois_dac(int raw)
  {
	long back = 0;
	back = ((255*(long)(raw - *ptr_vref_l))/((long)(*ptr_vref_h - *ptr_vref_l)));
	return (unsigned char)back;
  }

//___Volts to DAC 255___
unsigned char conv_dac(float voltage)
  {
    unsigned char spi_dac = (char)(voltage * 62.5);
    return spi_dac;
  }

//___RAW to %___
int calc_mois_perc(long raw){
	float back = 0;
	back = ((100*(long)(raw - *ptr_vref_l))/((long)(*ptr_vref_h - *ptr_vref_l)));
	return back;
}
