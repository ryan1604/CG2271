#include "basic.h"
#include "audio.h"

// Music
#define A4 440
#define Bflat4 466
#define B4 494
#define C5 523
#define Csharp5 554
#define D5 587
#define Dsharp5 622
#define E5 659
#define F5 698
#define Fsharp5 740
#define G5 784
#define Aflat5 831
#define A5 880
#define Bflat5 932
#define B5 988
#define C6 1047

#define semi_note 250
#define one_note 500
#define two_note 1000

/* init PWM*/
void initPWM(void) {
	// Enable Clock to PortA
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	// Configure MUX to enable PWM for PortA
	PORTA->PCR[12] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[12] |= PORT_PCR_MUX(3);
	
	//PORTB->PCR[PTB1_Pin] &= ~PORT_PCR_MUX_MASK;
	//PORTB->PCR[PTB1_Pin] |= PORT_PCR_MUX(3);
	
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

	TPM1->MOD = 7499; // 50hz
	
	TPM1->SC &= ~(TPM_SC_CMOD_MASK | TPM_SC_PS_MASK);
	TPM1->SC |= TPM_SC_CMOD(1) | TPM_SC_PS(7);
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM1_C0SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM1_C0SC |= TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1);
	
	TPM1_C0V = 3750; // Set the channel value for a 50% duty cycle
}

void setFrequency(uint32_t frequency) {
	// Assuming a 48MHz clock and a prescaler of 128
	uint32_t mod = (48000000 / (frequency * 128)) - 1;
	TPM1->MOD = mod;

	// Set duty cycle to 50%
	TPM1_C0V = mod / 2;
	
	TPM1->SC |= TPM_SC_CMOD(1); // Re-enable the clock to update the counter
}

void playSong () {
	setFrequency(E5);
	osDelay(one_note);
	if (isComplete) return;
	setFrequency(E5);
	osDelay(one_note);
	setFrequency(E5);
	osDelay(two_note);
	if (isComplete) return;
	
	setFrequency(E5);
	osDelay(one_note);
	if (isComplete) return;
	setFrequency(E5);
	osDelay(one_note);
	setFrequency(E5);
	osDelay(two_note);
	if (isComplete) return;
	
	setFrequency(E5);
	osDelay(one_note);
	setFrequency(G5);
	osDelay(one_note);
	if (isComplete) return;
	setFrequency(C5);
	osDelay(one_note);
	setFrequency(D5);
	osDelay(one_note);
	if (isComplete) return;
	setFrequency(E5);
	osDelay(two_note * 2);
	if (isComplete) return;
	
	setFrequency(F5);
	osDelay(one_note);
	setFrequency(F5);
	osDelay(one_note);
	if (isComplete) return;
	setFrequency(F5);
	osDelay(one_note);
	setFrequency(F5);
	osDelay(one_note);
	if (isComplete) return;
	
	setFrequency(F5);
	osDelay(one_note);
	setFrequency(E5);
	osDelay(one_note);
	if (isComplete) return;
	setFrequency(E5);
	osDelay(one_note);
	setFrequency(E5);
	osDelay(semi_note);
	setFrequency(E5);
	osDelay(semi_note);
	if (isComplete) return;
	
	setFrequency(G5);
	osDelay(one_note);
	setFrequency(G5);
	osDelay(one_note);
	if (isComplete) return;
	setFrequency(F5);
	osDelay(one_note);
	setFrequency(D5);
	osDelay(one_note);
	if (isComplete) return;
	
	setFrequency(C5);
	osDelay(two_note * 2);
}

void playCelebrationSong () {
	setFrequency(E5);
	osDelay(one_note);
	//setFrequency(B5);
	//osDelay(one_note);
	setFrequency(B5);
	osDelay(one_note);
	setFrequency(A5);
	osDelay(semi_note);
	setFrequency(B5);
	osDelay(semi_note);
	setFrequency(C6);
	osDelay(one_note);
	setFrequency(C6);
	osDelay(semi_note);
	setFrequency(B5);
	osDelay(one_note);
	setFrequency(G5);
	osDelay(semi_note);
	setFrequency(G5);
	osDelay(one_note);

	setFrequency(A5);
	osDelay(one_note);
	setFrequency(A5);
	osDelay(one_note);
	setFrequency(A5);
	osDelay(semi_note);
	setFrequency(G5);
	osDelay(semi_note * 3);
	setFrequency(E5);
	osDelay(one_note);
	setFrequency(E5);
	osDelay(semi_note);
	setFrequency(E5);
	osDelay(semi_note);
	setFrequency(E5);
	osDelay(semi_note);
	setFrequency(D5);
	osDelay(semi_note * 3);

	setFrequency(E5);
	osDelay(one_note);
	//setFrequency(B5);
	//osDelay(one_note);
	setFrequency(B5);
	osDelay(one_note);
	setFrequency(A5);
	osDelay(semi_note);
	setFrequency(B5);
	osDelay(semi_note);
	setFrequency(C6);
	osDelay(one_note);
	setFrequency(C6);
	osDelay(semi_note);
	setFrequency(B5);
	osDelay(one_note);
	setFrequency(G5);
	osDelay(semi_note);
	setFrequency(G5);
	osDelay(one_note);
	
	setFrequency(A5);
	osDelay(one_note);
	setFrequency(A5);
	osDelay(one_note);
	setFrequency(A5);
	osDelay(semi_note);
	setFrequency(G5);
	osDelay(semi_note * 3);
	setFrequency(E5);
	osDelay(one_note * 2);
	setFrequency(E5);
	osDelay(one_note * 2);
}
