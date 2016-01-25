#include "yla_vm.h"
#include "yla_stack.h"

#define TYPE_SET 54545

#ifndef YLA_SET_H_
#define YLA_SET_H_

int yla_vm_stack_push_set(yla_vm *vm);
int yla_vm_stack_set_add(yla_vm *vm, yla_int_type *value);
int yla_vm_stack_set_check_exist(yla_vm *vm, yla_int_type *value);
int yla_vm_stack_set_intersection(yla_vm *vm);
int yla_vm_stack_set_sum(yla_vm *vm);

#endif /* YLA_SET_H_ */