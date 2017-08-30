shell:	builtin.c	main.c	read.c	printPrompt.c  commands.c exec.c shell_loop.c
	gcc	-o	shell	exec.c builtin.c	main.c	read.c	printPrompt.c commands.c shell_loop.c