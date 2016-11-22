CC=gcc
CFLAGS=-fprofile-arcs -ftest-coverage 
name=refactored_expenseReport

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $< 

.PHONY: run
run: $(name).exe
	./$(name).exe
	
.PHONY: gcov
gcov: run
	gcov $(name).c

.PHONY: rebuild
rebuild: clean run

.PHONY: clean
clean:
	rm -f *.exe *.gcda *.gcno *.gcov
