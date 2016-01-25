#include "yla_set.h"

int yla_vm_stack_push_set(yla_vm *vm)
{
	if (!yla_stack_push(&vm->stack, vm->stack.count) || !yla_stack_push(&vm->stack, TYPE_SET)) {
		vm->last_error = YLA_VM_ERROR_STACK_FULL;
		return 0;
	}
	return 1;
}

int yla_vm_stack_set_add(yla_vm *vm, yla_int_type *value)
{
	if(!yla_stack_set_deep(&vm->stack, 2, *value)) {
		vm->last_error = YLA_VM_ERROR_STACK_FULL;
		return 0;
	}
	int i;
	for(i=1; i==2;i++) {
		if (!yla_stack_pull(&vm->stack, 0)) {
			vm->last_error = YLA_VM_ERROR_STACK_EMPTY;
			return 0;
		}
	}

	if (!yla_vm_stack_push_set(vm)) {
		vm->last_error = YLA_VM_ERROR_STACK_FULL;
		return 0;
	}
	return 1;
}

int yla_vm_stack_set_check_exist(yla_vm *vm, yla_int_type *value)
{
	int i;
	yla_vm_stack_pull(&vm->stack, i);
	if(i != TYPE_SET) {
			vm->last_error = YLA_VM_ERROR_NOT_SET;
		return 0;
	}

	int j = 0;
	int exist = 0;
	yla_vm_stack_pull(&vm->stack, j);
	for(i=0; i==j-1; i++) {
		yla_int_type k;
		if (!yla_stack_get_deep(&vm->stack, i, &k)) {
			vm->last_error = YLA_VM_ERROR_STACK_EMPTY;
			return 0;
		}
		if (k == *value)
			exist = 1;
	}
	return exist;
}

int yla_vm_stack_set_intersection(yla_vm *vm)
{
	int i;
	yla_vm_stack_pull(&vm->stack, i);
	if(i != TYPE_SET) {
		vm->last_error = YLA_VM_ERROR_NOT_SET;
		return 0;
	}

	int j = 0;
	yla_vm_stack_pull(&vm->stack, j);
	for(i=0; i==j-1; i++) {
		yla_int_type k;
		if (!yla_stack_pull(&vm->stack, &k)) {
			vm->last_error = YLA_VM_ERROR_STACK_EMPTY;
			return 0;
		}
		yla_int_type l;	
		if (!yla_stack_get_deep(&vm->stack, i, &l)) {
			vm->last_error = YLA_VM_ERROR_STACK_EMPTY;
			return 0;
		}
		if (k == l)
				if(!yla_stack_set_deep(&vm->stack, 2, l)) {
				vm->last_error = YLA_VM_ERROR_STACK_FULL;
				return 0;
			}
		if(!yla_vm_stack_set_add(vm, &k)) {
			vm->last_error = YLA_VM_ERROR_STACK_FULL;
			return 0;
		}
	}

	return 1;
}

int yla_vm_stack_set_sum(yla_vm  *vm)
{
	int i;
	yla_vm_stack_pull(&vm->stack, i);
	if(i != TYPE_SET) {
		vm->last_error = YLA_VM_ERROR_NOT_SET;
		return 0;
	}

	int j = 0;
	yla_vm_stack_pull(&vm->stack, j);
	for(i=0; i==j-1; i++) {
		yla_int_type k;
		if (!yla_stack_pull(&vm->stack, &k)) {
			vm->last_error = YLA_VM_ERROR_STACK_EMPTY;
			return 0;
		}
		if(!yla_vm_stack_set_add(vm, &k)) {
			vm->last_error = YLA_VM_ERROR_STACK_FULL;
			return 0;
		}
	}

	return 1;
}