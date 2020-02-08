
/*	IVAN CORTES
 * 	DATE: 2020-02-06
 * 	CLASS: ECE5721
 * 	LAB2: 7 SEGMENT DISPLAY
*/

// INCLUDE
#include <MKL25Z4.h>
/*******************************************************************************
 * DEFINITIONS
 ******************************************************************************/
#define Segment_a (0)
#define Segment_b (1)
#define Segment_c (2)
#define Segment_d (3)
#define Segment_e (4)
#define Segment_f (5)
#define Segment_g (6)
#define Segment_dot (7)
#define MASK(x)  (1UL << (x))
/*******************************************************************************
 * CODE
 ******************************************************************************/
// delay(ms) -- Spin wait delay (in ms)
//              Note:  uses low power timer (LPTMR)
void delay(unsigned int length_ms)
{
    SIM->SCGC5 |= SIM_SCGC5_LPTMR_MASK;  // Make sure clock is enabled
    LPTMR0->CSR = 0;                     // Reset LPTMR settings
    LPTMR0->CMR = length_ms;             // Set compare value (in ms)

    // Use 1kHz LPO with no prescaler
    LPTMR0->PSR = LPTMR_PSR_PCS(1) | LPTMR_PSR_PBYP_MASK;

    // Start the timer and wait for it to reach the compare value
    LPTMR0->CSR = LPTMR_CSR_TEN_MASK;
    while (!(LPTMR0->CSR & LPTMR_CSR_TCF_MASK))
        ;

    LPTMR0->CSR = 0;                     // Turn off timer
}

void SevenSegment(uint8_t count,uint8_t dp, uint8_t dec_hex)
{
/* This function shows value of count on display the decimal point is displayed if dp = 1
Note:
count must be less than 10 for decimal, or less than 16 for Hex. */
   //if(count <dec_hex)
   //{
      switch (count)
      {
         case 0:
        	 PTC->PDOR = 0x3F; 		//0 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 1:
        	 PTC->PDOR = 0x06;		//1 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 2:
         	 PTC->PDOR = 0x5B;		//2 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 3:
        	 PTC->PDOR = 0x4F;		//3 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 4:
        	 PTC->PDOR = 0x66;		//4 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 5:
        	 PTC->PDOR = 0x6D;		//5 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 6:
        	 PTC->PDOR = 0x7D;		//6 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 7:
        	 PTC->PDOR = 0x07;		//7 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 8:
        	 PTC->PDOR = 0x7F;		//8 in for h,g,f,e,d,c,b,a Cathode configuration
         break;

         case 9:
        	 PTC->PDOR = 0x6F;		//9 in for h,g,f,e,d,c,b,a Cathode configuration
         break;
		 //hex only
		 case 10:
			 PTC->PDOR = 0x77;		//A in for h,g,f,e,d,c,b,a Cathode configuration
         break;

		 case 11:
			 PTC->PDOR = 0x7C;		//b in for h,g,f,e,d,c,b,a Cathode configuration
         break;

		 case 12:
			 PTC->PDOR = 0x39;		//C in for h,g,f,e,d,c,b,a Cathode configuration
         break;

		 case 13:
			 PTC->PDOR = 0x5E;		//d in for h,g,f,e,d,c,b,a Cathode configuration
         break;

		 case 14:
			 PTC->PDOR = 0x79;		//E in for h,g,f,e,d,c,b,a Cathode configuration
         break;

		 case 15:
			 PTC->PDOR = 0x71;		//F in for h,g,f,e,d,c,b,a Cathode configuration
         break;
      }
      //if(dp)
      //{
         //if decimal point should be displayed make DP bit Low
         //PORT_7_SEGMENT&=0b11110111;
    	//  PTC->PSOR = MASK(Segment_dot);
      //}
   }
   //else
   //{
      //This symbol on display shows that count was greater than 9 or 15
      //so display can't handle it

      //PORT_7_SEGMENT=0b11011111;
	 // PTC->PSOR = MASK(Segment_dot);
   //}
//}

int main(void)
{
	   int count=0;
	   int dec_hex=16; //change to 10 for decimal

			// Enable Clock to port A
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTB_MASK;
			// Make GPIO
			PORTC->PCR[Segment_a] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[Segment_a] |= PORT_PCR_MUX(1);
			PORTC->PCR[Segment_b] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[Segment_b] |= PORT_PCR_MUX(1);
			PORTC->PCR[Segment_c] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[Segment_c] |= PORT_PCR_MUX(1);
			PORTC->PCR[Segment_d] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[Segment_d] |= PORT_PCR_MUX(1);
			PORTC->PCR[Segment_e] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[Segment_e] |= PORT_PCR_MUX(1);
			PORTC->PCR[Segment_f] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[Segment_f] |= PORT_PCR_MUX(1);
			PORTC->PCR[Segment_g] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[Segment_g] |= PORT_PCR_MUX(1);
			PORTC->PCR[Segment_dot] &= ~PORT_PCR_MUX_MASK;
			PORTC->PCR[Segment_dot] |= PORT_PCR_MUX(1);
			PORTB->PCR[0] = ~PORT_PCR_MUX_MASK;
			PORTB->PCR[0] = PORT_PCR_MUX(1);
			PORTB->PCR[1] = ~PORT_PCR_MUX_MASK;
			PORTB->PCR[1] = PORT_PCR_MUX(1);
			PORTB->PCR[2] = ~PORT_PCR_MUX_MASK;
			PORTB->PCR[2] = PORT_PCR_MUX(1);
			PORTB->PCR[3] = ~PORT_PCR_MUX_MASK;
			PORTB->PCR[3] = PORT_PCR_MUX(1);
			// set LEDs bits to outputs
			PTC->PDDR |= MASK(Segment_a) | MASK(Segment_b)| MASK(Segment_c)| MASK(Segment_d)| MASK(Segment_e)| MASK(Segment_f)| MASK(Segment_g)| MASK(Segment_dot);
			PTB->PDDR = 0x00;
			while (1)
			{
				SevenSegment(count,0, dec_hex);
				delay(2000);
				if(PTB->PDIR == 0x00)
					{
					count = 0;
					}
					else if (PTB->PDIR == 0x01)
					{
					count = 1;
					}
					else if (PTB->PDIR == 0x02)
					{
					count = 2;
					}
					else if (PTB->PDIR == 0x03)
					{
					count = 3;
					}
					else if (PTB->PDIR == 0x04)
					{
					count = 4;
					}
					else if (PTB->PDIR == 0x05)
					{
					count = 5;
					}
					else if (PTB->PDIR == 0x06)
					{
					count = 6;
					}
					else if (PTB->PDIR == 0x07)
					{
					count = 7;
					}
					else if (PTB->PDIR == 0x08)
					{
					count = 8;
					}
					else if (PTB->PDIR == 0x09)
					{
					count = 9;
					}
					else if (PTB->PDIR == 0x0A)
					{
					count = 10;
					}
					else if (PTB->PDIR == 0x0B)
					{
					count = 11;
					}
					else if (PTB->PDIR == 0x0C)
					{
					count = 12;
					}
					else if (PTB->PDIR == 0x0D)
					{
					count = 13;
					}
					else if (PTB->PDIR == 0x0E)
					{
					count = 14;
					}
					else if (PTB->PDIR == 0x0F)
					{
					count = 15;
					}
			}
}
