build: 
	gcc -o tema2 -Wall Netflix.c FctTema2.c FctLista.c FctCoada.c FctStiva.c
clean:
	rm -rf tema2 *.o