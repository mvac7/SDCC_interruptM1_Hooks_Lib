/* =============================================================================
  SDCC Z80 interrupt M1 Hooks MSX SDCC Library (fR3eL Project)
  Version: 1.1 (4 July 2021)
  Author: mvac7
  Architecture: MSX
  Format: C Object (SDCC .rel)
  Programming language: C and Z80 assembler

  Description:
    Functions to control over the hooks (TIMI and KEYI) used in the ISR of the 
    M1 interrupt included in the MSX system (BIOS/MSX-DOS).    
  
  History of versions:
   - v1.1 (4 July 2021)
   - v1.0 (4 July 2011) Published in Avelino Herrera's WEB 
                        http://msx.avelinoherrera.com/index_es.html#sdccmsx
============================================================================= */

#include "../include/interruptM1_Hooks.h"


#define HINT     0x0038 //Z80 INT (RST $38)  · IM 1 interrupts entry poin

#define HKEYI	 0xFD9A //Hook KEYI. Interrupt handler device other than the VDP. (RS-232C, MSX-Midi, etc) 
#define HTIMI	 0xFD9F //Hook TIMI. Interrupt handler VDP VBLANK


char OLD_TIMI[5];
char OLD_HKEYI[5];



/* =============================================================================
 Save_TIMI

 Function : Save TIME hook vector
 Input    : -
 Output   : -
============================================================================= */
void Save_TIMI() __naked
{
__asm
	di
  
	ld	 HL,#HTIMI
	ld	 DE,#_OLD_TIMI
	ld	 BC,#5
	ldir
  
	ei
	ret
__endasm;
}



/* =============================================================================
 Install_TIMI

 Function : Set new TIMI hook vector  
 Input    : Function address
 Output   : -
============================================================================= */
void Install_TIMI(void (*func)(void)) __naked
{
func;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ; Set new TIMI vector
  di
  ld   A,#0xC3       ;add a JP
  ld   (#HTIMI),A
  ld   L,4(IX)
  ld   H,5(IX)
  ld   (#HTIMI+1),HL
  ei
  
  pop IX
  ret
__endasm;
}



/* =============================================================================
 Restore_TIMI

 Function : Restore old TIMI hook vector 
 Input    : -
 Output   : -
============================================================================= */
void Restore_TIMI() __naked
{
__asm
	di
  
    ld	 HL,#_OLD_TIMI
	ld	 DE,#HTIMI
	ld	 BC,#5
	ldir
  
	ei
	ret
__endasm;
}




/* =============================================================================
 Disable_TIMI

 Function : Disable the TIMI hook (Add a ret on the hook).
 Input    : -
 Output   : -
============================================================================= */
void Disable_TIMI() __naked
{
__asm
    di
	ld  A,#0xC9     ; ret
    ld  (#HTIMI),A
    ei    
    ret
__endasm;
}



/* =============================================================================
 Save_KEYI

 Function : Save KEYI hook vector
 Input    : -
 Output   : -
============================================================================= */
void Save_KEYI() __naked
{
__asm
	di
  
	ld	 HL,#HKEYI
	ld	 DE,#_OLD_HKEYI
	ld	 BC,#5
	ldir
  
	ei
	ret
__endasm;
}



/* =============================================================================
 Install_KEYI

 Function : Set new KEYI hook vector  
 Input    : Function address
 Output   : -
============================================================================= */
void Install_KEYI(void (*func)(void)) __naked
{
func;
__asm
	push IX
	ld   IX,#0
	add  IX,SP
  
	di
	ld   A,#0xC3       ;add a JP
	ld   (#HKEYI),A
	ld   L,4(IX)
	ld   H,5(IX)
	ld   (#HKEYI+1),HL
	ei
	
	pop IX
	ret
__endasm;
}



/* =============================================================================
 Restore_KEYI

 Function : Restore old KEYI hook vector 
 Input    : -
 Output   : -
============================================================================= */
void Restore_KEYI() __naked
{
__asm
	di
  
    ld	 HL,#_OLD_HKEYI
	ld	 DE,#HKEYI
	ld	 BC,#5
	ldir
  
	ei
	ret
__endasm;
}




/* =============================================================================
 Disable_KEYI

 Function : Disable the KEYI hook (Add a ret on the hook).
 Input    : -
 Output   : -
============================================================================= */
void Disable_KEYI() __naked
{
__asm
    di
	ld  A,#0xC9     ; ret
    ld  (#HKEYI),A
    ei    
    ret
__endasm;
}