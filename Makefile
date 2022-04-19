CC=gcc
FIND_UTILITY=find_utility.o

%.o:%.c
	${CC} -c -o $@ $^

find_utility:${FIND_UTILITY}
	${CC} -o $@ $^

clean: 
	rm -f *.o
	rm -f find_utility