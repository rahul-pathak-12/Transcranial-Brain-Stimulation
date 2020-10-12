#include<stdio.h>
#include<math.h>
#include<stdint.h>
    
    void PrintHex8(uint8_t data, uint8_t length) // prints 8-bit data in hex with leading zeroes
    {
	char tmp[16];
	  for (int i=0; i<length; i++) {
	    sprintf(tmp, "0x%.2X",data);
	  }
	  printf("DATA: %x", data);
    }
    
    unsigned createMask(unsigned a, unsigned b){
    unsigned r = 0;
    for (unsigned i=a; i<=b; i++)
       r |= 1 << i;

    return r;
    }

    int main(){
   // int a = 32767;
    uint8_t a; 
    a= 32520;
    
   // PrintHex8(a,16);
    //  unsigned   r = createMask(0,8);
      //  unsigned result = r & 32767;
    printf("%02X", a);
    getchar();
    getchar();
    return 0;
    }


    /*int XNUM =0x5f70;
        printf("HEX: %x\n", XNUM);
    unsigned char BinConvert = XNUM>>8;
     unsigned char BinConvert1 = XNUM<<0;
     
     unsigned char x = BinConvert + BinConvert1;
       printf("FIRST: %x\n", BinConvert);
       printf("SECOND: %x\n\n", BinConvert1);
       
    int XNUM_X =0x6A6B;
        printf("HEX: %x\n", XNUM_X);
    unsigned char BinConvert_X = XNUM_X>>8;
     unsigned char BinConvert1_X = (XNUM>>8) & 0xff;
     
       printf("FIRST: %x\n", BinConvert_X);
       printf("SECOND: %x\n", BinConvert1_X);
       
       
       //byte BIT_MASK = (byte)0xff;   // low 8 bits
     //  byte byteValue = (byte)(intValue & BIT_MASK);

      // XNUM = XNUM << 8;
        //printf("%x", XNUM);*/
