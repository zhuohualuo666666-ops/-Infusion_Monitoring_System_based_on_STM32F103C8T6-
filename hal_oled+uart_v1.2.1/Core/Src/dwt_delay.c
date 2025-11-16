// dwt_delay.c
#include "dwt_delay.h"
#include "core_cm3.h"  // 关键：F103 用 cm3

static volatile uint32_t dwt_inited = 0;

/**
 * @brief  初始化 DWT 周期计数器（只需调用一次）
 */
void DWT_Init(void)
{
    if (dwt_inited) return;

    // 1. 使能 Trace 调试单元
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // 2. 使能 CYCCNT 计数器
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    // 3. 清零计数器
    DWT->CYCCNT = 0;

    dwt_inited = 1;
}

/**
 * @brief  微秒级延时（精度 ~13.9ns @72MHz）
 * @param  us: 延时微秒数
 */
void Delay_us(uint32_t us)
{
    if (!dwt_inited) DWT_Init();

    uint32_t start = DWT->CYCCNT;
    // SystemCoreClock 来自 CubeMX 自动更新（72MHz）
    uint32_t cycles = us * (SystemCoreClock / 1000000UL);
    while ((DWT->CYCCNT - start) < cycles);
}

/**
 * @brief  毫秒级延时（替代 HAL_Delay，更快）
 * @param  ms: 延时毫秒数
 */
void Delay_ms(uint32_t ms)
{
    Delay_us(ms * 1000);
}

