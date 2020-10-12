#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<stdint.h>

    void printHex(int num, int precision) {
	   char tmp[16];
	   char format[128];
    
	   sprintf(format, "0x%%.%dX", precision);

	   sprintf(tmp, format, num);
	   printf("DATA: %x", tmp);
    }
    
    void PrintHex8(uint8_t *data) // prints 8-bit data in hex with leading zeroes
    {
        uint8_t x;
	  //Serial.print("0x");
	  for (int i=0; i<8; i++) {
	    if (data[i]<0x10) {Serial.print("0");}
	    Serial.print(data[i],HEX);
	    Serial.print(" ");
	  }
    }

    void PrintHex16(uint16_t *data, uint8_t length) // prints 16-bit data in hex with leading zeroes
    {
	  Serial.print("0x");
	  for (int i=0; i<length; i++)
	  {
	    uint8_t MSB=byte(data[i]>>8);
	    uint8_t LSB=byte(data[i]);

	    if (MSB<0x10) {Serial.print("0");} Serial.print(MSB,HEX); Serial.print(" ");
	    if (LSB<0x10) {Serial.print("0");} Serial.print(LSB,HEX); Serial.print(" ");
	  }
    }
  /*  void PrintHex8(uint8_t data, uint8_t length) // prints 8-bit data in hex with leading zeroes
    {
	  Serial.print("0x");
	  for (int i=0; i<length; i++) {
	    if (data[i]<0x10) {Serial.print("0");}
	    printf("",data[i],HEX);
	  }
    }*/

    int main(){
        uint8_t = 32520;
	   //printHex(32520, 5);
	   //PrintHex8(32520, 8)
	long UPC2[] = 12;
	printf("%016llu\n",strtoll(UPC2,NULL,10));
	 
	getchar();
	getchar();
	return 0;
    }
