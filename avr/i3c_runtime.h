/*
 * I³C Runtime Environment
 *
 * Common configuration header used by the boot loader and applications.
 */



/*
 * Note:
 * 	Align Flash memory addresses to the Flash pages (64 bytes)!
 *
 * 	Mind to adapt the make file if you change any of these values!
 */

/*
 * This address must be chosen so that the loader completely
 * fits into the Flash memory. This value also denotes the maximal
 * size of a loaded firmware blob.
 */
#define BOOTLOADER_SIZE             0x0600

/*
 * The last address of the boot loader Flash memory space.
 *
 * This address represents the last Flash memory address
 * and is device dependent.
 *
 * TODO Select the address based on the device.
 */
#define BOOTLOADER_ENDADDRESS       0x0800

/*
 * Effective start address for the boot loader.
 *
 * This value also denotes the maximal size of a loaded firmware blob.
 */
#define BOOTLOADER_STARTADDRESS     (BOOTLOADER_ENDADDRESS - BOOTLOADER_SIZE)

/*
 * Address of the library function block.
 *
 * The block is stored at the end of the boot loader Flash memory space.
 */
#define BOOTLOADER_FUNC_ADDRESS     (BOOTLOADER_ENDADDRESS - sizeof(BOOTLOADER_FUNCTIONS))


/*
 * "Library functions" exported by the boot loader go here.
 *
 * app_main	Must be set to NULL in the bootloader code and will be
 * 		overwritten with the application entry point.
 */
typedef struct {
  void (*app_main) (void);
} BOOTLOADER_FUNCTIONS;

// End of File
