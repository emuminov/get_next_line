GREEN=\033[0;32m
YELLOW=\033[0;33m
OFF=\033[0;0m

BUFFER_SIZE=10000000

test:
	@echo "$(GREEN)Compiling tests...$(OFF)"
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g3 -D BUFFER_SIZE=$(BUFFER_SIZE)
	@echo "$(YELLOW)Test output:$(OFF)"
	@./test.out
	@valgrind ./test.out --check-leaks=full -s
	@echo "$(GREEN)Cleaning up.$(OFF)"
	@rm test.out -f

debug:
	@echo "$(GREEN)Compiling debug binary...$(OFF)"
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g3 -D BUFFER_SIZE=$(BUFFER_SIZE)

.PHONY: test debug
