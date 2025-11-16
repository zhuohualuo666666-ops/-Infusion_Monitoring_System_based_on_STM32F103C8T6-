#include "dwt_delay.h"
#include "stm32f1xx.h"         // 确保 SystemCoreClock 可用
#include "core_cm3.h"

static volatile uint32_t dwt_inited = 0;

void DWT_Init(void)
{
    if (dwt_inited) return;

    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // 使能 Trace
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;             // 使能 CYCCNT
    DWT->CYCCNT = 0;                                 // 清零
    __DSB();                                         // 同步
    dwt_inited = 1;
}

void Delay_us(uint32_t us)
{
    if (us == 0) return;
    if (!dwt_inited) DWT_Init();

    uint32_t start = DWT->CYCCNT;
    uint32_t cycles = us * (SystemCoreClock / 1000000UL);

    uint32_t now = DWT->CYCCNT;
    while ((now - start) < cycles) {
        now = DWT->CYCCNT;  // 关键：溢出安全
    }
}

/**
 * @brief  毫秒级延时（替代 HAL_Delay，更快）
 * @param  ms: 延时毫秒数
 */
void Delay_ms(uint32_t ms)
{
    Delay_us(ms * 1000);
}

