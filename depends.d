all:
random.o: src/random.cpp /home/yang/gitdir/DOD-demo/include/random.h
vector2D.o: src/vector2D.cpp \
 /home/yang/gitdir/DOD-demo/include/vector2D.h
DOD_car.o: src/DOD_car.cpp /home/yang/gitdir/DOD-demo/include/DOD_car.h \
 /home/yang/gitdir/DOD-demo/include/carinfo.h \
 /home/yang/gitdir/DOD-demo/include/random.h \
 /home/yang/gitdir/DOD-demo/include/vector2D.h
OOD_car.o: src/OOD_car.cpp /home/yang/gitdir/DOD-demo/include/OOD_car.h \
 /home/yang/gitdir/DOD-demo/include/carinfo.h \
 /home/yang/gitdir/DOD-demo/include/random.h \
 /home/yang/gitdir/DOD-demo/include/vector2D.h
simulation.o: src/simulation.cpp \
 /home/yang/gitdir/DOD-demo/include/cars.h \
 /home/yang/gitdir/DOD-demo/include/DOD_car.h \
 /home/yang/gitdir/DOD-demo/include/carinfo.h \
 /home/yang/gitdir/DOD-demo/include/random.h \
 /home/yang/gitdir/DOD-demo/include/vector2D.h \
 /home/yang/gitdir/DOD-demo/include/OOD_car.h
