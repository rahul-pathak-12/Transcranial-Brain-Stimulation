#include <stdio.h>
#include <math.h>
#include <mbed.h>

/* Establish communication from LPC1768 to 
 * AD5362 using SPI and enable voltage 
 * output to selected channel either by DC 
 * or AC.  
 * 
 * The following functions are the only ones 
 * that need to be used; 
 *  
 *      DC_WRITE(volts, channel);    
 *      AC_WRITE(volts, channel, frequency);
 *
 * Chip select and delay are dealt with in 
 * DC_WRITE(x,y).  
 * @Author: Rahul Pathak 
 */ 
    float adjvoltage(float x);                          /* Prototype */
    int firstCommand (int channel);                     /* Prototype */
    unsigned char secondCommand(int adjVoltage);        /* Prototype */
    unsigned char thirdCommand(int adjVoltage);         /* Prototype */
    void DC_WRITE(int voltage, int channel);            /* Prototype */ 
    void AC_WRITE(int voltage, int channel, int freq);  /* Prototype */ 
    
    /* SPI parameters:
     *              pin 5: MOSI
     *              pin 6: MISO
     *              pin 7: Serial Clock
     *              pin 8: Chip Select
     *              pin 9: Selected High
     *              pin 10: Selected High
     */
    SPI dac(p5, p6, p7);     
    DigitalOut cs(p8);       
    DigitalOut resetpin(p9); 
    DigitalOut clearpin(p10);   

    /*  @param: float x
     *  @return: float voltage 
     *        
     *   A function to adjust normal voltage to create 
     *   a integer of appropriate size which utilises 
     *   16 bit binary. This float is then returned. 
     */
    float adjvoltage(float x){
        float voltage = (x + 10.0) * (65535.0/20.0);//force float
        return voltage;
    }
    
    /*  @param: int channel
     *  @return:int channelBits
     *
     *   A function which generates both the method code
     *   alongside the channel code. (switch faster than 
     *   if else).
     *   
     *   [X][X] - [X][X][X][X][X][X]
     *   method   Channel 
     *   
     *   these bits are then returned. 
     */
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
    
    /*  @param: int adjVoltage
     *  @return: unsigned char
     *
     *  A function to shift the integer 8 bits to the 
     *  right in order to obtain the first 8 bits of
     *  the parameter adjVoltage. 
     */
    unsigned char secondCommand(int adjVoltage){
        return adjVoltage >> 8;
    }
    
    /*  @param: int adjVoltage
     *  @return: unsigned char
     *  
     *  A function to reverse the bits and manipulate
     *  the bits in order to obtain the last 8 bits of 
     *  the parameter adjVoltage. 
     */
    unsigned char thirdCommand(int adjVoltage){
        unsigned char rbyte = 0;
        unsigned char byte = adjVoltage; // Value to Be Reversed

        for (int i=0 ; i<8 ; i++)
            if (byte & (1<<i)) rbyte |= (1<<(7-i));
        return byte;
    }
    
    /*  @param: int voltage
     *          int channel       
     *  @return: void
     *
     *  This method takes the voltage and channel code
     *  it will then write these opcodes to the AD5362
     *  it does this in 8 bit frames (spi limit). 
     *
     *  first = 8 bits (2bits method, last 6bits are channel).
     *  second = 8bits (first half of voltage).
     *  third = 8 bits (second half of voltage). 
     */
    void DC_WRITE(int voltage, int channel){
        float voltage16 = adjvoltage(voltage);
    
        unsigned char first = firstCommand(channel);
        unsigned char second = secondCommand(voltage16);
        unsigned char third = thirdCommand(voltage16);
        
        cs=0;
        dac.write(first);
        dac.write(second);
        dac.write(third);
        cs=1;
        wait_us(0.1);
    }
    
    /*  @param: int voltage
     *          int channel
     *          int freq       
     *  @return: void
     *
     *  Uses a sine function to generate a sine wave  
     *  values are taken at 0.01 increments. Uses the
     *  following equation:
     *                     sin(2*pi*f*t)*voltage
     *                      pi=3.14159265358979...
     *                      f = frequency
     *                      t = increment (time)
     *                      voltage = voltage
     */
    void AC_WRITE(int voltage, int channel, int freq){
        rate = 1/((2*freq)+1);
        float PI = 3.14159;    
        for(float i=0; i<2*PI; i=i+rate){
            float sinvoltage = sin(i*2*PI*freq)*voltage;
            DC_WRITE(sinvoltage, channel);  //output voltage to DAC
        }
    }
    
    int main(){
     dac.format(8,1);         // 8 bits per frame, mode 1(POL = 0, PHA = 1). 
     dac.frequency(1000000);  //1MHZ  
     resetpin= 1;
     clearpin = 1;
     
        DC_WRITE(4, 202);   //5 volts on all channels. 
        AC_WRITE(5, 202, 2); //to make continuous forever change for loop to:
                            // for(int i=0; i>=0; i=i+0.1) // wil go on forever. 
    return 0;
    }
    

