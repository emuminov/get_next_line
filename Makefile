GREEN=\033[0;32m
YELLOW=\033[0;33m
OFF=\033[0;0m

test:
	@echo "$(GREEN)Compiling tests...$(OFF)"
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g
	@echo "$(YELLOW)Test output:$(OFF)"
	@./test.out
	@valgrind ./test.out --check-leaks=full -s
	@echo "$(GREEN)Cleaning up.$(OFF)"
	@#rm test.out -f

.PHONY: test
