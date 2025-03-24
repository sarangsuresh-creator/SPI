#include <xc.h>
#define _XTAL_FREQ 20000000  
#define baud_rate  9600
void string(char *s);
void mychar(char d);
void SPI_Slave_Init(void);
void uart_initiate(void);
unsigned char receivedData,transmitData;

int i=0;
void main(void)
{
    SPI_Slave_Init();
    uart_initiate();
  
    while(1)
    {
       
        if(SSPIF)  
        {
           receivedData = SSPBUF; 
            if(receivedData != 0Xff){
            string("received character:");
            mychar(receivedData);
            mychar('\n\r');
          
            SSPIF = 0;
            
        }else{
     
          transmitData = '0'+i;
          SSPBUF = transmitData;
          while(!SSPIF);
          i++;
          SSPIF = 0;
      
        }
      }
    }
  }

void SPI_Slave_Init(void)
{
    TRISC = 0x19;

    SSPSTAT = 0x00;    
    SSPCON1 = 0x24;    
    PIR1bits.SSPIF = 0;
}
void uart_initiate(){
  TXSTA = 0X24;
  RCSTA = 0X90;
  SPBRG = (((_XTAL_FREQ/baud_rate)/16)-1);
}

void string(char *s){
    while(*s){
        TXREG = *s++;
        while(!PIR1bits.TXIF);
        PIR1bits.TXIF = 0;
    }
}
void mychar(char d){
    TXREG = d;
    while(!PIR1bits.TXIF);
    PIR1bits.TXIF = 0;
}


    


        
 




