SRC := queens.c
TARGET := queens
CC = gcc
CFLAG = -Werror

ALL: $(SRC)
	$(CC) $(SRC) $(CFLAG) -o $(TARGET)

clean:
	rm $(TARGET)