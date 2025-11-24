#include <stdint.h>
#include "stm32f1xx_hal.h"  // CubeMX 自动生成
#include "tim.h"
#include "IC.h"



TIM_HandleTypeDef htim2;

/* 原函数：void IC_Init(void) */
void IC_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();      // 开启 TIM2 时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();     // 开启 GPIOA 时钟

    /* GPIO 初始化：PA0 上拉输入（TIM2_CH1） */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin       = GPIO_PIN_0;
    GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;          // HAL 里输入捕获使用 AF PP 或纯 INPUT 都可以
    GPIO_InitStruct.Pull      = GPIO_PULLUP;              // 上拉输入
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM2 基础配置 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler         = 7200 - 1;              // PSC = 7199
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.Period            = 65536 - 1;             // ARR = 65535（32位定时器可更大，这里保持原样）
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.RepetitionCounter = 0;
    HAL_TIM_Base_Init(&htim2);

    /* 输入捕获通道1 配置（对应 TIM2_CH1 → PA0） */
    TIM_IC_InitTypeDef IC_Config = {0};
    IC_Config.ICPolarity  = TIM_INPUTCHANNELPOLARITY_RISING;   // 上升沿捕获
    IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;          // 直通 TI1
    IC_Config.ICPrescaler = TIM_ICPSC_DIV1;                    // 不分频
    IC_Config.ICFilter    = 0xF;                               // 滤波器最大值，抗抖动
    HAL_TIM_IC_ConfigChannel(&htim2, &IC_Config, TIM_CHANNEL_1);

    /* 关键：选择 TI1FP1 作为触发源 + 从模式复位（上升沿到来时 CNT 自动归零） */
    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
    sSlaveConfig.SlaveMode    = TIM_SLAVEMODE_RESET;
    sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
    HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig);

    /* 启动输入捕获 + 同时启动基础定时器 */
    HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_1);
    // 如果你想用中断方式捕获，可改为 HAL_TIM_IC_Start_IT()
}

/**
  * 函数：获取输入捕获的频率（返回值为 10000*60 / 周期 ≈ RPM）
  * 原标准库：return 10000*60 / TIM_GetCapture1(TIM2);
  */
uint32_t IC_GetFreq(void)
{
    uint32_t ccr1_value = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_1);
    // 当计数器被复位时，CCR1 里保存的就是一个完整周期的计数值
    // 定时器时基频率 = 72MHz / 7200 = 10kHz → 周期 100us
    if(ccr1_value == 0) return 0;           // 防止除0
    return 10000UL * 60UL / ccr1_value;     // 与原代码完全等效
}

