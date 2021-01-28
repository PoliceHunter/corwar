//
// Created by Professional on 28.01.2021.
//

#include "../../includes/corwar.h"

int		check_duplicate_num(t_cor *cor, long tmp)
{
	int index;

	index = -1;
	while (++index < cor->count_players)
	{
		if (tmp == cor->player[index].id)
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
		exterminate(cor, FEW_AC_N);
	*i += 2;
	tmp = ft_atol(num);
	if (tmp > INT_MAX || tmp < INT_MIN)
		exterminate(cor, INVALID_FLAG_N);
	if (check_duplicate_num(cor, tmp))
		exterminate(cor, DUPLICATE_NUM_N);
	cor->player[amount_players].id = (int)tmp;
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
		count = cor->player[0].id;
		while (++index < cor->count_players)
			count = (count > cor->player[index].id) ? cor->player[index].id : count;
		count++;
		while (check_duplicate_num(cor, count))
			if (count++ == INT_MAX)
				return;
	}
	cor->player[cor->count_players].id = count;
	cor->player[cor->count_players].index_player_ac = *i;
}