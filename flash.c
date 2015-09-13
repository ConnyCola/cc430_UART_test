#include "flash.h"
//#include <msp430G2452.h>
#include "defines.h"

//___ERASE FLASH___                                              /* S_ERASEFLASH */
void erase_flash(int addr)
  {
    int *ptr_float_addr;                   // init pointer
    int float_addr;
    ptr_float_addr = &float_addr;
    
    while(FCTL3 & BUSY){};                 // wait till timing gen is ready
    FCTL3 = FWKEY;                         // Clear Lock bit
    FCTL1 = FWKEY + ERASE;                 // prepare to erase
    ptr_float_addr = (int *)addr;          // set address
    *ptr_float_addr = 0;                   // erase flash segment
    while(!(FCTL3 & WAIT)){};              // wait while writing
  }
                                                                 /* E_ERASEFLASH */
//___WRITE TO FLASH___                                           /* S_WRITEFLASH */
void write_flash_Vref(int val_vref_l, int val_vref_h, int val_vcc)
  {
    int *ptr_flash_addr;                 // init pointer
    int flash_addr;
    ptr_flash_addr = &flash_addr;
    
    while(FCTL3 & BUSY){};                 // wait till timing gen is ready
    FCTL3 = FWKEY;                         // Clear Lock bit
	FCTL1 = FWKEY+ERASE;                      // Set Erase bit
	int * Flash_ptr = (int *) FLASH_VREF_L;
	*Flash_ptr = 0;                           // Dummy write to erase Flash seg
    FCTL1 = FWKEY + WRT;                   // prepare to write
    
    //addresses come from defines.h
    ptr_flash_addr = (int *)FLASH_VREF_L;// set address
    *ptr_flash_addr = val_vref_l;          // save Vref- to flash
    ptr_flash_addr = (int *)FLASH_VREF_H;// set address
    *ptr_flash_addr = val_vref_h;          // save Vref+ to flash
    ptr_flash_addr = (int *)FLASH_VCC;   // set address
    *ptr_flash_addr = val_vcc;             // save VCC to flash
    while(!(FCTL3 & WAIT)){};              // wait while writing
    FCTL1 = FWKEY;                         // Clear WRT bit
    FCTL3 = FWKEY + LOCKA + LOCK;          // Set LOCK & LOCKA bit
  }
                                                                 /* E_WRITEFLASH */
//___READ FROM FLASH___                                           /* S_READFLASH */
int read_flash_ref(int addr)
  {
    int *ptr_flash_addr;
    int flash_addr;
    int flash_data;
    ptr_flash_addr = &flash_addr;
    
    ptr_flash_addr = (int *)addr;        // redirect pointer to address
    flash_data = *ptr_flash_addr;
    return flash_data;                     // return loaded value
  }
                                                                  /* E_READFLASH */
