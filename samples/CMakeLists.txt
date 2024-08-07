# SPDX-FileCopyrightText: 2021 The IREE bare-metal Arm Authors
#
# Licensed under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

if(BUILD_WITH_CMSIS)
  if(ARM_TARGET STREQUAL "NRF52840")
    set(CONDITIONAL_DEP nrfx_nrf52840)
  elseif(ARM_TARGET STREQUAL "NRF5340")
    set(CONDITIONAL_DEP nrfx_nrf5340)
  elseif(ARM_TARGET STREQUAL "STM32F407" OR ARM_TARGET STREQUAL "STM32F4XX")
    set(CONDITIONAL_DEP cmsis_device_f407xx)
  elseif(ARM_TARGET STREQUAL "STM32F411XE")
    set(CONDITIONAL_DEP cmsis_device_f411xe)
  elseif(ARM_TARGET STREQUAL "STM32F446")
    set(CONDITIONAL_DEP cmsis_device_f446xx)
  elseif(ARM_TARGET STREQUAL "STM32F746")
    set(CONDITIONAL_DEP cmsis_device_f746xx)
  elseif(ARM_TARGET STREQUAL "STM32L4R5")
    set(CONDITIONAL_DEP cmsis_device_l4r5xx)
  elseif(ARM_TARGET STREQUAL "STM32L476")
    set(CONDITIONAL_DEP cmsis_device_l476xx)
  elseif(ARM_TARGET STREQUAL "CORSTONE-300")
    set(CONDITIONAL_DEP ethos_u_core_platform_corstone-300)
  endif()
elseif(BUILD_WITH_LIBOPENCM3)
  set(CONDITIONAL_DEP stm32f4)
endif()

add_library(firmware ALIAS ${CONDITIONAL_DEP})

if(EXISTS ${IREE_HOST_BIN_DIR}/iree-compile)
  # Use `iree-compile` if installed to IREE_HOST_BIN_DIR.
  set(_COMPILE_TOOL_EXECUTABLE ${IREE_HOST_BIN_DIR}/iree-compile)
else()
  # Use `iree-compile` provided via a snapshot.
  find_program(_COMPILE_TOOL_EXECUTABLE iree-compile)
  if(_COMPILE_TOOL_EXECUTABLE STREQUAL _COMPILE_TOOL_EXECUTABLE-NOTFOUND)
    message(FATAL_ERROR "Could not find iree-compile.")
  endif()
endif()

add_subdirectory(simple_embedding)
add_subdirectory(simple_vec_mul)
add_subdirectory(static_library)
add_subdirectory(vision_inference)
