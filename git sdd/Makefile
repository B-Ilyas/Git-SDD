CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc

PROGRAMS = main_list main_work main_commit myGit main_branch main_fusion

.PHONY:	all clean

all: $(PROGRAMS)

main_list: list.o main1.o
	$(CC) -o $@ $(CFLAGS) $^
	
main_work: list.o work.o main2.o
	$(CC) -o $@ $(CFLAGS) $^

main_commit: list.o work.o commit.o main3.o
	$(CC) -o $@ $(CFLAGS) $^

myGit: list.o work.o commit.o branch.o fusion.o myGit.o
	$(CC) -o $@ $(CFLAGS) $^

main_branch: list.o work.o commit.o branch.o main4.o
	$(CC) -o $@ $(CFLAGS) $^

main_fusion: list.o work.o commit.o branch.o fusion.o main5.o
	$(CC) -o $@ $(CFLAGS) $^

list.o: list.c
	gcc $(CFLAGS) -c $^

work.o: work.c
	gcc $(CFLAGS) -c $^

commit.o: commit.c
	gcc $(CFLAGS) -c $^

branch.o: branch.c
	gcc $(CFLAGS) -c $^

fusion.o: fusion.c
	gcc $(CFLAGS) -c $^

main1.o: main1.c
	gcc $(CFLAGS) -c $^

main2.o: main2.c
	gcc $(CFLAGS) -c $^

main3.o: main3.c
	gcc $(CFLAGS) -c $^

myGit.o: myGit.c
	gcc $(CFLAGS) -c $^
	
main4.o: main4.c
	gcc $(CFLAGS) -c $^

main5.o: main5.c
	gcc $(CFLAGS) -c $^


clean:
	rm -f *.o *~ $(PROGRAMS)


