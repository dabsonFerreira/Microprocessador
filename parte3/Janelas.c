#include <mega32.h>
#include <stdio.h>
eeprom int combustivel = 0;
// Timer 0 overflow interrupt service routine
// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{ combustivel = combustivel - 20;
  if (PINB.6 == 1){
        
        PORTA.0 = ~PORTA.0 ;             
        TCNT1H=0x1F00 >> 8;
        TCNT1L=0x1F00 & 0xFF;
        while(PORTA.0 == 1){
            PORTA.0 = 1;
            if (PINB.6==0){                
                PORTA.0 = 0;
                break;
            }
        }
        
        
  }
        
 
    
   if (PINB.7 == 1){
       
       PORTA.1 = ~PORTA.1;
       TCNT1H=0x1F00 >> 8;
       TCNT1L=0x1F00 & 0xFF;
       
       while(PORTA.1 == 1){
            PORTA.1 = 1;
            if (PINB.7==0){
                PORTA.1 = 0;
                break;
            }
       }
   }  
}
       //DESLIGUEE ISSO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//interrupt [EXT_INT2] void ext_int2_isr(void)
//{
//   
//    
//
//}

void main(void)
{
// Declare your local variables here
PORTA=0x00;
DDRA=0x03;
// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=Out 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=0 State0=0 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 14,400 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Toggle
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=0x40;
TCCR1B=0x05;
TCNT1H=0x38;
TCNT1L=0x3F;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0xFF;
OCR1AL=0xFF;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;


// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: On
// INT2 Mode: Falling Edge
GICR|=(0<<INT1) | (0<<INT0) | (1<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (0<<INTF0) | (1<<INTF2);

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x04;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Global enable interrupts
#asm("sei")


while (1)
      {
         if (combustivel/1000 <=10)
         {
            printf("Alerta. Abasteça! Seu combustível é de %d", combustivel); 
         }
      }
}