#include "stack-vm.h"
//instruction format: header->2bit, body(data)->30bits
//header: 
//0 => pos int
//1 => primitive instrction
//2 => neg int
//3 => undefined

//implement funcs
Stack_vm::Stack_vm(){
	memory.reserve(1000000);
}

i32 Stack_vm::get_type(i32 instrc){
	i32 type = 0xc0000000; //essentially since everything is 32bit, every 2 characters is a byte 
	type = (type & instrc) >> 30; //every instruction has a 2bit header saying what sort of instruction it is
	return type;
}

i32 Stack_vm::get_data(i32 instrc){
	i32 data = 0x3fffffff;
	data = data & instrc;
	return data;
}

void Stack_vm::fetch(){
	prog_cnter++;
}

void Stack_vm::decode(){
	typ = get_type(memory[prog_cnter]);
	dat = get_data(memory[prog_cnter]);
}

void Stack_vm::execute(){
	if (typ == 0 || typ == 2){
		stack_pnter++;
		memory[stack_pnter] = dat;
	} else {
		do_primitive();
	}
}

void Stack_vm::do_primitive(){ //equivalent to cpu control mechanism
	switch(dat) { //instruction set 
		case 0: //halt
			std::cout << "halt" << std::endl;
			running = 0;
			break;

		case 1: //add
			std::cout << "add " << memory[stack_pnter- 1] << " " << memory[stack_pnter] << std::endl;
			memory[stack_pnter - 1] = memory[stack_pnter - 1] + memory[stack_pnter];
			stack_pnter--;
			break;

		case 2: //subtrct
			std::cout << "subtract " << memory[stack_pnter- 1] << " " << memory[stack_pnter] << std::endl;
			memory[stack_pnter - 1] = memory[stack_pnter - 1] - memory[stack_pnter];
			stack_pnter--;
			break;

		case 3: //multply
			std::cout << "multiply " << memory[stack_pnter- 1] << " " << memory[stack_pnter] << std::endl;
			memory[stack_pnter - 1] = memory[stack_pnter - 1] * memory[stack_pnter];
			stack_pnter--;
			break;

		case 4: //divsion
			std::cout << "divide " << memory[stack_pnter- 1] << " " << memory[stack_pnter] << std::endl;
			memory[stack_pnter - 1] = memory[stack_pnter - 1] / memory[stack_pnter];
			stack_pnter--;
			break;
	}
}

void Stack_vm::run(){
	prog_cnter -= 1;
	while (running == 1){
		fetch();
		decode();
		execute();
		std::cout << "t.o.s: " << memory[stack_pnter] << std::endl;
	}
}

void Stack_vm::load_progrm(std::vector<i32> prog){
	for (i32 i = 0; i < prog.size(); i++){
		memory[prog_cnter + i] = prog[i];
	}
}