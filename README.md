# Interrupt M1 Hooks MSX SDCC Library (fR3eL Project)

```
Author: mvac7 
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```



## History of versions:
- v1.1 (4 July 2021) More functions to control the two Hooks (added KEYI).
- v1.0 (4 July 2011) Published in [Avelino Herrera's WEB](http://msx.avelinoherrera.com/index_es.html#sdccmsx)



  


## Sorry!: This text is pending correction of the English translation. <<<<<<<<




## Introduction

This library provides you with various functions to have total control over the hooks used in the ISR of the M1 interrupt included in the MSX system (BIOS/MSX-DOS).

This project is an Open Source library. You can add part or all of this code in your libraries/engines.

It allows working with both the interruptions produced by the VDP (TIMI), and those produced by other peripherals (KEYI).

It is a very light library, but if you need to gain a few Bytes and you are only going to use the VDP interrupts, you can use the reduced version interruptM1_TIMI

**ATTENTION!** Although they can be used for MSX-DOS applications, you must be aware of an existing problem. 
Because the ISR when it executes the hook has the BIOS visible, you will have to control that your functions for the interruption are located above page 0. 
If your application is small, you should copy your function in the highest area of the RAM, although you can also substitute the ISR of the system for yours but it will require a different library than this one.

Remember that an interrupt routine for a hook is not an ISR. You have more information in the How to Use it section.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

In the source code (\examples), you can find applications for testing and learning purposes.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!



## License





## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

* Avelino Herrera > [(WEB)](http://msx.avelinoherrera.com/index_es.html)
* Nerlaska > [(Blog)](http://albertodehoyonebot.blogspot.com.es)
* Marq > [(Marq)](http://www.kameli.net/marq/)
* Fubukimaru [(gitHub)](https://github.com/Fubukimaru)
* Andrear > [(Blog)](http://andrear.altervista.org/home/msxsoftware.php)
* Sapphire/Z80ST > [(WEB)](http://z80st.auic.es/)
* Fernando García > [(Curso)](http://www.z80st.es/cursos/bitvision-assembler)
* Ramones > [(MSXblog)](https://www.msxblog.es/tutoriales-de-programacion-en-ensamblador-ramones/) - [(MSXbanzai)](http://msxbanzai.tni.nl/dev/faq.html)
* Eric Boez > [(gitHub)](https://github.com/ericb59)
* MSX Assembly Page > [(WEB)](http://map.grauw.nl/resources/msxbios.php)
* Portar MSX Tech Doc > [(WEB)](https://problemkaputt.de/portar.htm)
* MSX Resource Center > [(WEB)](http://www.msx.org/)
* Karoshi MSX Community > [(WEB)](http://karoshi.auic.es/)
* BlueMSX emulator >> [(WEB)](http://www.bluemsx.com/)
* OpenMSX emulator >> [(WEB)](http://openmsx.sourceforge.net/)
* Meisei emulator >> ?



## Requirements

* Small Device C Compiler (SDCC) v4.1 > http://sdcc.sourceforge.net/
* Hex2bin v2.5 > http://hex2bin.sourceforge.net/



## Definitions

* **DI** Disable interrupts (Z80 Assembler DI)
* **EI** Enable interrupts (Z80 Assembler EI)

* **PUSH_AF** Saves the AF value on the stack. Required for starting TIMI (VBLANK) type functions (Z80 Assembler PUSH AF)
* **POP_AF**  Retrieves the value of AF from the stack. Required for the end of TIMI (VBLANK) type functions (Z80 Assembler POP AF)

* **HALT** Suspends all actions until the next interrupt (Z80 Assembler HALT)



## Functions

* void **Save_TIMI**() Save TIME hook vector.
* void **Install_TIMI**(void (*isr)(void)) Set new TIMI hook vector.
* void **Restore_TIMI**() Restore old TIMI hook vector
* void **Disable_TIMI**() Disable the TIMI hook (Add a ret on the hook).

* void **Save_KEYI**() Save KEYI hook vector.
* void **Install_KEYI**(void (*isr)(void)) Set new KEYI hook vector.
* void **Restore_KEYI**() Restore old KEYI hook vector
* void **Disable_KEYI**() Disable the KEYI hook (Add a ret on the hook).
 


## How to use

This library contains several functions to have full control of the hooks of the M1 interrupt. 
Allows you to save the system hook, replace it, disable it, and retrieve it. 
The way you work is up to you.

Remember that in the hook you do not have to connect an ISR type function. 
The hook is called by the system's ISR, so you will have interrupts disabled and all records saved (including alternates)..

Nor do you have to worry about reading the state of register 0 of the VDP since the ISR does, 
but it is recommended that at the beginning and end of your function, you save and retrieve the pair of AF registers. 
For this I have included two definitions for when it is programmed in C: PUSH_AF and POP_AF.

When you leave your function you do not have to do anything either. 
The system ISR is responsible for retrieving the values from the registers and triggering the interrupts.

Here is an example:

```
/* -----------------------------------------------------------------------------
   Any example...
----------------------------------------------------------------------------- */

void TestM1();

void my_TIMI1();
void my_TIMI2();




void main()
{
    Save_TIMI();   // save the old hook vector 

    Install_TIMI(my_TIMI1);  // Install the first function for the interrupt
    
    TestM1();
    
    Disable_TIMI(); // disable hook vector
    
    TestM1();
    
    Install_TIMI(my_TIMI2);   // Install the second function for the interrupt 
    
    TestM1();        

    Restore_TIMI(); // restore the old hook vector
}



void TestM1()
{
    char n=255;
    
    while(n>0)
    {
        HALT;
        n--;
    }
}



// C
void my_TIMI1()
{
  PUSH_AF;
    
// your C code goes here
  
    
  POP_AF;
}



// assembler
void my_TIMI2() __naked
{
__asm
  push AF
      
; your Assembler code goes here

    
  pop AF
  ret  
__endasm;
}


```