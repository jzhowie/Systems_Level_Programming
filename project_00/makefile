all: main.o music_list.o library.o
	gcc -o music_library main.o music_list.o library.o

main.o: main.c music_list.h library.h
	gcc -c main.c

library.o: library.c library.h music_list.h
	gcc -c library.c

music_list.o: music_list.c music_list.h
	gcc -c music_list.c

run:
	./music_library
