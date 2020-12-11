#include "corwar.h"

void init_cor(t_cor *cor, char **av)
{
	cor->cycles_to_die = CYCLE_TO_DIE;
	cor->files = av;
	cor->count_players = 0;
}

void parse_dump_flag(t_cor *cor, char *num, int *i, int ac)
{
	long tmp;

	if ((*i + 3) > ac)
		ft_printf("Count players need >= 2\n"); /// exit func
	*i += 1;
	tmp = atol(num); ///TODO write ft_atol
	if (tmp > INT_MAX || tmp < 0)
		ft_printf("Invalid dump num\n"); /// Need functiom exit
	cor->dump = (int)tmp;
}

int		check_duplicate_num(t_cor *cor, long tmp)
{
	int index;

	index = -1;
	while (++index < cor->count_players)
	{
		if (tmp == cor->player[index].player_num)
			return (1);
	}
	return (0);
}


void	save_num_player(t_cor *cor, char *num, int *i, int ac)
{
	long tmp;
	int amount_players;

	amount_players = cor->count_players;
	if ((*i + 3) > ac)
		ft_printf("Count players need >= 2\n"); /// exit func
	*i += 2;
	tmp = atol(num); ///TODO write ft_atol
	if (tmp > INT_MAX || tmp < INT_MIN)
		ft_printf("INVALID NUM for -n\n"); ///exit func
	if (check_duplicate_num(cor, tmp))
		ft_printf("THIS NUM IS ALREADY EXISTS!\n"); /// exit func
	cor->player[amount_players].player_num = (int)tmp;
	cor->player[amount_players].index_player_ac = *i;
}

void	save_empty_num_player(t_cor *cor, const int *i)
{
	int count;
	int index;

	index = -1;
	if (cor->count_players == 0)
		count = 1;
	else
	{
		count = cor->player[0].player_num;
		while (++index < cor->count_players)
			count = (count > cor->player[index].player_num) ? cor->player[index].player_num : count;
		count++;
		while (check_duplicate_num(cor, count))
			if (count++ == INT_MAX)
				return;
	}
	cor->player[cor->count_players].player_num = count;
	cor->player[cor->count_players].index_player_ac = *i;
}

void	parse_flags(t_cor *cor, int ac, char **av)
{
	int i;

	i = 1;
	if (ft_strcmp(av[i], "-dump") == 0)
		parse_dump_flag(cor, av[i + 1], &i, ac);
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-n") || is_filename(av[i], ".cor"))
		{
			if (ft_strcmp(av[i], "-n") == 0)
				save_num_player(cor, av[i + 1], &i, ac);
			else
				save_empty_num_player(cor, &i);
			cor->count_players++;
			if (cor->count_players > MAX_PLAYERS)
				ft_printf("TOO MNOGO PLAYERS!!! СВАЛИТЕ ОТСЮДА НАБУБОН\n"); ///exit func
		}
	}
	cor->count_cursors = cor->count_players;
}

int main(int ac, char **av)
{
	t_cor cor;
	if (ac == 1)
		printf("Error usage, programm arg should be more then 1");
	init_cor(&cor, av);
	parse_flags(&cor, ac, av);
	parse_champion_file(&cor, ac, av);
	return 0;
}
