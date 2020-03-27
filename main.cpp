#include "stack-vm.h"

int main(){
	Stack_vm vm;
	std::vector<i32> prog{3, 4, 0x40000001, 5, 0x40000002, 3, 0x40000003, 2, 0x40000004, 0x40000000};
	vm.load_progrm(prog);
	vm.run();
	return 0;
}