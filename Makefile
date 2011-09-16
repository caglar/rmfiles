CC=gcc
CFLAGS=-O4

rm_files: 
	$(CC) $(CFLAGS) rm_files.c -o rm_files
