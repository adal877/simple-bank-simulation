COMP = gcc
CFLAGS = -ggdb -fasynchronous-unwind-tables -fstack-clash-protection -g3 -O2
SOURCE = main.c bank.c bank.h
BIN = run-main

$(BIN): $(SOURCE)
	$(COMP) $(CFLAGS) $(SOURCE) -o $(BIN)
