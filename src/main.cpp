/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"

int how_to_save_a_life = 0;
			

int main(void)
{


	//---------Configure PLL 168MHz as clock source-------------
		//SET FLASH MEMORY LATENCY AND ENABLE PREFETCH
			FLASH->ACR &= ~FLASH_ACR_LATENCY;
			FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
			FLASH->ACR |= FLASH_ACR_PRFTEN;

			//Enable HSI
			RCC->CR |= RCC_CR_HSION;
			//check if HSI is ready
			while(!(RCC->CR & (1<<1))){}
			//set PLL SOURCE to HSI
			RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;
			//set Division factor for the main PLL division clock to 8
			RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
			RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3;
			//set main PLL multiplication factor to 168
			RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
			RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3;
			RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_5;
			RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_7;
			//set PLL division factor for main system clock to 2
			RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;

			//Set APB1 clock frequency to 42MHz(prescaler of 4)
			RCC->CFGR &= ~RCC_CFGR_PPRE1;
			RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
			//Set APB2 clock frequency to 84MHz(prescaler of 2)
			RCC->CFGR &= ~RCC_CFGR_PPRE2;
			RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
			//Enable PLL
			RCC->CR |= RCC_CR_PLLON;
			//check if PLL is ready
			while(!(RCC->CR & (1<<25))){}
			//Select PLL as system clock
			RCC->CFGR |= RCC_CFGR_SW_PLL;
			//check to confirm PLL being used
			while(!(RCC->CFGR & RCC_CFGR_SWS_PLL )){}

		//--------------------------------------------------

	//Enable timer 1 RCC
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	//Enable output port RCC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//Set alternate function mode PA8
	GPIOA->MODER |= GPIO_MODER_MODER8_1;
	//set the specific alternate function
	GPIOA->AFR[1] |= GPIO_AF_TIM1;

	//Set prescaler
	TIM1->PSC = 10;
	//Set ARR
	TIM1->ARR = 1000;
	//Set duty cycle
	TIM1->CCR1 = 500;

	//Set the output compare mode to PWM Mode 1
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0;
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2;

	//Set output compare preload enable
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;

	//Enable capture/compare output
	TIM1->CCER |= TIM_CCER_CC1E;

	//set main Output Enable
	TIM1->BDTR |= TIM_BDTR_MOE;

	//Enable the UG bit to update preload register
	TIM1->EGR |= TIM_EGR_UG;


	//Enable timer 1
	TIM1->CR1 |= TIM_CR1_CEN;











	while(1){

	}
}
