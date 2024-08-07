# SPDX-FileCopyrightText: 2022 The IREE bare-metal Arm Authors
#
# Licensed under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set(nrfx_DIR "${iree-bare-metal-arm_SOURCE_DIR}/third_party/nrfx/")
set(nrfx_custom_DIR "${iree-bare-metal-arm_SOURCE_DIR}/third_party/nrfx-custom/")
set(CMSIS_5_SOURCE_DIR "${iree-bare-metal-arm_SOURCE_DIR}/third_party/CMSIS_5/")

#-------------------------------------------------------------------------------
# nRF52840
#-------------------------------------------------------------------------------

add_library(nrfx_nrf52840 STATIC "")

target_sources(nrfx_nrf52840
  PRIVATE
    ${nrfx_DIR}/mdk/system_nrf52840.c
    ${nrfx_custom_DIR}/gcc_startup_nrf52840.S
)

target_include_directories(nrfx_nrf52840
  PUBLIC
    ${CMSIS_5_SOURCE_DIR}/CMSIS/Core/Include/
  PRIVATE
    ${nrfx_DIR}/mdk/
)

target_compile_definitions(nrfx_nrf52840
  PUBLIC
    NRF52840_XXAA
)

# Allow ld to find generic linker script
target_link_directories(nrfx_nrf52840 INTERFACE "${nrfx_custom_DIR}")

#-------------------------------------------------------------------------------
# nRF5340
#-------------------------------------------------------------------------------

add_library(nrfx_nrf5340 STATIC "")

target_sources(nrfx_nrf5340
  PRIVATE
    ${nrfx_DIR}/mdk/system_nrf5340_application.c
    ${nrfx_custom_DIR}/gcc_startup_nrf5340_application.S
)

target_include_directories(nrfx_nrf5340
  PUBLIC
    ${CMSIS_5_SOURCE_DIR}/CMSIS/Core/Include/
  PRIVATE
    ${nrfx_DIR}/mdk/
)

target_compile_definitions(nrfx_nrf5340
  PUBLIC
    NRF5340_XXAA
    NRF5340_XXAA_APPLICATION
    NRF_APPLICATION
)

# Allow ld to find generic linker script
target_link_directories(nrfx_nrf5340 INTERFACE "${nrfx_custom_DIR}")

#-------------------------------------------------------------------------------
# nRF UART
#-------------------------------------------------------------------------------

add_library(nrfx_uart STATIC "")

target_sources(nrfx_uart
  PRIVATE
    ${nrfx_DIR}/drivers/src/nrfx_uart.c
)

target_include_directories(nrfx_uart
  PUBLIC
    ${nrfx_DIR}
    ${nrfx_DIR}/drivers/include/
    ${nrfx_DIR}/hal/
    ${nrfx_DIR}/templates/
    ${nrfx_DIR}/mdk/
)

if(USE_UART0)
  target_compile_definitions(nrfx_uart
    PUBLIC
      NRFX_UART_ENABLED
      NRFX_UART0_ENABLED
  )
endif()

if(ARM_TARGET STREQUAL "NRF52840")
  target_link_libraries(nrfx_uart
    PRIVATE
      nrfx_nrf52840
  )
endif()

#-------------------------------------------------------------------------------
# nRF UARTE
#-------------------------------------------------------------------------------

add_library(nrfx_uarte STATIC "")

target_sources(nrfx_uarte
  PRIVATE
    ${nrfx_DIR}/drivers/src/nrfx_uarte.c
    ${nrfx_DIR}/soc/nrfx_atomic.c
)

target_include_directories(nrfx_uarte
  PUBLIC
    ${nrfx_custom_DIR}
    ${nrfx_DIR}
    ${nrfx_DIR}/drivers/include/
    ${nrfx_DIR}/hal/
    ${nrfx_DIR}/mdk/
    ${nrfx_DIR}/soc/
)

if(USE_UART0)
  target_compile_definitions(nrfx_uarte
    PUBLIC
      NRFX_UARTE_ENABLED
      NRFX_UARTE0_ENABLED
  )
endif()

if(ARM_TARGET STREQUAL "NRF5340")
  target_link_libraries(nrfx_uarte
  PRIVATE
    nrfx_nrf5340
)
endif()
