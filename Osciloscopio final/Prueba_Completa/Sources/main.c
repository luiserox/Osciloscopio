/* ###################################################################
**     Filename    : main.c
**     Project     : Prueba_potenciometro
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-02-11, 13:57, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "TI1.h"
#include "AS1.h"
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

char flag = 0;

void main(void)
{
  /* Write your local variable definition here */
	char cd1, cd2, frag1, frag2;
 	 char size=4;
 	 unsigned int send=4;
	 char	analog[4];
	 char 	error = 0;
	 char datos[4];
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  
  /* Write your code here */
  	 //do {error = AD1_Start();} while(error != ERR_OK);

  	  while(1){
  		  if(flag){
  			  flag = 0;
  			do {error = AD1_Measure(1);} while(error != ERR_OK);
  			  do {error = AD1_GetValue(analog);} while(error != ERR_OK);
  			  if(Bit1_GetVal()>0)
  				  cd1 = 0b01000000;
  			  else cd1 = 0;
  			  if(Bit2_GetVal()>0)
  				  cd2 = 0b01000000;
  			  else cd2 = 0;			
  			  frag1 = analog[1] & 0b11000000;
  			  frag2 = analog[3] & 0b11000000;
  			  datos[0] = (analog[0]<<2) | (frag1>>6);
  			  datos[1] = 0b10000000 | (cd1) | (analog[1] & 0b00111111);
  			  datos[2] = 0b10000000 | (cd2) | (analog[2]<<2) | (frag2>>6);
  			  datos[3] = 0b11000000 | (analog[3] & 0b00111111);
  			  
  			  do {error = AS1_SendBlock(datos,size,&send);} while(error != ERR_OK);
  			  Bit3_NegVal();
  		  }
  	  }
  
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
