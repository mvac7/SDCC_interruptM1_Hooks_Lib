/* =============================================================================
  Test SDCC Z80 interrupt M1 Hooks MSX SDCC Library (fR3eL Project)
  Version: 1.1 (4/7/2021) 
  Author: mvac
  Architecture: MSX
  Format: ROM 8K
  Programming language: C
  WEB: 
  mail: mvac7303b@gmail.com
    
History of versions:
 - v1.1 (04/07/2021)
 - v1.0 (10/08/2019) 
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxBIOS.h"
#include "../include/msxSystemVariables.h"

#include "../include/interruptM1_Hooks.h"
#include "../include/textmode.h"
#include "../include/keyboard.h"





//  definition of functions  ---------------------------------------------------
void WAIT(uint cicles);

void my_KEYI();

void my_TIMI1();
void my_TIMI2();


// ------------------------------------------------------------------- constants

const char AppAbout[] = "Test Interrupt M1 Hooks Lib\r\nv1.1 (4/7/2021)";

const char text03[] = "Press any key";


// ------------------------------------------------------------ global variables
uint contaKEYI;
uint contaTIMI;  


// Functions -------------------------------------------------------------------


//
void main(void)
{
  uint contaTest = 0;
  char cursorLine = 12;
  
  contaKEYI = 0;
  contaTIMI = 0;
  
  SCREEN1();
  WIDTH(32);
  
  
  LOCATE(0,0);
  PRINT(AppAbout);

  LOCATE(0,3);  
  PRINT(text03);
  INKEY();
  
  LOCATE(0,3);  
  PRINT("             ");  //clear 'press any key'

  LOCATE(0,5);  
  PRINT("Hook VBLANK:");
  
  LOCATE(0,7);  
  PRINT("Hook KEYI:");
  
  LOCATE(0,9);  
  PRINT("Time:             sec.(50Hz)");
  
  //LOCATE(0,12);  
  //PRINT("Press ESC for Exit");  


  Save_TIMI();   // save the old hook vector 
  
  Install_TIMI(my_TIMI1);  
  LOCATE(0,cursorLine++);
  PRINT("Install_TIMI(my_TIMI1)");
  
  while(1)
  {
    HALT;
    contaTest++;
    
    LOCATE(12,5);
    PrintFNumber(contaTIMI,32,5);    
    
    LOCATE(12,7);
    PrintFNumber(contaKEYI,32,5);
    
    LOCATE(12,9);
    PrintFNumber(contaTest/50,32,5);
    
    if (contaTest==10*50)
    { 
        Disable_TIMI();
        LOCATE(0,cursorLine++);
        PRINT("Disable_TIMI()        ");
    }
    
    if (contaTest==20*50)
    {
        Install_KEYI(my_KEYI);
        LOCATE(0,cursorLine++);
        PRINT("Install_KEYI(my_KEYI) ");
    }
    
    if (contaTest==30*50)
    {
        Install_TIMI(my_TIMI1);  
        LOCATE(0,cursorLine++);
        PRINT("Install_TIMI(my_TIMI1)");
    }
    
    if (contaTest==40*50)
    {
        Disable_KEYI();
        LOCATE(0,cursorLine);
        PRINT("Disable_KEYI()        ");
    }
    
    if (contaTest==50*50)
    {
        break;  //exit test
    }
        
    //keyPressed = GetKeyMatrix(7);      
    //if (!(keyPressed&Bit2)) break;   //ESC Key
  }


  Restore_TIMI();
  
//Return to MSXDOS -------------------------------------------------------------
  LOCATE(0,18);
  PRINT("-------------------------------\r\n");
  PRINT("End TEST");
  //PRINT("TEST result: ");
  //if (contaKEYI==1002 && contaTIMI==1503) PRINT("OK");
  //else PRINT("ERROR");
  
  LOCATE(0,21);  
  PRINT(text03);
  INKEY();
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





// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
}













