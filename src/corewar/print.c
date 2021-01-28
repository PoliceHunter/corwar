//
// Created by Professional on 28.01.2021.
//

#include "../../includes/corwar.h"

void		print_arena(uint8_t *map, int print_mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.4p : ", i);
		j = -1;
		while (++j < print_mode)
			ft_printf("%.2x ", map[i + j]);
		ft_printf("\n");
		i += print_mode;
	}
}

void		print_intro(t_cor *cor)
{
	int32_t id;

	id = -1;
	ft_printf("Introducing contestants...\n");
	while (++id != cor->count_players)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", id, cor->player[id].code_size, cor->player[id].name, cor->player[id].comment);
}
