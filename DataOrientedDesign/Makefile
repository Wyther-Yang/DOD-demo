vpath %.h include
vpath %.cpp src
vpath %.o lib
vpath %.a lib

cc := g++ -Wall -Os
std := -std=c++17
pwd = $(shell pwd)
units := random vector2D
include = -I $(pwd)/include
debug := 


unit :=
unit-obj = lib/$(unit).o
unit-code = src/unit_$(unit).cpp

objs := random.o vector2D.o DOD_car.o simulation.o

phony += all
all: simulation

phony += test
test: $(unit).o
	$(cc) $(std) $(include) -o $(unit) $(unit-code) $(unit-obj)


phony += clearunit	
clearunit: 
	rm -f $(units) 
	cd lib && rm -f $(addsuffix .o,$(units))

phony += clear
clear:
	@rm -f simulation lib/*

simulation: main.cpp locallib.a
	@echo cc -o simulation $^
	@$(cc) $(std) $(include) $(debug) -o bin/$@ $< $(addprefix lib/,locallib.a)

locallib.a: $(objs)
	@echo ar -o locallib.a $^
	@ar -r lib/locallib.a $(addprefix lib/,$^) 2>/dev/null
	@rm -f $(addprefix lib/,$^)


%.o: %.cpp
	@echo cc -o $@ $^
	@$(cc) $(std) $(include) $(debug) -c -o $(pwd)/lib/$@ $^


