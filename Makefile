TOOL = xrun
TOOL_OPTS  = -64bit
TOOL_OPTS += -disable_sem2009
TOOL_OPTS += -sv_lib c_code.so

SOURCE_LIST = ./testbench.sv

all: run

clean:
	rm -rf c_code.so c_code.o __pycache__ xcelium.d xrun.history xrun.log .bpad test

compile: clean
	gcc -c -fPIC c_code.c -I/usr/include/python3.10/ -o c_code.o

create_dynamic_lib: compile
	ld -G -o c_code.so c_code.o /usr/lib/x86_64-linux-gnu/libpython3.10.so.1

run: create_dynamic_lib
	${TOOL} $(TOOL_OPTS) ${SOURCE_LIST}

test: clean
	gcc -fPIC c_code.c -I/usr/include/python3.10/ /usr/lib/x86_64-linux-gnu/libpython3.10.so.1 -o test
	./test

