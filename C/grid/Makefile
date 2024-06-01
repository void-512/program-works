objects = test-grid.o grid.o symlib.o

grid : $(objects)
	gcc -o grid $(objects)

test-grid.o : test-grid.c grid.h grid.c symlib.h symlib.c
	gcc -c test-grid.c

grid.o : grid.h grid.c
	gcc -c grid.c

symlib.o : symlib.h symlib.c
	gcc -c symlib.c

.PHONY : clean
clean : 
	del *.o