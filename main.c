#include "monty.h"

/**
 * main - Checks arguments, open file to work with then
 * calls the function _readline to extract the lines from the file
 *
 * @argc: Number of arguments passed to the program.
 * @argv: arguments, file to work with must be included.
 * Return: 0  on success,
 * otherwise calls the appropiate function to handle the error and exits.
 */
int main(int argc, char **argv)
{
	int montyfd;
	FILE *montyf;

	if (argc == 2)
	{
		montyfd = open(argv[1], O_RDONLY);
		if (montyfd == -1)
		{
			openerr(argv[1]);
		}
		montyf = fdopen(montyfd, "r");
		_readline(montyf);
	} else
		nargumenterr();
	return (0);
}

/**
 * _readline - Reads the lines from a file and
 * calls the function _chkcmd to call the appropiate operation
 *
 * @fd: file descriptor to a File in the system
 *
 */
void _readline(FILE *fd)
{
	char *cmd, *cvalue, *linerd;
	size_t nlinerd = 0, line = 0;
	stack_t *stack = NULL;
	instruction_t ins[] = {
		{"push", _opush},
		{"pall", _opall},
		{NULL, NULL}
	};

	while (getline(&linerd, &nlinerd, fd) > 0)
	{
		line++;
		cmd = linerd;
		cvalue = NULL;
		while (*linerd != '\n')
		{
			if (*linerd == ' ' && *linerd - 1 != ' ')
			{
				*linerd = '\0';
				cvalue = linerd + 1;
			}
			linerd += 1;
		}
		*linerd = '\0';
		_chkcmd(ins, cmd, cvalue, &stack, line);
	}
}

/**
 * _chkcmd - Compares a command received and calls the appropiate function.
 *
 * @ins: Structure with a list of operations.
 * @cmd: command to compare with structure elements.
 * @cvalue: argument used when calling the operation function.
 * @stack: Linear data structure used when calling the operation function.
 *
 */
void _chkcmd(instruction_t *ins, char *cmd, char *cvalue,
	     stack_t **stack, size_t line)
{
	unsigned int line_number = 0;

	while (cvalue)
	{
		if (_isdigit(*cvalue) != 0)
			;
		else
			nint(line);
		cvalue += 1;
	}
	while (ins->opcode != NULL)
	{
		if (_strcmp(ins->opcode, cmd) == 0)
		{
			ins->f(stack, line_number);
			break;
		}
		ins += 1;
	}
}