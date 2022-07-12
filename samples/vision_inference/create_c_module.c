// Copyright 2021 The IREE Authors
// Copyright 2022 Fraunhofer-Gesellschaft zur Förderung der angewandten
//                Forschung e.V.
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#include <stdio.h>

#include "mnist_emitc.h"

// A function to create the C module.
iree_status_t create_module(iree_vm_module_t** module) {
  return module_create(iree_allocator_system(), module);
}

void print_success() { printf("mnist_static_library_run_c passed\n"); }
