#include "../../includes/corwar.h"

int			is_filename(const char *filename, const char *ext)
{
	if (filename && ext && ft_strlen(filename) >= ft_strlen(ext))
		return (!ft_strcmp(ft_strchr(filename, '\0') - ft_strlen(ext), ext));
	else
		return (FALSE);
}

void start_game(t_cor *cor)
{
	int		index;

	index = -1;
    process_game_logic(cor);
	while (cor->last_live_player != 0 && ++index < cor->count_players)
	{
		if (cor->player[index].id == cor->last_live_player)
			break;
	}
	if (cor->flag.dump64 == 0 && cor->flag.dump32 == 0)
	{
		if (cor->last_live_player == 0)
		{
			index = 0;
			cor->last_live_player = cor->player[index].id;
		}
		ft_printf("Contestant %d, \"%s\", has won !\n", cor->last_live_player, cor->player[index].name);
	}
	free_cor(cor);
}



int main(int ac, char **av)
{
	t_cor cor;
	if (ac == 1)
		error_usage();
	init_cor(&cor, av);
	parse_flags(&cor, ac, av);
	parse_champion_file(&cor);
	init_arena(&cor);
	init_processes(&cor);
	print_intro(&cor);
	start_game(&cor);
	return 0;
}
//TODO Зависимость id игрока от положения на карте
