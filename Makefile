vpath %.h include
vpath %.cpp src
vpath %.o lib
vpath %.a lib

cc := g++ -Wall -Os
std := -std=c++17
pwd = $(shell pwd)
units := random vector2D
include = -I $(pwd)/include
lib = -L $(pwd)/lib
dependency := depends.d
debug := 


unit :=
unit-obj = lib/$(unit).o
unit-code = src/unit_$(unit).cpp

objs := random.o vector2D.o DOD_car.o simulation.o

ifneq "$(MAKECMDGOALS)" "clear"
	-include $(dependency)
endif

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
	@rm -f bin/simulation lib/* $(dependency)

simulation: main.cpp liblocal.a
	@echo cc -o simulation 
	@$(cc) $(std) $(include) $(debug) $(lib) $< -llocal  -o bin/$@

liblocal.a: $(objs)
	@echo ar -o liblocal.a $^
	@ar -r lib/liblocal.a $(addprefix lib/,$^) 2>/dev/null
	@rm -f $(addprefix lib/,$^)

%.o: %.cpp
	@echo cc -c -o $@ 
	@$(cc) $(std) $(include) $(debug) -c -o $(pwd)/lib/$@ \
	$(filter %.cpp,$^)

%.d: 
	@echo "all:">$(dependency)
	@echo cc -m $@
	@$(cc) $(include) -MM $(addprefix src/,$(subst .o,.cpp,$(objs))) 1>>$(dependency)