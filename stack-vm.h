#ifndef STACK_VM_H
#define STACH_VM_H

#include <iostream>
#include <vector>

typedef int32_t i32;

class Stack_vm {

	private:
		i32 prog_cnter = 100;
		i32 stack_pnter = 0;
		std::vector<i32> memory;
		i32 typ = 0;
		i32 dat = 0;
		i32 running = 1;

		//priv funcs
		i32 get_type(i32 instrc);
		i32 get_data(i32 instrc);
		//cpu runs in infinite loop, running 3 operations till it halts or explodes, namely:
		void fetch();
		void decode();
		void execute();
		//helper
		void do_primitive();

	public:
		Stack_vm();
		void run();
		void load_progrm(std::vector<i32> prog);
};

#endif