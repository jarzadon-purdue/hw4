# You MUST modify this file

GCC = gcc
CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -DRUN_INTEGRATE -DTEST_INTEGRATE
LIBS = -lm
EXEC = hw4

OBJS = hw4.o integrator-hw4.o func1.o func2.o func3.o func4.o func5.o

%.o : %.c
	$(GCC) $(CFLAGS) -c $<

$(EXEC): $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXEC)

testall: $(EXEC)
	./$(EXEC) testcases/test1 output1.txt
	./$(EXEC) testcases/test2 output2.txt
	./$(EXEC) testcases/test3 output3.txt
	./$(EXEC) testcases/test4 output4.txt

clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f output*.txt