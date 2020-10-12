#include <stdio.h>
#include <math.h>
//#include <mbed.h>

    float adjvoltage(float x);                          /* Prototype */
    int firstCommand (int channel);                     /* Prototype */
    unsigned char secondCommand(int adjVoltage);        /* Prototype */
    unsigned char thirdCommand(int adjVoltage);         /* Prototype */
    void DC_WRITE(int voltage, int channel);            /* Prototype */ 
    void AC_WRITE(int voltage, int channel, int freq);  /* Prototype */ 
    
/*
    SPI dac(p5, p6, p7);     
    DigitalOut cs(p8);       
    DigitalOut resetpin(p9); 
    DigitalOut clearpin(p10);   
*/

    float adjvoltage(float x){
        float voltage = (x + 10.0) * (65535.0/20.0); //force float
        return voltage;
    }
    

    int firstCommand (int channel) {
    int channelBits = 0;    
        switch (channel) { 
           case 202:channelBits= 11000000;       //202 = All channels 
                break;  
           case 200:channelBits= 11000001;       //200 = group 0
                break;
           case 201:channelBits= 11000010;       //201 = group 1
                break;
            case 0: channelBits= 11001000;       //0 = channel 0
                break;
            case 1: channelBits= 11001001;       //1 = channel 1
                break;
            case 2: channelBits= 11001010;       //2 = channel 2
                break;  
            case 3: channelBits= 11001011;       //3 = channel 3
                break;
            case 4: channelBits= 11010000;       //4 = channel 4
                break;
            case 5: channelBits= 11010001;       //5 = channel 5
                break;
            case 6: channelBits= 11010010;       //6 = channel 6
                break;
            case 7: channelBits= 11010011;       //7 = channel 7
                break;
            default:
                printf("ERROR"); 
        }
    return channelBits;
    }
    

    unsigned char secondCommand(int adjVoltage){
        return adjVoltage >> 8;
    }
    

    unsigned char thirdCommand(int adjVoltage){
        unsigned char rbyte = 0;
        unsigned char byte = adjVoltage; // Value to Be Reversed

        for (int i=0 ; i<8 ; i++)
            if (byte & (1<<i)) rbyte |= (1<<(7-i));
        return byte;
    }
    

    void DC_WRITE(int voltage, int channel){
        float voltage16 = adjvoltage(voltage);
        unsigned char first = firstCommand(channel);
        unsigned char second = secondCommand(voltage16);
        unsigned char third = thirdCommand(voltage16);
        
       // cs=0;
       // dac.write(first);
       // dac.write(second);
      //  dac.write(third);
      //  cs=1;
      //  wait_ms(0.005);
       printf("FIRST:  %x\n", first);
        printf("SECOND: %x\n",second);
        printf("THIRD:  %x\n",third);  
    }
    
   
    void AC_WRITE(int voltage, int channel, int freq){
        float PI = 3.14159;    
       // while(1){
        for(float i=0; i<=(PI/2); i=i+0.1){  //multily increment by 10etc to change freq and TIME in DC_WRITE   ,i<=0.01                                  
            float sinvoltage = sin(2*PI*freq*i)*10;
            
            printf("DC WRITE AC:");
            DC_WRITE(sinvoltage, channel);  //output voltage to DAC                  channel 5 and channel 0      
            printf("DC WRITE DC:");
            DC_WRITE(5, 0);  
            
        }        
       // }
    }
    
    int main(){
   //  dac.format(8,1);         // 8 bits per frame, mode 1(POL = 0, PHA = 1). 
  //   dac.frequency(1000000);  //1MHZ  
  //   resetpin= 1;
   //  clearpin = 1;
 
        AC_WRITE(10, 5, 1000); //to make continuous forever change for loop to
       // wait(1);
       
    getchar();
    getchar();
    return 0;
    }
    
