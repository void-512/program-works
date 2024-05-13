objects = test-morse.o morse.o

morse : $(objects)
	gcc -o morse $(objects)

test-morse.o : test-morse.c morse.h
	gcc -c test-morse.c

morse.o : morse.c morse.h
	gcc -c morse.c

.PHONY : clean
clean : 
	del *.o