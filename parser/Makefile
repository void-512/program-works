objects = test-parser.o parser.o

parser : $(objects)
	gcc -o parser $(objects)

test-parser.o : test-parser.c parser.h
	gcc -c test-parser.c

parser.o : parser.c parser.h
	gcc -c parser.c

.PHONY : clean
clean : 
	del *.o