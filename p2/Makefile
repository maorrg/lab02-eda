SOURCE  = main.cpp
OUT = main.o
CC  = g++
CFLAGS  = -pthread

all: compile-main

compile-main:
	$(CC) $(CFLAGS) $(SOURCE) -o $(OUT)

run-basic: compile-main
	./$(OUT)

test:
	$(CC) $(CFLAGS) test.cpp -o $(OUT)

all-operations: test
	./$(OUT) all

single-pop: test
	./$(OUT) singlePop

single-push: test
	./$(OUT) singlePush

correct-items: test
	./$(OUT) correctItems

multiple-pop: test
	./$(OUT) multiplePop

multiple-push: test
	./$(OUT) multiplePush

clean:
	rm $(OUT)