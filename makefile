assemble: act.o macros.o command_line.o labels.o trie.o vector.o datatable.o entry.o extern.o externout.o object.o 
	gcc -ansi -Wall -g act.o macros.o command_line.o labels.o trie.o vector.o datatable.o entry.o extern.o externout.o object.o  -o assemble 
act.o: act.c define.h vector.h declerations.h 
	gcc -c -ansi -Wall -g act.c -o act.o
macros.o: macros.c define.h
	gcc -c -ansi -Wall -g macros.c -o macros.o
command_line.o: command_line.c define.h declerations.h trie.h 
	gcc -c -ansi -Wall -g command_line.c -o command_line.o 
labels.o: labels.c define.h trie.h
	gcc -c -ansi -Wall -g labels.c -o labels.o
trie.o: trie.c 
	gcc -c -ansi -Wall -g trie.c -o trie.o
vector.o: vector.c
	gcc -c -ansi -Wall -g vector.c -o vector.o
datatable.o: datatable.c define.h declerations.h trie.h 
	gcc -c -ansi -Wall -g datatable.c -o datatable.o
entry.o: entry.c define.h declerations.h trie.h
	gcc -c -ansi -Wall -g entry.c -o entry.o
extern.o: extern.c define.h declerations.h trie.h
	gcc -c -ansi -Wall -g extern.c -o extern.o
externout.o: externout.c define.h declerations.h trie.h 
	gcc -c -ansi -Wall -g externout.c -o externout.o
object.o: object.c define.h declerations.h trie.h
	gcc -c -ansi -Wall -g object.c -o object.o

