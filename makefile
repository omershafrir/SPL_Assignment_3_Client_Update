LDFLAGS:=-lboost_system -pthread

all: run

run: bin/Client.o bin/EncoderDecoder.o bin/connectionHandler.o
	g++ bin/Client.o bin/EncoderDecoder.o bin/connectionHandler.o -o run $(LDFLAGS)

bin/Client.o: src/Client.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Client.o src/Client.cpp

#bin/clients.o: src/clients.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/clients.o src/clients.cpp

bin/EncoderDecoder.o: src/EncoderDecoder.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/EncoderDecoder.o src/EncoderDecoder.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/connectionHandler.o src/connectionHandler.cpp

	@echo success

clean:
	rm bin/Client.o bin/clients.o  bin/run