#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 8000000UL	 // 8 MHz clock speed
#endif


#define D4 eS_PORTB1
#define D5 eS_PORTB2
#define D6 eS_PORTB3
#define D7 eS_PORTB4
#define RS eS_PORTC5
#define EN eS_PORTC6

#include "lcd.h"

#include <string.h>
#include <stdlib.h>

#define SENS_OUTPUT_DDR DDRC
#define MOTOR_OUTPUT_DDR DDRB
#define SENS_INPUT_DDR DDRA
#define CUPSIZE_SELECT_DDR DDRD




volatile uint16_t mile_seconds =0;
int s[]={0,0,0,0,0};

int main(void){

    SENS_INPUT_DDR= 0x00;
	SENS_OUTPUT_DDR |=(1<<0) |(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	CUPSIZE_SELECT_DDR=0xff;
	MOTOR_OUTPUT_DDR |=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4);
		
	TIMSK=1<<OCIE0;
	OCR0=124;

    GICR |=1<<INT0 | 1<<INT1;
    MCUCR|=1<<ISC01 | 1<<ISC00 | 1<<ISC11 | 1<<ISC10;
    TCCR0=(1<<CS01) | (1<<WGM01) | (1<<WGM00) |(1<<CS00) ;
   uint16_t delay = 5000;
     
	sei();
	
	
	while(1){
    
    
    
     
	
	//......................................
	    	
		
		if(!(PINA &(1<<2))){
		
			PORTC=0x01;
			s[0]=1;
			
		
		}
		
		if((PINA &(1<<2))){
		
			PORTC=0x00;
			s[0]=0;
			
		
		}
		
		
		if(!(PINA &(1<<3))){
		
			PORTC=0x02;
			s[1]=1;
		
		}
		
		if((PINA &(1<<3))){
		
			PORTC=0x00;
			s[1]=0;
			
		
		}
		if(!(PINA &(1<<4))){
		
			PORTC=0x04;
			s[2]=1;
			
		
		}
		
		if((PINA &(1<<4))){
		
			PORTC=0x00;
			s[2]=0;
		
		}
		
		
		if(!(PINA &(1<<5))){
		
			PORTC=0x08;
			s[3]=1;
			
		
		}
		
		if((PINA &(1<<5))){
		
			PORTC=0x00;
			s[3]=0;
			
		
		}
		
		
		if(!(PINA &(1<<6))){
		
			PORTC=0x10;
			s[4]=1;
			
		
		}
		
		if((PINA &(1<<6))){
		
			PORTC=0x00;
			s[4]=0;
		//.........................................	
		
		}

        if(s[0]==0){
		
			PORTD=0;
			
		}
		if(s[1]==0){
		
			PORTD=0;
			
		}
        
        if(s[0]==0 &&s[1]==0 && s[2]==0 && s[3]==0 && s[4]==0){
        
             Lcd4_Set_Cursor(1,2);
	         Lcd4_Write_String("KEEP THE CUP ");

	         _delay_ms(2000);
			 	
			
		}

        
        
        
		if(s[0]==1 &&s[1]==1 && s[2]==0 && s[3]==0 && s[4]==0){
		
			if(	 mile_seconds>=1000){
		
			PORTB ^=(1<<0);
			 mile_seconds = 0;
             
              Lcd4_Set_Cursor(1,2);
              Lcd4_Write_String("VOLUME = 100ml");
	          _delay_ms(2000);
			 
		
		
		}
		
		
				_delay_ms(1000000);


		
			PORTD=0x80;
			
			
		}
		if(s[0]==1 && s[1]==1 && s[2]==1 && s[3]==0 &&s[4]==0){
		
			if(	 mile_seconds>=3000){
		
			PORTB ^=(1<<0);
			 mile_seconds = 0;
             
             Lcd4_Set_Cursor(1,2);
	         Lcd4_Write_String("VOLUME = 275ml");
		      _delay_ms(2000);
		
		
		}
		
			PORTD=0x40;
			
			
		}
		if(s[0]==1 && s[1]==1 && s[2]==1 && s[3]==1 &&s[4]==0){
		
			if(	 mile_seconds>=5300){
		
			PORTB ^=(1<<0);
			 mile_seconds = 0;
             
              Lcd4_Set_Cursor(1,2);
	          Lcd4_Write_String("VOLUME = 650ml");
		      _delay_ms(2000);
		
		
		}
		
			PORTD=0x08;
			
			
		}
		if(s[0]==1 && s[1]==1 && s[2]==1 && s[3]==1 &&s[4]==1){
		
			if(	 mile_seconds>6000){
		
			PORTB ^=(1<<0);
			 mile_seconds = 0;
             
             Lcd4_Set_Cursor(1,2);
	         Lcd4_Write_String("VOLUME = 800ml");
		     _delay_ms(2000);
		
		
		}
		
			PORTD=0x10;
			
			
		}
		Lcd4_Set_Cursor(1,2);
	    Lcd4_Write_String("THANK YOU!");
		
		_delay_ms(2000);	
		
	}
    
	
	
	
}

ISR(TIMER0_COMP_vect){
   
  mile_seconds++; 
    		
  }



