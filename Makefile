GREEN=\033[0;32m
YELLOW=\033[0;33m
OFF=\033[0;0m

BUFFER_SIZE=1

test:
	@echo "$(GREEN)Compiling tests...$(OFF)"
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g3 -D BUFFER_SIZE=$(BUFFER_SIZE) -D TEST_FILE="\"tests/file.txt\""
	@echo "$(YELLOW)File test output:$(OFF)"
	@./test.out
	@valgrind ./test.out --track-origins=yes --check-leaks=full -s
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g3 -D BUFFER_SIZE=$(BUFFER_SIZE) -D TEST_FILE="\"tests/small_file.txt\""
	@echo "$(YELLOW)Small file test output:$(OFF)"
	@./test.out
	@valgrind ./test.out --track-origins=yes --check-leaks=full -s
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g3 -D BUFFER_SIZE=$(BUFFER_SIZE) -D TEST_FILE="\"tests/super_small_file.txt\""
	@echo "$(YELLOW)Super small file test output:$(OFF)"
	@./test.out
	@valgrind ./test.out --track-origins=yes --check-leaks=full -s
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g3 -D BUFFER_SIZE=$(BUFFER_SIZE) -D TEST_FILE="\"tests/empty_file.txt\""
	@echo "$(YELLOW)Empty file test output:$(OFF)"
	@./test.out
	@valgrind ./test.out --track-origins=yes --check-leaks=full -s
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g3 -D BUFFER_SIZE=$(BUFFER_SIZE) -D TEST_FILE="\"tests/empty_with_newlines_file.txt\""
	@echo "$(YELLOW)Empty file with a lot of newlines test output:$(OFF)"
	@./test.out
	@valgrind ./test.out --track-origins=yes --check-leaks=full -s
	@echo "$(GREEN)Cleaning up.$(OFF)"
	@rm test.out -f

debug:
	@echo "$(GREEN)Compiling debug binary...$(OFF)"
	@$(CC) get_next_line.c get_next_line_utils.c tests/get_next_line.c -o test.out -g3 -D BUFFER_SIZE=$(BUFFER_SIZE) -D TEST_FILE="\"tests/empty_with_newlines_file.txt\""

.PHONY: test debug
