Musuroi Daniel-Nicusor - 313CB
			
			TEMA 2 - NETFLIX

	Tema foloseste 4 fisiere .h:
-TLista.h
-TCoada.h
-TStiva.h
-Tema2.h
	Fiecare are un nume sugestiv si are asociat un fisier .c ce contine
functii ajutatoare pentru realizarea temei:
-FctLista.c -> contine functiile necesare pentru listele folosite
-FctCoada.c -> contine functiile necesare pentru cozile folosite
-FctStiva.c -> contine functiile necesare pentru stivele folosite
-FctTema2.c -> contine functiile necesare pentru realizarea temei, atat
cele principale ce descriu realizarea temei (add, add_top, add_sezon, 
later, watch, watch_later), cat si unele secundare ce ajuta la realizarea
functiilor principale (precum Extrage_serial, find_serial, show, ...).
	
	Erorile din program (precum alocarea de memorie nereusita) sunt 
semnalate prin mesaje la stdout usor de inteles.
	
	Functia add doar adauga un serial la una dintre cele 3 categorii
(liste).
	Functia add_top adauga un serial la cea de-a patra categorie Top10
(lista), avand grija sa se respecte pozitia sa in lista.
	Functia add_sezon gaseste serialul in una dintre cele 4 categorii
sau in categorie later, watching_later sau history si ii adauga un sezon
in coada de sezoane.
	Functia later muta un serialul din cele 4 categorii in coada later.
	Functia watch extrage serialul de unde se afla, scade durata ramasa
din serial cu durata data si daca mai ramane ceva de vizionat adauga serialul
in coada watching, iat daca nu adauga serialul in history.
	Functia show se foloseste de functii specifice pentru liste, cozi si
stive pentru a scrie in fisierul de output serialele din cele 4 categorii, 
din coada later sau din stivele watching sau history.

	Pe checkerul local primesc un punctaj de 103/135 (lipsa de timp).
	