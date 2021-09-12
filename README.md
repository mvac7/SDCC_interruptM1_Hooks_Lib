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

<br/>


---

## Description

This library provides you with various functions to have total control over the hooks used in the ISR of the M1 interrupt included in the MSX system (BIOS/MSX-DOS).

This project is an Open Source library. You can add part or all of this code in your libraries/engines.

It allows working with both the interruptions produced by the VDP (TIMI), and those produced by other peripherals (KEYI).

This library can be used to program applications that run from MSX-BASIC and as ROMs. 
It can also be used in MSX-DOS but under certain conditions. To learn more, see the "How to use this" section.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

You can access the documentation here with [How to use the library](https://github.com/mvac7/SDCC_interruptM1_Hooks/blob/master/HOWTO.md).

In the source code (\examples), you can find applications for testing and learning purposes.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!

<br/>


## License

<br/>



## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

* Avelino Herrera > [(WEB)](http://msx.avelinoherrera.com/index_es.html)
* Nerlaska > [(Blog)](http://albertodehoyonebot.blogspot.com.es)
* Marq > [(Marq)](http://www.kameli.net/marq/)
* MSXKun/Paxanga soft > [(WEB)](http://paxangasoft.retroinvaders.com/)
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
* [WebMSX](https://webmsx.org/) emulator by Paulo A. Peccin >> [(gitHub)](https://github.com/ppeccin/webmsx)
* fMSX emulator by Marat Fayzullin [WEB](https://fms.komkon.org/fMSX/)
* Meisei emulator >> ?


---

## References

### English

* Z80 Family - [CPU User Manual](https://zany80.github.io/documentation/Z80/UserManual.html) (by ZiLOG) [(PDF)](http://map.grauw.nl/resources/cpu/z80.pdf)
* MSX2 Technical Handbook - [Chapter 2](https://github.com/Konamiman/MSX2-Technical-Handbook/blob/master/md/Chapter2.md#45-interrupt-usage) - 4.5 Interrupt usage
* The MSX Red Book - [4. ROM BIOS - KEYINT](https://github.com/gseidler/The-MSX-Red-Book/blob/master/the_msx_red_book.md#chapter_4)
* [Z80 Family Interrupt Structure](http://www.z80.info/1653.htm) (by Michael Moore)
* MSX Computer Magazine - Nº 51 Januari 1992 - [Interrupts](http://map.grauw.nl/articles/interrupts.php) - Page 6. (In English on MSX Assembly Page) 
* MSX Resource Center - Wiki - [System hooks](https://www.msx.org/wiki/System_hooks)



### Spanish

* Karoshi MSX Community - [Interrupciones del MSX](http://karoshi.auic.es/index.php?topic=947.0) (por SapphiRe)
* MSX Inside 005 - [Interrupciones](https://www.youtube.com/watch?v=dJymuMfgw9I) (por SapphiRe)
* MSX Inside 006 - [Interrupciones VBLANK](https://www.youtube.com/watch?v=aUkHk_mjtOU) (por SapphiRe)
* MSX Inside 007 - [Interrupciones de Línea](https://www.youtube.com/watch?v=E8nTwqaxEAg) (por SapphiRe)

