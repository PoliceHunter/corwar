#include <stdio.h>
#include "corwar.h"

void init_cor(t_cor *cor, char **av)
{
	cor->cycles_to_die = CYCLE_TO_DIE;
	cor->files = av;
}

int main(int ac, char **av)
{
	t_cor cor;
	if (ac == 1)
		printf("Error usage, programm arg should be more then 1");
	init_cor(&cor, av);
	parse_flags(&cor, ac, av);
	files_to_string(&cor);
	parse_players(&cor);
	printf("Hello, World!\n");
	return 0;
}
