
## Tutorial 

Integrate Python function in systemverilog testbench

---

#### 1. Find in your system python

	find /usr/ -name "Python.h" 2>/dev/null 
    

In my case

	~/python_in_systemverilog$  find /usr/ -name "Python.h" 2>/dev/null 
	/usr/include/python3.10/Python.h

If  you don't have python in your PC

####  [Download Python](https://www.python.org/downloads/)

---

#### 2. Find in your system libpython3.*.so.1

    find /usr/ -name "libpython3.*" 2>/dev/null

In my case 

	~/python_in_systemverilog$  find /usr/ -name "libpython3.*" 2>/dev/null

	/usr/lib/x86_64-linux-gnu/libpython3.10.so.1

---

#### 3. Add Path and libpython3.*.so.1 in Makefile

	test: clean
	gcc -fPIC c_code.c -I/usr/include/python3.10/ /usr/lib/x86_64-linux-gnu/libpython3.10.so.1 -o test

	compile: clean
	gcc -c -fPIC c_code.c -I/usr/include/python3.10/ -o c_code.o

	create_dynamic_lib: compile
	ld -G -o c_code.so c_code.o /usr/lib/x86_64-linux-gnu/libpython3.10.so.1

---

#### 4. Run project

	make test

result

	~/python_in_systemverilog$  make test 
	rm -rf c_code.so c_code.o __pycache__ xcelium.d xrun.history xrun.log .bpad test
	gcc -fPIC c_code.c -I/usr/include/python3.10/ /usr/lib/x86_64-linux-gnu/libpython3.10.so.1 -o test
	./test
	Hello in main! 
	Call py_func! 
	Let's give this a shot! x = 10
	You passed this Python program  Python_Function  from C, from system verilog! x =  10
	Result is 10


or
		
	make all

result 

	~/python_in_systemverilog$  make all
	rm -rf c_code.so c_code.o __pycache__ xcelium.d xrun.history xrun.log .bpad test
	gcc -c -fPIC c_code.c -I/usr/include/python3.10/ -o c_code.o
	ld -G -o c_code.so c_code.o /usr/lib/x86_64-linux-gnu/libpython3.10.so.1
	xrun -64bit -disable_sem2009 -sv_lib c_code.so ./testbench.sv
	TOOL:   xrun(64)        19.09-s004: Started on Aug 04, 2022 at 23:04:38 MSK
	xrun(64): 19.09-s004: (c) Copyright 1995-2019 Cadence Design Systems, Inc.
	file: ./testbench.sv
			module worklib.sv_top:sv
					errors: 0, warnings: 0
					Caching library 'worklib' ....... Done
			Elaborating the design hierarchy:
			Top level design units:
					$unit_0x4ccdf83b
					sv_top
			Building instance overlay tables: .................... Done
			Generating native compiled code:
					worklib.sv_top:sv <0x4e1d7216>
							streams:   1, words:  2127
					worklib.\$unit_0x4ccdf83b :compilation_unit <0x5405ff0c>
							streams:   0, words:     0
			Building instance specific data structures.
			Loading native compiled code:     .................... Done
			Design hierarchy summary:
								Instances  Unique
					Modules:            1       1
					Registers:          2       -
					Initial blocks:     1       1
					Compilation units:  1       1
			Writing initial simulation snapshot: worklib.sv_top:sv
	Loading snapshot worklib.sv_top:sv .................... Done
	xcelium> run
	Let's give this a shot! x = 5
	You passed this Python program  Python_Function  from C, from system verilog! x =  5
	Result is 5
	Let's give this a shot! x = 15
	You passed this Python program  Python_Function  from C, from system verilog! x =  15
	Result is 15
	Let's give this a shot! x = 52
	You passed this Python program  Python_Function  from C, from system verilog! x =  52
	Result is 52
	Let's give this a shot! x = 56
	You passed this Python program  Python_Function  from C, from system verilog! x =  56
	Result is 56
	Let's give this a shot! x = 75
	You passed this Python program  Python_Function  from C, from system verilog! x =  75
	Result is 75
	xmsim: *W,RNQUIE: Simulation is complete.
	xcelium> exit
	TOOL:   xrun(64)        19.09-s004: Exiting on Aug 04, 2022 at 23:04:39 MSK  (total: 00:00:01)

---
