CC=gcc
CFLAGS=-g -Wall
OBJS=main.o command_line.o get_token.o is_redirection.o is_pipe.o change_directory.o
TARGET=minishell.out

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
	
main.o: header.h main.c
command_line.o: header.h command_line.c
get_token.o: header.h get_token.c
is_redirection.o: header.h is_redirection.c
is_pipe.o: header.h is_pipe.c
change_directory.o: header.h change_directory.c
