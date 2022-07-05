vpath %.h include
vpath %.cpp src
vpath %.o lib
vpath %.a lib

# GCC args
cc := g++ -Wall -Os 
std := -std=c++17 -fPIC 
pwd = $(shell pwd)
units := random vector2D
include = -I $(pwd)/include
lib = -L $(pwd)/lib
dependency := depends.d
debug := 

# unit test name
unit :=
unit-obj = lib/$(unit).o
unit-code = src/unit_$(unit).cpp

objs := random.o vector2D.o DOD_car.o OOD_car.o simulation.o
macro := -D OOD

# lazing init of dependency
ifneq "$(MAKECMDGOALS)" "clear"
	-include $(dependency)
endif

# main target
phony += all
all: ood dod

phony += test
test: $(unit).o
	$(cc) $(std) $(include) -o $(unit) $(unit-code) $(unit-obj)


# clear unit test exec file
phony += clearunit	
clearunit: 
	rm -f $(units) 
	cd lib && rm -f $(addsuffix .o,$(units))

phony += clear
clear:
	@rm -f bin/simulation lib/* $(dependency)


ood: main.cpp liblocal.a
	@echo cc -o ood
	@$(cc) $(std) $(macro) $(include) $(debug) $(lib) $< -llocal  -o bin/$@

dod: main.cpp liblocal.a
	@echo cc -o ood
	@$(cc) $(std) $(include) $(debug) $(lib) $< -llocal  -o bin/$@

# create static lib
liblocal.a: $(objs)
	@echo ar -o liblocal.a $^
	@ar -r lib/liblocal.a $(addprefix lib/,$^) 2>/dev/null
	@rm -f $(addprefix lib/,$^)

.PHONY: $(phony)

# obj pattern
%.o: %.cpp
	@echo cc -c -o $@ 
	@$(cc) $(std) $(include) $(debug) -c -o $(pwd)/lib/$@ \
	$(filter %.cpp,$^)

# depend pattern
%.d: 
	@echo "all:">$(dependency)
	@echo cc -m $@
	@$(cc) $(include) -MM $(addprefix src/,$(subst .o,.cpp,$(objs))) 1>>$(dependency)