

CC= g++
CFLAGS= -g -std=c++17

output: main.o
	$(CC) $(CFLAGS) *.o -o main.elf

main.o: main.cpp student.o text.o node.h node.tpp
	$(CC) $(CFLAGS) -c main.cpp
	
student.o: text.o student.cpp student.h	
	$(CC) $(CFLAGS) -c student.cpp
	
# node.o: node.cpp node.h	
# 	$(CC) $(CFLAGS) -c node.cpp

text.o: text.cpp text.h
	$(CC) $(CFLAGS) -c text.cpp
	
clean:
	rm *.o main.elf