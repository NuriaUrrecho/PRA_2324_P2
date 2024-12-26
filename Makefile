bin/testMonedas: monedas.cpp
	mkdir -p bin
	g++ -o bin/testMonedas monedas.cpp

bin/testMochila: mochila.cpp
	mkdir -p bin
	g++ -o bin/testMochila mochila.cpp

clean:
	rm -rf *.o *.gch bin 2>/dev/null || true