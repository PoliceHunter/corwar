//
// Created by Professional on 28.01.2021.
//

#include "../../includes/corwar.h"

void parse_dump_flag(t_cor *cor, char *num, int *i, int ac)
{
	long tmp;

	if (cor->flag.dump32 != 0 || cor->flag.dump64 != 0)
		exterminate(cor, FEW_AC_DUMP);
	if ((*i + 3) > ac)
		exterminate(cor, FEW_AC_DUMP);
	*i += 2;
	tmp = ft_atol(num);
	if (tmp > INT_MAX || tmp < 0)
		exterminate(cor, INVALID_FLAG_D);
	cor->flag.dump32 = (int)tmp;
}

void parse_d_flag(t_cor *cor, char *num, int *i, int ac)
{
	long tmp;

	if (cor->flag.dump64 != 0 || cor->flag.dump32 != 0)
		exterminate(cor, FEW_AC_DUMP);
	if ((*i + 3) > ac)
		exterminate(cor, FEW_AC_DUMP);
	*i += 2;
	tmp = ft_atol(num);
	if (tmp > INT_MAX || tmp < 0)
		exterminate(cor, INVALID_FLAG_D);
	cor->flag.dump64 = (int)tmp;
}

void visual(t_cor *cor, int ac, int *i)
{
	if (cor->flag.visual != 0)
		exterminate(cor, FEW_AC_V);
	if ((*i + 2) > ac)
		exterminate(cor, FEW_AC_V);
	cor->flag.visual = 1;
	*i += 1;
}

void flag_aff(t_cor *cor, int ac, int *i)
{
	if (cor->flag.aff != 0)
		exterminate(cor, FEW_AC_V);
	if ((*i + 2) > ac)
		exterminate(cor, FEW_AC_V);
	cor->flag.aff = 1;
	*i += 1;
}

void	parse_flags(t_cor *cor, int ac, char **av)
{
	int i;

	i = 0;
	while (++i < ac)
	{
		if (ft_strcmp(av[i], "-dump") == 0)
			parse_dump_flag(cor, av[i + 1], &i, ac);
		if (ft_strcmp(av[i], "-d") == 0)
			parse_d_flag(cor, av[i + 1], &i, ac);
		if (ft_strcmp(av[i], "-visual") == 0)
			visual(cor, ac, &i);
		if (ft_strcmp(av[i], "-aff") == 0)
			flag_aff(cor, ac, &i);
		if (!ft_strcmp(av[i], "-n") || is_filename(av[i], ".cor"))
		{
			if (ft_strcmp(av[i], "-n") == 0)
				save_num_player(cor, av[i + 1], &i, ac);
			else
				save_empty_num_player(cor, &i);
			cor->count_players++;
			if (cor->count_players > MAX_PLAYERS)
				exterminate(cor, TOO_MANY_PLAYERS);
		}
		else if (!is_filename(av[i], ".cor"))
			exterminate(cor, INVALID_PARAM);
	}
	cor->count_cursors = cor->count_players;
}