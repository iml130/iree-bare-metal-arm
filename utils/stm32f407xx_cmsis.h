// Copyright 2022 The IREE bare-metal Arm Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "stm32f407xx.h"

// When using the PLL, the clock needs to be configured accordingly. Adjust
// these values to your needs.

#define FLASH_WAIT_STATES FLASH_ACR_LATENCY_5WS
#define AHB_PRESCALER RCC_CFGR_HPRE_DIV1
#define APB1_PRESCALER RCC_CFGR_PPRE1_DIV4
#define APB2_PRESCALER RCC_CFGR_PPRE2_DIV2
#if defined(USE_PLL_HSI_CLOCK)
#define PLL_M 8
#elif defined(USE_PLL_HSE_CLOCK)
#define PLL_M 4
#endif
#define PLL_N 168
#define PLL_P 0  // divides by 2
