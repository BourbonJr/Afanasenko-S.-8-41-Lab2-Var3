#include "../Inc/init.h"

void GPIO_Init(void)
{
    RCC_AHB1ENR |= RCC_GPIOB_EN | RCC_GPIOC_EN;

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE14_0);
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT14);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR14_0);
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR14_0);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE0_0);
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT0);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR0_0);
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR0_0);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE7_0);
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT7);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR7_0);
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR7_0);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR7);

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE12_0);
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT12);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR12_0);
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR12_0);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR12);

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE13_0);
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT13);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR13_0);
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR13_0);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR13);

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE15_0);
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT15);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR15_0);
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR15_0);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR15);

    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER9_1);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEED9_Msk);
    MODIFY_REG(GPIOC->AFR[1], GPIO_AFRH_AFSEL9_Msk, 0x0);
}

void RCC_Init(void)
{
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U);
    CLEAR_REG(RCC->CFGR);
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

    SET_BIT(RCC->CR, RCC_CR_HSEON);
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
    SET_BIT(RCC->CR, RCC_CR_CSSON);

    CLEAR_REG(RCC->PLLCFGR);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, RCC_PLLCFGR_PLLM_2);
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, RCC_PLLCFGR_PLLN_2 | RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_7);
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk);
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY));

    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO2PRE, RCC_CFGR_MCO2PRE_Msk);
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);

    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_5WS);
}

void ITR_Init(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
    NVIC_SetPriorityGrouping(0);

    MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_Msk, SYSCFG_EXTICR4_EXTI13_PC);
    SET_BIT(EXTI->IMR, EXTI_IMR_MR13);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13);
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR13);
    NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    MODIFY_REG(SYSCFG->EXTICR[1], SYSCFG_EXTICR2_EXTI6_Msk, SYSCFG_EXTICR2_EXTI6_PC);
    SET_BIT(EXTI->IMR, EXTI_IMR_MR6);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR6);
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR6);
    NVIC_SetPriority(EXTI9_5_IRQn , NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void SysTick_Init(void)
{
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
    MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk, SYSTLOAD << SysTick_LOAD_RELOAD_Pos);
    MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk, SYSTLOAD << SysTick_VAL_CURRENT_Pos);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
}