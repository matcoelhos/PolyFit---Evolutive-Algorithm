CC = g++
FILES = main.cpp EA.cpp solucao.cpp problema.cpp
OPTIONS = -std=c++11 -ofast

#main section
main: $(FILES)
	$(CC) $(OPTIONS) $(FILES) -o main

clear:
	rm -f main
