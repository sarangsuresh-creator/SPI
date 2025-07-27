#include <xc.h>
#define _XTAL_FREQ 20000000  
#define baud_rate  9600
void string(char *s);
void mychar(char d);
void uart_initiate(void);

void SPI_Master_Init(void);
void SPI_Master_Write(unsigned char data);
unsigned char receivedData;
int i;
void main(void)
{
    SPI_Master_Init();
    uart_initiate();

    while(1)
    {

            SSPBUF = '0'+i++;
            SSPIF=0;
            while(!PIR1bits.SSPIF);
            receivedData = SSPBUF;
            string("received character:");
            mychar(receivedData);
            mychar('\n\r');
            __delay_ms(1000); 
    }
}

void SPI_Master_Init(void)
{
    TRISC = 0x90;
    SSPSTAT = 0x00; 
    SSPCON1 = 0x22;
    PIR1bits.SSPIF = 0;
}

void SPI_Master_Write(unsigned char data)
{
    SSPBUF = data;
    while(!PIR1bits.SSPIF);
    SSPIF = 0;
}
void uart_initiate(){
  TXSTA = 0X24;
  RCSTA = 0X90;
  SPBRG = (((_XTAL_FREQ/baud_rate)/16)-1);
}
void string(char *s){
    while(*s){
        TXREG = *s++;
        while(!TXIF);
        TXIF = 0;
    }
}
void mychar(char d){
    TXREG = d;
    while(!TXIF);
    TXIF = 0;
}















        
 
