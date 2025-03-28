#include <stdio.h>
#include <stdlib.h>

// Compile fake functions if using windows
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char * readline (char *prompt) {
	fputs (prompt, stdout);
	fgets (buffer, 2048, stdin);
	
	char *cpy = malloc (strlen (buffer) + 1);
	strcpy (cpy, buffer);
	cpy [strlen (cpy) - 1] = '\0';
	return cpy;
}

// Fake add history function
void add_history (char *unused) {}

// Other wise include editlines headers
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main (int argc, char **argv) {
	puts ("Lisp Version 0.0.1");
	puts ("Press Ctrl+c to Exit\n");
	
	while (1) {
		char *input = readline ("lisp> ");
		add_history (input);
		
		printf ("No you're a %s\n", input);
		free (input);
	}
	
	return 0;
}
