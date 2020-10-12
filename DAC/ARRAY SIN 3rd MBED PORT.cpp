#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<stdint.h>
 
    float adjvoltage(float x);                          /* Prototype */
    int firstCommand (int channel);                     /* Prototype */
    unsigned char secondCommand(int adjVoltage);        /* Prototype */
    unsigned char thirdCommand(int adjVoltage);         /* Prototype */
    void DC_WRITE(int voltage, int channel);            /* Prototype */ 
    void AC_WRITE(int voltage, int channel, int freq);  /* Prototype */ 

    float adjvoltage(float x){
        float voltage = (x + 10.0) * (65535.0/20.0);
        return voltage;
    }

    int firstCommand (int channel) {
    int channelBits = 0;    
        switch (channel) { 
           case 202:channelBits= 0xC0;       //202 = All channels 
                break;  
           case 200:channelBits= 0xC1;       //200 = group 0
                break;
           case 201:channelBits= 0xC2;       //201 = group 1
                break;
            case 0: channelBits= 0xC8;       //0 = channel 0
                break;
            case 1: channelBits= 0xC9;       //1 = channel 1
                break;
            case 2: channelBits= 0xCA;       //2 = channel 2
                break;  
            case 3: channelBits= 0xCB;       //3 = channel 3
                break;
            case 4: channelBits= 0xD0;       //4 = channel 4
                break;
            case 5: channelBits= 0xD1;       //5 = channel 5
                break;
            case 6: channelBits= 0xD2;       //6 = channel 6
                break;
            case 7: channelBits= 0xD3;       //7 = channel 7
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
        unsigned char buff[50]; 
        for (int i=0 ; i<8 ; i++){
            if (byte & (1<<i)) rbyte |= (1<<(7-i));
        }
        return byte;
    }

    void DC_WRITE(float voltage, int channel){    
        voltage = adjvoltage(voltage);
        //printf("adjVOLTAGE: %f", voltage);   
        unsigned char first = firstCommand(channel);
        unsigned char second = secondCommand(voltage); 
        unsigned char third = thirdCommand(voltage); 
    }
    
    void AC_WRITE(float *one, int freq, int channel, int voltageA){
    float three[100];
    float actualTime=0.0;
    float PI = 3.14159; 
    actualTime=1.0/freq;

      int time=0; 
      for(float z=0; z<actualTime; z=z+(actualTime/100)){         
        three[time] = (sin(2*PI*freq*z)) *voltageA;         
        DC_WRITE(three[time],channel);          
        time++;                                                 
      }                                                         
    }                                                            
 
    int main(){
        float x[100];
        AC_WRITE(x,1000, 202, 5);//set 
        printf("hello world");
    getchar();
    getchar();
    return 0;
    }

