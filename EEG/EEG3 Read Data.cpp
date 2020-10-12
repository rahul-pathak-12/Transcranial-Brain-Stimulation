#include "mbed.h"

/*Define SPI Master pins*/
SPI master(p5, p6, p7);     // MOSI, MISO, SCLK
DigitalOut _CS(p8);         // \CS

/*Print to PC screen in Tera Term terminal window*/
Serial pc(USBTX, USBRX);        //PC Communication via USB
LocalFileSystem local("local"); //txt location

/*Define ADS1298 pins*/
DigitalOut CLKSEL(p9); 
DigitalOut _PWDN_RESET(p10);
DigitalIn _DRDY(p11);
DigitalOut START(p12);

/***** MAIN *****/
int main() {
    master.format(8,1);           //8 bits per frame, mode 1(POL = 0, PHA = 1). 
    master.frequency(10000);      //10kHZ 
    
    pc.printf("\n /***************************************/\n");
    pc.printf(" /*           Boot-up Sequence          */\n");
    pc.printf(" /*               ADS1298               */\n");
    pc.printf(" /***************************************/\n\n");
    
    CLKSEL = 1;                   //use internal clock
    wait_us(10);
    _PWDN_RESET = 1;            
    wait(1);                      //delay for power-on
    
    _CS = 0;                      //begin master transmission
        pc.printf(" //====================[Begin Transmission]\n");
        master.write(0x06);       //RESET command, could use _RESET pin
        wait_us(10);
            pc.printf("\n   RESET\n");    

        master.write(0x11);       //SDATAC stop data continuous command //===========================================> may cause problems for continuous. 
            pc.printf("   SDATAC\n");
        wait_us(3);
                    
        master.write(0x0A);//stop command
            pc.printf("   STOP\n\n");
         wait_us(3);
            
       //Write Configuration Register 3 (RLD and Vref)     
        master.write(0x43);         //address of register to be written to
        wait_us(3);                 //wait 4tclk approx. 1.96us for CLK=2.048MHz delay required when 8tsclk>4tclk
        master.write(0x00);         //number of registers
        wait_us(3);
        master.write(0xC8);         //data sent
            pc.printf("   Config3 (Internal Reference)\n");
    _CS = 1;
         
        //Read Configuration Register 3
    _CS = 0;
        master.write(0x23);
        wait_us(3);
        master.write(0x00);
        wait_us(3);
        char config3 = master.write(0x00);
            pc.printf("   Configuration 3: 0x%X\n\n",config3);
        wait_us(6);

        //Write Configuration Register 1 (High Resolution and Data Rate)      
        master.write(0x41);
        wait_us(3);
        master.write(0x00);
        wait_us(3);
        master.write(0xE6); //output internal clock on CLK pin, verify 2.048MHz
            pc.printf("   Config1 (High Resolution 500SPS)\n");
        
            //Read Configuration Register 1   
        master.write(0x21);
        wait_us(3);
        master.write(0x00);
        wait_us(3);
        char config1 = master.write(0x00);
            pc.printf("   Configuration 1: 0x%X\n\n",config1);            
 
            //Set all Channels (default=ON), gain=1 (default=6), normal electrode input (default)                    
        master.write(0x45); //opcode 1: address of first register to write to
        wait_us(3);
        master.write(0x07); //opcode 2: number of registers to write to
        wait_us(3); 
        master.write(0x10); //chn1 ON
        wait_us(3);
        master.write(0x10); //chn2 OFF
        wait_us(3);
        master.write(0x10); //chn3 OFF
        wait_us(3);
        master.write(0x10); //chn4 ON
        wait_us(3);
        master.write(0x10); //chn5 OFF
        wait_us(3);
        master.write(0x10); //chn6 ON
        wait_us(3);
        master.write(0x10); //chn7 OFF
        wait_us(3);
        master.write(0x90); //chn8 OFF
            pc.printf("   CHnSET (gain 1), Chn 1, 4 and 6 ON\n");      
            /** TEST WRITE LOFF_SENSP**/
        master.write(0x4F);
        master.write(0x00);
        master.write(0xFF);
            /** TEST READ LOFF_SENSP**/
        master.write(0x2F);
        master.write(0x00);
        int LOFF_SENSP = master.write(0x00);
            pc.printf("   LOFF_SENSP: %X\n", LOFF_SENSP);
            /** TEST READ LOFF_STATP**/
        master.write(0x3F);
        master.write(0x00);
        int LOFF_STATP = master.write(0x00);
            pc.printf("   LOFF_STATP: %x\n", LOFF_STATP);  
        
       //Start recording                       
        master.write(0x08);  //START = 1;
            pc.printf("   START RECORDING \n");
        
       //Read Data Continuous mode            
       //master.write(0x10);
       //pc.printf("RDATAC\n");   
              
        //Read Data
        wait_us(10);
        master.write(0x12); //RDATA
            pc.printf("   RDATA\n\n");
            pc.printf(" //=====================[End Transmission]\n\n");//end transmission    
    _CS = 1;

    pc.printf("   Await _DRDY...\n");//monitor _DRDY      
   int count=0;
   int channel=1;
        if(!_DRDY){ //when _DRDY goes low,
            _CS = 0;
                pc.printf("\n DATA:\n");
                for(int i=0; i<27; i++){ //27
                    int x = master.write(0x00);
                        pc.printf("\t 0x%X\n", x); 
                    count++;
                        if(count==3){
                            pc.printf("\nChannel %d: \n", channel);
                            channel++;
                            count=0;
                       }
                    /*  FILE *fp = fopen("/local/ADS1298_test.txt", "w");
                    fprintf(fp, "%X\n%", i);
                    fclose(fp);*/
                }
        } 
//    _CS = 1;                           
}
