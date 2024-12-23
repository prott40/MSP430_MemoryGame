#include <msp430.h>
#include <stdlib.h>

#define Start 0
#define Display 1
#define Read 2
#define Check 3
#define Win 4
#define Lose 5

volatile int state = Start;

volatile int goal[10];

volatile int guess[10];

volatile int current_goal = 0;

volatile int current_guess = 0;

volatile int numgoals = 0;

void generate(){
	
}

void Buttons(){
	P1DIR &= ~BIT1; //clears port 1
    P1REN |= BIT1;  //sets as pullup
    P1OUT |= BIT1;  //sets as input

    P1IFG &=~ BIT1; //clears port 1 flag
    P1IE |= BIT1;   //enables port 1 flag
	
	P1DIR &= ~BIT2; //clears port 2
    P1REN |= BIT2;  //sets as pullup
    P1OUT |= BIT2;  //sets as input

    P1IFG &=~ BIT2; //clears port 2 flag
    P1IE |= BIT2;   //enables port 2 flag
}

void BuzzerClock(){
	TB0CTL |= TBCLR;          // Clears clock value
    TB0CTL |= TBSSEL__SMCLK;   // Sets clock to 1MHz
    TB0CTL |= MC__UP;          // Sets to a pullup

    //TB0CCR0 &= ~0x0000;
    TB0CCR0 = 500000;// sets the pulse width
	TB0CCR1 = 0; // sets the active high
	TB0CCTL0 |= CCIE;// enables interrupt flags
	TB0CCTL1 |= CCIE;
	TB0CCTL0 &= ~CCIFG;
	TB0CCTL1 &= ~CCIFG;
}
void DisplayClock(){
	TA0CTL |= TACLR;          // Clears clock value
    TA0CTL |= TASSEL__SMCLK;   // Sets clock to 1MHz
    TA0CTL |= MC__UP;          // Sets to a pullup

    //TB0CCR0 &= ~0x0000;
    TA0CCR0 = 500000;
	TA0CCTL0 |= CCIE;// enables interrupt flags
	TA0CCTL0 &= ~CCIFG;
	
}
void main(){
	generate();
	
	
	while(1){
		switch(state){
			case Start:
				state = Display;
			break;
			case Dispaly:
			
			
			break;
			
		}
		
	}
	return 0;
	
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void ISR_TA0_Overflow(void)
{
    
    TA0CTL &= ~TAIFG; // Clear TA0 flag
}


#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
	if(state == Lose){
    P2OUT |= BIT1; // set this to pwm pin
    
	}
    TB0CCTL0 &= ~CCIFG;// clears interrupt flag

}
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR1(void)
{
    switch (__even_in_range(TB0IV, 14))
            {
                case TB0IV_TBCCR1:

if(state == Lose){
	
                    P2OUT &= ~BIT1;// cleares the pulse 
}
                    TB0CCTL1 &= ~CCIFG; resets theflag

                    break;
                

                // Add other cases for additional CCRs if needed
                default:
                    break;
            }
}

#pragma vector = PORT1_VECTOR
__interrupt void ISR_Switch_Overflow(void)
{
	
	
	
	
	P1IFG &=~ BIT1;        //clears the flag
    P1IFG &=~ BIT2;
}