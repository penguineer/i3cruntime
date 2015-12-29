/*
 * I³C Runtime Environment
 *
 * Autor: Stefan Haun <tux@netz39.de>
 * 
 * inspired by http://www.mikrocontroller.net/articles/Konzept_f%C3%BCr_einen_ATtiny-Bootloader_in_C
 * 
 * uses https://github.com/eriksl/usitwislave.git
 * 
 * DO NOT forget to set the fuses s.th. the controller uses the 8 MHz clock!
 */


/* define CPU frequency in MHz here if not defined in Makefile */
#ifndef F_CPU
  #define F_CPU 8000000UL
#endif

#include <inttypes.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/boot.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdint.h>
#include <string.h>

#include <usitwislave.h>

#include "i3c_runtime.h"

/*
 * Write a RJMP to boot loader at the program start address (0x0000)
 */
#define RJMP		(0xC000U - 1)	// opcode of RJMP minus offset 1
#define RESET_SECTION	__attribute__((section(".bootreset")))

uint16_t boot_reset RESET_SECTION = RJMP + BOOTLOADER_STARTADDRESS / 2;

/*
 * Pointers to exported functions go here
 */
static BOOTLOADER_FUNCTIONS bootloader_functions = {
    (void (*)) NULL, // app_main
};

/*
 * Macro to fill a flash page without interruptions.
 *
 * Environment:
 * 	This macro expects an uint8_t sreg to be present in the
 * 	call environment.
 */
#define boot_program_page_fill(bAddr, word) \
{ \
  sreg = SREG; \
  cli(); \
  boot_page_fill( (uint32_t)(bAddr), (word)); \
  SREG = sreg; \
}


/*
 * Macro to erase and write a flash page without interruptions.
 *
 * Environment:
 * 	This macro expects an uint8_t sreg to be present in the
 * 	call environment.
 *
 * Note:
 * 	The original macro contained a call to boot_rww_enable(), however
 * 	the there referenced register SPMCR with the bit RWWSRE is not
 * 	present in the ATTINY44, therefore we omit the call.
 *
 * 	TODO Check if there is an alternative action we have to pursue.
 *
 * 	If the call should be enabled, you need to
 * 	#define RWWSRE 4
 */
#define boot_program_erase_write(pageAddr) \
{ \
  eeprom_busy_wait(); \
  sreg = SREG; \
  cli(); \
  boot_page_erase((uint32_t)(pageAddr)); \
  boot_spm_busy_wait(); \
  boot_page_write((uint32_t)(pageAddr)); \
  boot_spm_busy_wait(); \
  /*   boot_rww_enable();  */ \
  SREG = sreg; \
}



/*
 * Write a block from an SRAM variable into the flash memory.
 *
 * Note:
 * 	This function only handles a single memory page.
 * 	Structures that cross flash page boundaries cannot be written!
 */
static void pgm_write_block (uint16_t flash_addr,
			     uint16_t *block,
			     size_t size)
{
    uint16_t start_addr;
    uint16_t addr;
    uint16_t w;
    uint8_t idx = 0;
    uint8_t sreg; // Used in the macros
 
    // round down (granularity is SPM_PAGESIZE)
    start_addr = (flash_addr / SPM_PAGESIZE) * SPM_PAGESIZE;
 
    for (idx = 0; idx < SPM_PAGESIZE / 2; idx++) {
        addr = start_addr + 2 * idx;
 
	// decide if the target data value should come
	// from the structure or from the memory,
	// i.e. if the memory value should be overwritten
        if (addr >= flash_addr && size > 0) {
            w = *block++;
            size -= sizeof (uint16_t);
        } else {
            w = pgm_read_word (addr);
        }
 
	// set the new memory value
        boot_program_page_fill(addr, w);
    }
 
    // erase and write the page
    boot_program_erase_write(start_addr);
}

void start_bootloader()
{
  // TODO do something useful here?

  return;
}

void bootloader_flash_init() {
  uint16_t rjmp;
  uint8_t idx;
  uint8_t sreg;
  
  // get rjmp address
  // and add the offset difference
  rjmp = pgm_read_word(BOOTLOADER_STARTADDRESS) + BOOTLOADER_STARTADDRESS / 2;
  
  // only copy if not already similar to reset address
  if (rjmp != pgm_read_word(0)) {
    
    // copy interrupt vectors to beginning of flash
    // and add the offset difference
    for (idx = 0; idx < _VECTORS_SIZE; idx += 2) {
	rjmp = pgm_read_word(BOOTLOADER_STARTADDRESS + idx) + BOOTLOADER_STARTADDRESS / 2;
	boot_program_page_fill(idx, rjmp);      
    }
    
    // fill the remaining bytes (to 64 bytes page size) with zero
    while (idx < SPM_PAGESIZE) {
      boot_program_page_fill(idx, 0);
      idx += 2;
    }

    // write to the first Flash page
    boot_page_write(0x0000);

    // copy the bootloader functions to the BOOTLOADER_FUNC_ADDRESS
    // so that – once installed – the "user space" program can find it
    pgm_write_block(BOOTLOADER_FUNC_ADDRESS, 
		    (uint16_t *) &bootloader_functions, 
		    sizeof (bootloader_functions));
  }  
}

int main(void)
{
  // Initialize the flash for the boot loader.
  // This is called exactly one when the boot loader
  // has been flashed onto the device.
  bootloader_flash_init();

  // Boot loader main loop
  for (;;) {
    // call the boot loader code
    start_bootloader();

    // boot loader returns here if there is nothing to do
    
    // Get the library functions from the Flash memory
    memcpy_P(&bootloader_functions,
	     (PGM_P) BOOTLOADER_FUNC_ADDRESS,
	     sizeof(bootloader_functions));

    // call applicaton if present
    if (bootloader_functions.app_main != NULL) {
	cli ();
	(*bootloader_functions.app_main)();
    }
  }
  
  return 0;
}