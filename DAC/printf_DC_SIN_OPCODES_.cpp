#include <stdio.h>
#include <math.h>
 
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
           case 202:channelBits= 11000000;       //All channels 
                break;  
           case 200:channelBits= 11000001;       //group 0
                break;
           case 201:channelBits= 11000010;       //group 1
                break;
            case 0: channelBits= 11001000;       //channel 0
                break;
            case 1: channelBits= 11001001;       //channel 1
                break;
            case 2: channelBits= 11001010;       //channel 2
                break;  
            case 3: channelBits= 11001011;       //channel 3
                break;
            case 4: channelBits= 11010000;       //channel 4
                break;
            case 5: channelBits= 11010001;       //channel 5
                break;
            case 6: channelBits= 11010010;       //channel 6
                break;
            case 7: channelBits= 11010011;       //channel 7
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
       // float voltage16 = adjvoltage(voltage);
       printf("SIN VOLTAGE: %f\n", voltage);
        unsigned char first = firstCommand(channel);
        unsigned char second = secondCommand(voltage);
        unsigned char third = thirdCommand(voltage);
        
       /*  
        FILE *file; 
            file = fopen("C:\\Users\\001\\Desktop\\oldvoltage16.txt","a+"); //APPEND
            fprintf(file,"%f\n",voltage16); //WRITE
            fclose(file); //CLOSE
        
        printf("FIRST:  %x\n", first);
        printf("SECOND: %x\n",second);
        printf("THIRD:  %x\n",third);  
            FILE *file; 
            file = fopen("C:\\Users\\001\\Desktop\\vacc.txt","a+"); //APPEND
            fprintf(file,"%x%x\n",second, third); //WRITE
            fclose(file); //CLOSE
        */
    }
    

    void AC_WRITE(int voltage, int channel, int freq){
        float PI = 3.14159;    
        for(float i=0; i<2*PI; i=i+0.01){
            float sinvoltage = sin(i*2*PI*freq)*voltage;
            DC_WRITE(sinvoltage, channel);  
        }
        
    }
    
    int main(){
        //DC_WRITE(2, 202);   //5 volts on all channels. 
        AC_WRITE(10, 202, 1);
    getchar();
    getchar();
    return 0;
    }
    
// roundf ??
