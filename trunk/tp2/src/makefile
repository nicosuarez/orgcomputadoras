all: tp2

tp2: tamanioCache tamanioBloque cantidadVias tp2.cpp
	g++ -Wall -pedantic -g tp2.cpp -o tp2

tamanioCache: tamanioCache.cpp
	g++ -Wall -pedantic -O1 -g tamanioCache.cpp -o tamanioCache

tamanioBloque: tamanioBloque.cpp
	g++ -Wall -pedantic -O1 -g tamanioBloque.cpp -o tamanioBloque

cantidadVias: cantidadVias.cpp
	g++ -Wall -pedantic -O1 -g cantidadVias.cpp -o cantidadVias

clean:
	-rm -f tamanioCache tamanioBloque cantidadVias tp2




