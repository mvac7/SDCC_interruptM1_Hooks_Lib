/* =============================================================================
  Test SDCC Z80 interrupt M1 Hooks MSX SDCC Library (fR3eL Project)
  Version: 1.2 (4/10/2021) 
  Author: mvac
  Architecture: MSX
  Format: ROM 8K
  Programming language: C
  WEB: 
  mail: mvac7303b@gmail.com
    
History of versions:
 - v1.2 ( 4/10/2021) 
 - v1.1 ( 4/07/2021)
 - v1.0 (10/08/2019) 
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxBIOS.h"
#include "../include/msxSystemVariables.h"

#include "../include/interruptM1_Hooks.h"
#include "../include/textmode.h"
#include "../include/keyboard.h"





// ---------------------------------------------------- Declaration of functions
char PEEK(uint address);
void WAIT(uint cicles);
boolean GetVFrequency();

void TestHooks();

void my_KEYI();

void my_TIMI1();
void my_TIMI2();


// ------------------------------------------------------------------- constants
const char AppAbout[] = "Test Interrupt M1 Hooks Lib\r\nv1.2 (4/10/2021)";
const char text03[] = "Press any key";

const char VFreqSTRINGS[2][5]={"60Hz","50Hz"};
const char msxSTRINGS[4][7]={"MSX   ","MSX2  ","MSX2+ ","TurboR"};


// ------------------------------------------------------------ global variables
uint contaKEYI;
uint contaTIMI;  

char MSXvers;
char VFreq;    
boolean is60Hz;  // 0=NTSC/60Hz, 1=PAL/50Hz



// ------------------------------------------------------------------- Functions


//
void main(void)
{
  MSXvers = PEEK(MSXVER);
  
  is60Hz = GetVFrequency();
  
  if(is60Hz) VFreq=50;
  else VFreq=60;  
  
  SCREEN1();
  WIDTH(32);
 
  
  LOCATE(0,0);
  PRINT(AppAbout);
  
  LOCATE(0,2);
  PRINT("MSX version: ");
  PRINT(msxSTRINGS[MSXvers]);
  
  LOCATE(0,3);
  PRINT("Video Freq.: ");
  PRINT(VFreqSTRINGS[is60Hz]);
  

  LOCATE(0,5);  
  PRINT(text03);
  INKEY();
  
  LOCATE(0,5);  
  PRINT("             ");  //clear 'press any key'

  
  TestHooks();
  

//Return to MSXDOS -------------------------------------------------------------
  LOCATE(0,23);  
  PRINT(text03);
  INKEY();
}



char PEEK(uint address) __naked
{
address;
__asm
  push IX
  ld   IX,#0
  add  IX,SP

  ld   L,4(IX)
  ld   H,5(IX)
  ld   L,(HL)
  
  pop  IX
  ret
__endasm;
}



// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
}



/* -----------------------------------------------------------------------------
   GetVFrequency
  
   Get Video Frequency (for BIOS in page 0)
   Input: ---
   Output: 0=NTSC/60Hz, 1=PAL/50Hz 
----------------------------------------------------------------------------- */  
boolean GetVFrequency() __naked
{
__asm
  push IX
  
  ld   A,(#MSXVER)   ;MSXVER=002D MSX version number (0=MSX,1=MSX2,2=MSX2+,3=TurboR)
  or   A
  jr   NZ,readHZfromVDP  //IF A!=0
  
;in the MSX1, the information about the video frequency is in a system variable
  ld   A,(#0x002B)  ;MSXROM1=002B
  bit  7,A          ;Default interrupt frequency (0=NTSC/60Hz, 1=PAL/50Hz)
  or   A
  jr   Z,_isNTSC
  jr   _isPAL   

;If it is run on an MSX2 or higher, we can check the video frequency in the VDP registers.
readHZfromVDP:
;look at the system variable that contains the VDP registry value
  ld   A,(#0xFFE8)    ;RG9SAV=FFE8 Mirror of VDP register 9
  bit  1,A           ;(0=NTSC/60Hz, 1=PAL/50Hz)  
  or   A  
  jr   Z,_isNTSC
  
_isPAL:
  ld   L,#1
  pop  IX
  ret
  
_isNTSC:  
  ld   L,#0
  pop  IX  
  ret  
__endasm;
}



void TestHooks()
{
  char line[]="-------------------------------";
  char cursorLine = 11;
  uint contaTest = 0;
  
  contaKEYI = 0;
  contaTIMI = 0;       

  LOCATE(0,5);  
  PRINT("Hook TIMI:    ");
  
  LOCATE(0,7);  
  PRINT("Hook KEYI:");
  
  LOCATE(0,9);  
  PRINT("Time (sec):");
  
  //LOCATE(0,12);  
  //PRINT("Press ESC for Exit");  

  //save the old hooks vectors
  //Save_ISR();
  Save_TIMI();   
  Save_KEYI(); 
  
  LOCATE(0,cursorLine++);
  PRINT("Log:");
  
  LOCATE(0,cursorLine++);
  PRINT(line);
  
  Install_TIMI(my_TIMI1);  
  LOCATE(0,cursorLine++);
  PRINT(">Install_TIMI(my_TIMI1)");
  
  while(1)
  {
    HALT;
    contaTest++;
    
    LOCATE(12,5);
    PrintFNumber(contaTIMI,32,5);    
    
    LOCATE(12,7);
    PrintFNumber(contaKEYI,32,5);
    
    LOCATE(12,9);
    PrintFNumber(contaTest/VFreq,32,5);
    
    if (contaTest==10*VFreq)
    { 
        Disable_TIMI();
        LOCATE(0,cursorLine++);
        PRINT(">Disable_TIMI()");
    }
    
    if (contaTest==20*VFreq)
    {
        Install_KEYI(my_KEYI);
        LOCATE(0,cursorLine++);
        PRINT(">Install_KEYI(my_KEYI) ");
    }
    
    if (contaTest==30*VFreq)
    {
        Install_TIMI(my_TIMI1);  
        LOCATE(0,cursorLine++);
        PRINT(">Install_TIMI(my_TIMI1)");
    }
    
    if (contaTest==40*VFreq)
    {
        Disable_KEYI();
        LOCATE(0,cursorLine++);
        PRINT(">Disable_KEYI()        ");
    }
    
    if (contaTest==50*VFreq)
    {
        break;  //exit test
    }
        
    //keyPressed = GetKeyMatrix(7);      
    //if (!(keyPressed&Bit2)) break;   //ESC Key
  }
  
  LOCATE(0,cursorLine++);
  PRINT(line);
  
  LOCATE(0,cursorLine++);
  PRINT("End TEST");
  //PRINT("TEST result: ");
  //if (contaKEYI==1002 && contaTIMI==1503) PRINT("OK");
  //else PRINT("ERROR");
  
  //It is not needed in ROM because it reboots the system at the end
  //Restore_ISR();
  Restore_TIMI();  
  Restore_KEYI();

}



void my_KEYI() 
{ 
  contaKEYI++;
}



void my_TIMI1()  // __interrupt 
{
  PUSH_AF;
  
  contaTIMI++;
  
  POP_AF;	
}


void my_TIMI2() __naked
{
__asm

  push AF

	ld	iy,#_contaTIMI
	inc	0 (iy)
	jr	NZ,TIMI_exit
	inc	1 (iy)

TIMI_exit:
  pop  AF
  
	ret
__endasm;		
}















