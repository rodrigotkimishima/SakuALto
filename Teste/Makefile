cc = `pkg-config --cflags --libs gtk+-3.0` 
o = Lista.o Pontos.o
example:	$(o)
	gcc example.c	$(o)	-o	example	$(cc)

Lista.o:	Lista.c	Lista.h
	gcc $(cc) -c Lista.c	


Pontos.o: Pontos.c Pontos.h
	gcc $(cc) -c Pontos.c

clean:	
	rm	-rf	*.o	./example *.svg
