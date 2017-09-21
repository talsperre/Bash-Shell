
# Make file:
#	takes all the files
#	Compiles them

shell:	builtin.c	main.c	read.c	printPrompt.c  commands.c exec.c shell_loop.c shell_initialize.c sig_handler.c nightswatch.c semicolon_seperate.c
	gcc	-o	shell	exec.c builtin.c	main.c	read.c	printPrompt.c commands.c shell_loop.c shell_initialize.c sig_handler.c nightswatch.c semicolon_seperate.c