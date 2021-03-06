#include <mega32.h>
#include <stdio.h>
#include <alcd.h>
#include <delay.h>

char painel1[33];
char painel2[33];

eeprom int combustivel = 28000;
int isConsumindoCombustivel = 0;
 //JANELA 
int isJanelaE = 0;
int isJanelaD = 0;

//Porta
int isPortaE = 0;
int isPortaD = 0;

//Parabrisa
int isParabrisaF = 0;
int isParabrisaT = 0;
 
int isMovimento0 = 0;
 
void diminuiCombustivel() {
     if (combustivel > 0) {
         combustivel -= 1001;
     } else {
         combustivel = 28000;
         printf("O Sistema ficou sem combustivel, para reabastecer aperte qualquer bot?o!\n");
         
     }
     isConsumindoCombustivel = 0;
 }

 // External Interrupt 0 service routine
 interrupt[EXT_INT0]void ext_int0_isr(void) {
     // Place your code here
     if (PINB.4 == 1) {
         PORTD.0 = ~PORTD.0; 
         isConsumindoCombustivel = 1;
         if (PORTD.0){
            isParabrisaT = 1;}
         else{
            isParabrisaT=0;}
     }

     if (PINB.3 == 1) {
         PORTD.1 = ~PORTD.1;
         isConsumindoCombustivel = 1;  
         if (PORTD.1){
            isParabrisaF = 1;}
         else{
            isParabrisaF = 0;}
     }

     //HABILITANDO O isConsumindoCombustivel DE COMBUSTIVEL AO USAR O LIMPADOR
     //if (PINB.4 || PINB.3) {
        // isConsumindoCombustivel = 1;
     //}
 }

 interrupt[EXT_INT1]void ext_int1_isr(void) {
     //Place your code here
     if (PINB.1 == 1) {
         PORTD.4 = ~PORTD.4;
         isConsumindoCombustivel = 1;
         if (PORTD.4){    
            isPortaE = 1;}
         else{
            isPortaE = 0;}
     }

     if (PINB.0 == 1) {
         PORTD.6 = ~PORTD.6;
         isConsumindoCombustivel = 1;
         if (PORTD.6){    
            isPortaD = 1;}
         else{
            isPortaD = 0;}
     }

     //HABILITANDO O isConsumindoCombustivel DE COMBUSTIVEL AO USAR O LIMPADOR
     //if (PINB.1 || PINB.0) {
         //isConsumindoCombustivel = 1;
     //}
 }

 interrupt[TIM1_OVF]void timer1_ovf_isr(void) {
     //HABILITANDO O isConsumindoCombustivel DE COMBUSTIVEL AO USAR O LIMPADOR
     //if (PINB.6 || PINB.7) {
       //  isConsumindoCombustivel = 1;
     //}

     if (PINB.6 == 1) {
         isConsumindoCombustivel = 1;
         PORTA.0 = ~PORTA.0;
         TCNT1H = 0x1F00 >> 8;
         TCNT1L = 0x1F00 & 0xFF;
         isMovimento0 = 0;
         if (isJanelaE){
            isJanelaE = 0;
        }
         else{
            isJanelaE = 1;
         }
         while (PORTA.0 == 1) {
             PORTA.0 = 1;
             if (PINB.6 == 0) {
                 PORTA.0 = 0;
                 isMovimento0 = 1;
                 break;
             }
         }
     }

     if (PINB.7 == 1) {
         isConsumindoCombustivel = 1;
         PORTA.1 = ~PORTA.1;
         TCNT1H = 0x1F00 >> 8;
         TCNT1L = 0x1F00 & 0xFF;
         isMovimento0 = 0; 
         if (isJanelaD){
            isJanelaD = 0;
         }
         else{
            isJanelaD = 1;
         }
         while (PORTA.1 == 1) {
             PORTA.1 = 1;
             if (PINB.7 == 0) {
                 PORTA.1 = 0;
                 isMovimento0 = 1;
                 break;
             }
         }
     }

 }

 // Declare your global variables here
 void main(void) {
     // Declare your local variables here
     // Input/Output Ports initialization
     // Port A initialization
     // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
     DDRA = (0 << DDA7) | (0 << DDA6) | (0 << DDA5) | (0 << DDA4) | (0 << DDA3) | (0 << DDA2) | (1 << DDA1) | (1 << DDA0);
     // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=0
     PORTA = (0 << PORTA7) | (0 << PORTA6) | (0 << PORTA5) | (0 << PORTA4) | (0 << PORTA3) | (0 << PORTA2) | (0 << PORTA1) | (0 << PORTA0);

     // Port B initialization
     // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
     DDRB = (0 << DDB7) | (0 << DDB6) | (0 << DDB5) | (0 << DDB4) | (0 << DDB3) | (0 << DDB2) | (0 << DDB1) | (0 << DDB0);
     // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
     PORTB = (0 << PORTB7) | (0 << PORTB6) | (0 << PORTB5) | (0 << PORTB4) | (0 << PORTB3) | (0 << PORTB2) | (0 << PORTB1) | (0 << PORTB0);

     // Port C initialization
     // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
     DDRC = (0 << DDC7) | (0 << DDC6) | (0 << DDC5) | (0 << DDC4) | (0 << DDC3) | (0 << DDC2) | (0 << DDC1) | (0 << DDC0);
     // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
     PORTC = (0 << PORTC7) | (0 << PORTC6) | (1 << PORTC5) | (0 << PORTC4) | (0 << PORTC3) | (0 << PORTC2) | (0 << PORTC1) | (0 << PORTC0);

     // Port D initialization
     // Function: Bit7=In Bit6=Out Bit5=Out Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=Out
     DDRD = (0 << DDD7) | (1 << DDD6) | (0 << DDD5) | (1 << DDD4) | (0 << DDD3) | (0 << DDD2) | (1 << DDD1) | (1 << DDD0);
     // State: Bit7=T Bit6=0 Bit5=0 Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=0
     PORTD = (0 << PORTD7) | (0 << PORTD6) | (0 << PORTD5) | (0 << PORTD4) | (0 << PORTD3) | (0 << PORTD2) | (0 << PORTD1) | (0 << PORTD0);

     // Timer/Counter 0 initialization
     // Clock source: System Clock
     // Clock value: Timer 0 Stopped
     // Mode: Normal top=0xFF
     // OC0 output: Disconnected
     TCCR0 = (0 << WGM00) | (0 << COM01) | (0 << COM00) | (0 << WGM01) | (0 << CS02) | (0 << CS01) | (0 << CS00);
     TCNT0 = 0x00;
     OCR0 = 0x00;

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
     // Compare A Match Interrupt: Off
     // Compare B Match Interrupt: Off
     TCCR1A = 0x00;
     TCCR1B = 0x05;
     TCNT1H = 0x38;
     TCNT1L = 0x3F;
     ICR1H = 0x00;
     ICR1L = 0x00;
     OCR1AH = 0x00;
     OCR1AL = 0x00;
     OCR1BH = 0x00;
     OCR1BL = 0x00;

     // Timer/Counter 2 initialization
     // Clock source: System Clock
     // Clock value: Timer2 Stopped
     // Mode: Normal top=0xFF
     // OC2 output: Disconnected
     ASSR = 0 << AS2;
     TCCR2 = (0 << PWM2) | (0 << COM21) | (0 << COM20) | (0 << CTC2) | (0 << CS22) | (0 << CS21) | (0 << CS20);
     TCNT2 = 0x00;
     OCR2 = 0x00;

     // Timer(s)/Counter(s) Interrupt(s) initialization
     TIMSK = 0x04;

     // External Interrupt(s) initialization
     // INT0: On
     // INT0 Mode: Low level
     // INT1: On
     // INT1 Mode: Low level
     // INT2: Off
     GICR |= (1 << INT1) | (1 << INT0) | (0 << INT2);
     MCUCR = (0 << ISC11) | (0 << ISC10) | (0 << ISC01) | (0 << ISC00);
     MCUCSR = (0 << ISC2);
     GIFR = (1 << INTF1) | (1 << INTF0) | (0 << INTF2);

     // USART initialization
     // USART disabled
     //UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

     // Analog Comparator initialization
     // Analog Comparator: Off
     // The Analog Comparator's positive input is
     // connected to the AIN0 pin
     // The Analog Comparator's negative input is
     // connected to the AIN1 pin
     ACSR = (1 << ACD) | (0 << ACBG) | (0 << ACO) | (0 << ACI) | (0 << ACIE) | (0 << ACIC) | (0 << ACIS1) | (0 << ACIS0);
     SFIOR = (0 << ACME);

     // ADC initialization
     // ADC disabled
     ADCSRA = (0 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) | (0 << ADIE) | (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0);

     // SPI initialization
     // SPI disabled
     SPCR = (0 << SPIE) | (0 << SPE) | (0 << DORD) | (0 << MSTR) | (0 << CPOL) | (0 << CPHA) | (0 << SPR1) | (0 << SPR0);

     // TWI initialization
     // TWI disabled
     TWCR = (0 << TWEA) | (0 << TWSTA) | (0 << TWSTO) | (0 << TWEN) | (0 << TWIE);
     // Alphanumeric LCD initialization
     // Connections are specified in the
     // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
     // RS - PORTC Bit 0
     // RD - PORTC Bit 1
     // EN - PORTC Bit 2
     // D4 - PORTC Bit 4
     // D5 - PORTC Bit 5
     // D6 - PORTC Bit 6
     // D7 - PORTC Bit 7
     // Characters/line: 8

     lcd_init(16);
     
 
 
     // Globally enable interrupts
      # asm("sei")while (1) {
        /* if (((PINB.4) || (PINB.3) || (PINB.1) || (PINB.0) || (PORTA.1 == 0 && isMovimento0 == 1) || (PORTA.0 == 0 && isMovimento0 == 1)) && (combustivel <= 10000)) {
             printf("Aten??o! Seu combust?vel em n?vel critico!\n");
             printf("Seu combust?vel ? de %d.\n", combustivel);
         }

         if ((PINB.4) || (PINB.3) || (PINB.1) || (PINB.0) || (PORTA.1 == 0 && isMovimento0 == 1) || (PORTA.0 == 0 && isMovimento0 == 1) && (combustivel >= 10000)) {
             printf("Seu combust?vel ? de %d.\n", combustivel);

             isMovimento0 = 0;
         }*///Devido ao delay, essa fun??o n?o consegue ser imprimida.

         //delay_ms(5000);
        
        //Limpador frontral 
         if (isParabrisaF){
              lcd_gotoxy(0,0);
              sprintf(painel1,"LF 1");
              lcd_clear();
              lcd_puts(painel1);
         }
         else{
            lcd_gotoxy(0,0);
            sprintf(painel1,"LF 0");  
            lcd_clear();
            lcd_puts(painel1);
         }
         //Limpador traseiro
         if (isParabrisaT){
              lcd_gotoxy(5,0);
              sprintf(painel1,"LT 1");
              //lcd_clear();
              lcd_puts(painel1);
         }
         else{
              lcd_gotoxy(5,0);
              sprintf(painel1,"LT 0");
              //lcd_clear();
              lcd_puts(painel1);
         }
//         // porta esquerda
         if (isPortaE){
              lcd_gotoxy(0,1);
              sprintf(painel2,"PE A");
              //lcd_clear();
              lcd_puts(painel2);
         }
         else{
              lcd_gotoxy(0,1);
              sprintf(painel2,"PE F");
              //lcd_clear();
              lcd_puts(painel2);
         }
         // porta direita
         if (isPortaD){
              lcd_gotoxy(5,1);
              sprintf(painel2,"PD A"); 
              //lcd_clear();
              lcd_puts(painel2);
         }
         else{
              lcd_gotoxy(5,1);
              sprintf(painel2,"PD F");
              //lcd_clear();
              lcd_puts(painel2);
         }
         //Janela
         if (isJanelaD){
              lcd_gotoxy(10,0);
              sprintf(painel2,"JD A"); 
              //lcd_clear();
              lcd_puts(painel2);
         }
         else{
              lcd_gotoxy(10,0);
              sprintf(painel2,"JD F");
              //lcd_clear();
              lcd_puts(painel2);
         }
         if (isJanelaE){
              lcd_gotoxy(10,1);
              sprintf(painel2,"JE A"); 
              //lcd_clear();
              lcd_puts(painel2);
         }
         else{
              lcd_gotoxy(10,1);
              sprintf(painel2,"JE F");
              //lcd_clear();
              lcd_puts(painel2);
         }
         if(combustivel >=1000){
              lcd_gotoxy(14,1);
              sprintf(painel2," |"); 
              //lcd_clear();
              lcd_puts(painel2);
         }
         else{
              if(combustivel <= 1000){
                  lcd_gotoxy(14,1);
                  sprintf(painel2," i");
                  //lcd_clear();
                  lcd_puts(painel2);}
              
              if(combustivel == 0){ 
                  lcd_gotoxy(14,1);
                  sprintf(painel2," o");
                  //lcd_clear();
                  lcd_puts(painel2);
              }
         } 
                                 
         //printf("%d", isConsumindoCombustivel);

         // CONSUMINDO COMBUSTIVEL AO USAR O LIMPADOR
         if (isConsumindoCombustivel) {
             diminuiCombustivel();
         }
         
         delay_ms(5000);
     }
 }