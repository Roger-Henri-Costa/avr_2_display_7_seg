#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>



char digitos7seg[10] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F}; // Definindo os nmrs

void disp7seg_init( void )
{
	// Inicializando saídas
    DDRD  = 0xFF;
    PORTD = 0x00;
	DDRB  = 0x03;
    PORTB = 0x00;
}

void disp7seg_de( unsigned char d )
{
	PORTB = 0; // zerando os transistores
    PORTD = digitos7seg[(d/10)%10]; // adicionando a dezena no display
	PORTB = 0x01; // setando o display da dezena
}

void disp7seg_un( unsigned char d )
{
	PORTB = 0;
	PORTD = digitos7seg[d%10];
	PORTB = 0x02;
}
unsigned char disp7seg_scan = 0;

void disp7seg ( unsigned char d )
{
	if(disp7seg_scan%2)
	{
		disp7seg_un( d );		
	}
	else 
	{	
		disp7seg_de( d );
	}
	disp7seg_scan++;
}

int main(void) 
{
	char i = 0;
	long t = 0;	
    disp7seg_init();
	
    while( 1 )
    {
        disp7seg(i);
		_delay_ms(1);
		t++;
		if((t%500)==0)
		{
			i = ++i % 100;
		}
    }
}