

CC= g++
CFLAGS= -g -std=c++17

output: computer.o file.o folder.o globalVarsNFuns.o main.o memory.o parser.o path.o text.o ipadress.o
	$(CC) $(CFLAGS) *.o -o main.elf

computer.o: computer.cpp computer.h text.o globalVarsNFuns.o command.h parser.o path.o file.o memory.o folder.o
	$(CC) $(CFLAGS) -c computer.cpp
	
file.o: file.cpp file.h text.o path.o
	$(CC) $(CFLAGS) -c file.cpp
	
folder.o: folder.cpp folder.h text.o path.o file.o
	$(CC) $(CFLAGS) -c folder.cpp
	
globalVarsNFuns.o: globalVarsNFuns.cpp globalVarsNFuns.h text.o
	$(CC) $(CFLAGS) -c globalVarsNFuns.cpp
	
main.o: main.cpp text.o globalVarsNFuns.o command.h parser.o path.o file.o memory.o folder.o computer.o
	$(CC) $(CFLAGS) -c main.cpp
	
memory.o: memory.cpp memory.h text.o path.o file.o
	$(CC) $(CFLAGS) -c memory.cpp
	
parser.o: parser.cpp parser.h text.o command.h
	$(CC) $(CFLAGS) -c parser.cpp

path.o: path.cpp path.h text.o
	$(CC) $(CFLAGS) -c path.cpp
	
ipadress.o: ipadress.cpp ipadress.h 
	$(CC) $(CFLAGS) -c ipadress.cpp

text.o: text.cpp text.h 
	$(CC) $(CFLAGS) -c text.cpp
	
clean:
	rm *.o main.elf