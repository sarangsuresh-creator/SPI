#include <xc.h>
#define _XTAL_FREQ 20000000  
#define baud_rate  9600
void string(char *s);
void mychar(char d);
void uart_initiate(void);

void SPI_Master_Init(void);
unsigned char receivedData;
int i;
void main(void)
{
    ADCON1 = 0x0F;
    uart_initiate();
    SPI_Master_Init();
    

    while(1)
    {
         SSPIF = 0;
         RA5 = 0;

            SSPBUF = '0'+i++;
            while(!SSPIF);
            receivedData = SSPBUF;
           
            RA5 = 1;
            string("received character:");
            mychar(receivedData);
           string("\r\n");
            __delay_ms(1000); 
    }
}

void SPI_Master_Init(void)
{
    TRISC|=0x10;
    TRISA = 0X00;
    RA5 = 1;
    SSPSTAT = 0x40; 
    SSPCON1 = 0x22;

}

void uart_initiate(){
  TRISC = 0x80;
  TXSTA = 0X24;
  RCSTA = 0X90;
  SPBRG = (((_XTAL_FREQ/baud_rate)/16)-1);
}
void string(char *s){
    while(*s){
       while(!TXIF);
       TXREG = *s++;
      
       
    }
}
void mychar(char d){
  while(!TXIF);
  TXREG = d;
   
   
}
