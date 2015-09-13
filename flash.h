#ifndef FLASH_H
#define FLASH_H

void erase_flash(int addr);
void write_flash_Vref(int val_vref_l, int val_vref_h, int val_vcc);
int read_flash_ref(int addr);

#endif
