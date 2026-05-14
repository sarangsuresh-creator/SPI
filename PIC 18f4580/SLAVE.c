#include <xc.h>
#define _XTAL_FREQ 20000000  
#define baud_rate  9600
void string(char *s);
void mychar(char d);
void SPI_Slave_Init(void);
void uart_initiate(void);
unsigned char receivedData;

int i=0;
void main(void)
{
    ADCON1 = 0x0f;
    uart_initiate();
    SPI_Slave_Init();
    
  
    while(1)
    {   SSPIF = 0;
            
        SSPBUF  = '0'+i++;
        while(!SSPIF);
            receivedData = SSPBUF; 
           
            string("received character:");
            mychar(receivedData);
           string("\r\n");
          
 

      
    }
  }

void SPI_Slave_Init(void)
{
     TRISC|=0x18;
     TRISA = 0Xff;
    SSPSTAT = 0x40;    
    SSPCON1 = 0x24;    
   
}
void uart_initiate(){
   TRISC = 0x80;
  TXSTA = 0X24;
  RCSTA = 0X90;
  SPBRG = (((_XTAL_FREQ/baud_rate)/16)-1);
}

void string(char *s){
    while(*s){
     while(!PIR1bits.TXIF);
     TXREG = *s++;
        
    
    }
}
void mychar(char d){
      while(!PIR1bits.TXIF);
  TXREG = d;
    
}

