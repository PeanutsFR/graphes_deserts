FLAGS    = -Wall -g3 -O3 -c 
FLEXE    = -Wall -g3 -O3 -o 


generation : generation.o main.c graph_outils.o
	gcc $(FLEXE) generation generation.o main.c graph_outils.o

%.o : %.c %.h
	gcc $(FLAGS) $<

clean : 
	rm -f *.o generation

