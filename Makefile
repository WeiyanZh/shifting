tests: tests.c
	gcc -std=c99 -pedantic -Wall -Werror -Wextra $< -o $@

