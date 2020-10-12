#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<stdint.h>

 void printHex(int num, int precision) {
	char tmp[16];
	char format[128];

	sprintf(format, "0%x", precision);

	sprintf(tmp, format, num);
	printf("X: %x\n", tmp);
	printf("S: %s\n", tmp);//correct 177
	printf("D: %d\n", (int) tmp);
	printf("U: %u\n", tmp);
}

int main(){
	printHex(375, 8);
getchar();
getchar();
return 0;
} 
