objects = test-xmltree.o collector.o tokenizer.o xml-tree.o

xmltree : $(objects)
	clang -o xmltree $(objects)

test-xmltree.o : tokenizer.h xml-tree.h tokenizer.c xml-tree.c
	clang -c test-xmltree.c

collector.o : collector.h collector.h
	clang -c collector.c

tokenizer.o : tokenizer.h collector.h tokenizer.c collector.c
	clang -c tokenizer.c

xml-tree.o : xml-tree.h collector.h collector.c
	clang -c xml-tree.c

.PHONY : clean
clean : 
	del *.o