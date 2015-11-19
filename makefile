# build an executable named myprog from myprog.c
the_network: main.o wallpost.o wall.o user.o usernetwork.o
	g++ main.o wall.o wallpost.o user.o usernetwork.o -o the_network -std=c++11

main.o: usernetwork.h
	g++ main.cpp -c -std=c++11

usernetwork.o: user.h linkedlist.h
	g++ usernetwork.cpp -c

user.o: linkedlist.h wall.h wallpost.h
	g++ user.cpp -c -std=c++11

wallpost.o:
	g++ wallpost.cpp -c -std=c++11

wall.o: wallpost.h linkedlist.h
	g++ wall.cpp -c -std=c++11



clean:
	rm the_network -f
	rm *.o -f
	cp data.txt.bak data.txt
	cp data_friends.txt.bak data_friends.txt
	cp data_comments.txt.bak data_comments.txt
