all: client server

client: basic_client.o pipe_networking.o connect_four.o
	gcc -o client basic_client.o pipe_networking.o connect_four.o

server: basic_server.o pipe_networking.o connect_four.o
	gcc -o server basic_server.o pipe_networking.o connect_four.o

connect_four.o: connect_four.c connect_four.h
	gcc -c connect_four.c

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	rm *~
