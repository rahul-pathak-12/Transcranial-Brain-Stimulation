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
      /*  if(byte<15){
            char buff[2];
            sprintf(buff,"0%x" ,byte);
             //   printf("BUFF: %s\n",buff);
           // byte = strtol(buff, NULL, 10);
              //  printf("BYTE: %x\n",byte);
               printf("BUFF: %d\n",byte);
              byte = (int) buff;
              printf("BUFF: %x\n",byte);
            return byte;
       // return buff;
        }*/
        return byte;
    }

  //  int *thirdCommand(int adjVoltage){
    //}
    
    void DC_WRITE(float voltage, int channel){    
        unsigned char first = firstCommand(channel);//FINE
        unsigned char second = secondCommand(voltage); //fine
        unsigned char third = thirdCommand(voltage); //SOME WEIRD SHIT GOING ON HERE
         
      //  printf("FIRST:  %x\n", first);
       // printf("SECOND: %x\n",second);
      //  printf("THIRD:  %x\n",third); 
         //   FILE *file; 
        //    file = fopen("C:\\Users\\001\\Desktop\\100hz.txt","a+"); //APPEND
        //    fprintf(file,"%x%x\n",second, third); //WRITE
        //    fclose(file); //CLOSE
    }
    
    void AC_WRITE(float *xalter, int freq, int channel, int voltageA){
    float xadjusted[100];
    float PI = 3.14159; 
    int count=-1;
    float sum=0;
    float average = 1;
        int t=0;
        float limit = (2*PI); ///6
               
        for(float i=0; i<limit; i+=(0.0628)){//6
            xalter[t] = adjvoltage((sin(2*PI*freq*i)) *voltageA); //voltage      
            
            /*FILE *file; 
            file = fopen("C:\\Users\\001\\Desktop\\1.txt","a+"); //APPEND
            fprintf(file,"%f\n",xalter[t]); //WRITE
            fclose(file);  //CLOSE*/
            
            t++ ;
        }
        
        for (int a=0; a<=100; a++){
          sum=sum+xalter[a];  
        }
        
        average = sum/100;        //find average
        printf("AVERAGE: %f", average);
        
        for(int y=0; y<100; y++){           //problem here
        xadjusted[y] = xalter[y]-average;
        
       /* FILE *file; 
            file = fopen("C:\\Users\\001\\Desktop\\2.txt","a+"); //APPEND
            fprintf(file,"%f\n",xadjusted[y]); //WRITE
            fclose(file);  //CLOSE*/
        }
      
      for(int x=0; x<=101; x++){
        if(xadjusted[x]<=0 && xadjusted[x+1]>=0){
        count++;
        }
      }
       // printf("%d",count); 
        int time=0; 
        for(float z=0; z<(limit/count); z+=(0.0628/count)){//6
            xalter[time] = adjvoltage((sin(2*PI*freq*z)) *voltageA);          
            DC_WRITE(xalter[time],channel);
          
            /*FILE *file; 
            file = fopen("C:\\Users\\001\\Desktop\\3.txt","a+"); //APPEND
            fprintf(file,"%f\n",xalter[time]); //WRITE
            fclose(file);  //CLOSE*/
            
            time++;
        }
    }   
 
   /* void AC_WRITE(int voltage, int channel, int freq){
        float PI = 3.14159;    
        for(float i=0; i<2*PI; i=i+0.01){
            float sinvoltage = sin(i*2*PI*freq)*voltage;
           // printf("SIN VOLTAGE: %f\n", sinvoltage);
            DC_WRITE(sinvoltage, channel);  
        }
    }*/
    
    int main(){
        float x[100];
        AC_WRITE(x,100, 202, 5);//set 
        
        //DC_WRITE(2, 202);   //5 volts on all channels. 
       // AC_WRITE(10, 202, 1);
    
    getchar();
    getchar();
    return 0;
    }

