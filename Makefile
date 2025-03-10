CC = gcc
CFLAGS = -g -Werror -Wall

SRCS = main.c basic.c board.c run.c commands.c write.c
OUT = main.out

all: $(OUT) 

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT)

clean:
	rm -f $(OUT)
