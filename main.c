#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect) 
{ 
}

void UARTInit( void ) {
	UBRRL = 103;
	UBRRH = 0;
	UCSRA = 0;
	UCSRB = 0b00011000;
	UCSRC = 0b10000110;
}

void sendUART ( unsigned char c ) {
	while( !(UCSRA & (1 << UDRE))) {
	}
	UDR = c;
}

unsigned char readUART( void ) {
	while(!(UCSRA & (1 << RXC ))) {
	}
	return UDR; 
}	

void greenHighlight( void ) {
	PORTD &= 0b01111111;//зажигаем зеленый
}

void yellowHighlight( void ) {
	PORTD &= 0b10111111;//зажигаем желтый
}

void greenUnhighlight( void ) {
	PORTD |= 0b10000000;//зажигаем зеленый
}

void yellowUnhighlight( void ) {
	PORTD |= 0b01000000;//зажигаем желтый
}
 
int main( void ) {
	DDRA = 0b00001111; //конф как выходы
	DDRB = 0b00001111;
	DDRD = 0b11000000;
	unsigned char i;
	PORTA = 0x00;	
	PORTB = 0b101;

	unsigned char fine1=0;
	unsigned char fine2=0;
	greenHighlight();
	yellowUnhighlight();

	while(1) {
		PORTA |= 0b1111;
		_delay_ms( 100 );  
	  	i = PINA;
		if(i >> 4 != 0b1111) {
			yellowHighlight();
			greenUnhighlight();
			fine1=0;
		}
		else {
			if(fine1 && fine2)
				greenHighlight();
			fine1=1;
		}
		_delay_ms( 100 );  		
		PORTA &= 0b11110000;
		_delay_ms( 100 );  
	  	i = PINA;
		if(i >> 4 != 0b0000) {
			yellowHighlight();
			greenUnhighlight();	
			fine2=0;	
		}			
		else {
			if(fine1 && fine2)
				greenHighlight();				
			fine2=1;
		}
		_delay_ms( 100 );  
	}	
	return 0;
}
