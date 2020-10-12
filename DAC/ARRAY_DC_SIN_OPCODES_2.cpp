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
        unsigned char first = firstCommand(channel);//FINE
        unsigned char second = secondCommand(voltage); //fine
        unsigned char third = thirdCommand(voltage); //SOME WEIRD SHIT GOING ON HERE
         
         //   FILE *file; 
        //    file = fopen("C:\\Users\\001\\Desktop\\100hz.txt","a+"); //APPEND
        //    fprintf(file,"%x%x\n",second, third); //WRITE
        //    fclose(file); //CLOSE
    }
    
    void AC_WRITE(float *one, int freq, int channel, int voltageA){
   // float one[100]; passed as x
    float two[100];
    float three[100];
    float the100 = 0;
    float actualTime=0.0;
    
    float PI = 3.14159; 
    int count=-1;
    float sum=0;
    float average = 0;
        float limit = (2*PI); ///6
        
        int counter=0;       
        for(float i=0; i<limit; i+=(0.0628)){                           //ORINGINAL WAVE
            one[counter] = adjvoltage((sin(2*PI*freq*i)) *voltageA);   //
            counter++ ;                                                 //
        }                                                               //
        
        for (int a=0; a<=100; a++){ //AVERAGEE
          sum=sum+one[a];          //
        }                           //
        average = sum/100;          //

        for(int y=0; y<100; y++){   //RENORMALISE
        two[y] = one[y]-average;    //
        }                           //
      
      for(int x=0; x<=100; x++){        //COUNT
        if(two[x]>=0 && two[x+1]<=0){   //
        the100 =  (two[x]+average)/voltageA;      //
       // actualTime = (asin(the100))/(2*PI*freq);
        printf("%f\n", the100);
        printf("%f\n", two[x]/5);
        break;
        }                               //
      }                                 //
    
      int time=0; 
      for(float z=0; z<actualTime; z=z+(0.0628/actualTime)){              //FIND NEW
        three[time] = adjvoltage((sin(2*PI*freq*z)) *voltageA);  //          
        DC_WRITE(three[time],channel);  
       // FILE *file; 
       // file = fopen("C:\\Users\\001\\Desktop\\100hz.txt","a+"); 
       // fprintf(file,"%f\n", three[time]); 
       // fclose(file);
        time++;                                                 
      }                                                          
    }                                                            
 
    int main(){
        float x[100];
        AC_WRITE(x,100, 202, 5);//set 
    getchar();
    getchar();
    return 0;
    }

