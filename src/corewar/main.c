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
	//print_arena(cor->map, 64);
	game_logic(cor);
	while (++index < cor->count_players)
	{
		if (cor->player[index].id == cor->last_live_player)
			break;
	}
	if (cor->flag.dump64 == 0 && cor->flag.dump32 == 0)
		ft_printf("Contestant %d, \"%s\", has won !\n", cor->last_live_player, cor->player[index].name);


		//t_process *caretka = get_from_vec(&cor->process, index);
		//caretka->name_op = cor->map[caretka->pos]; // Check if name_op is correct
		//find_op(cor, caretka->name_op, caretka); // сопоставляет имся операции и выполняет функцию с названием этой операции
		/*if (index == cor->process.size)
		{
			check_cycle(cor);
			index = -1;
		}*/
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
	//((t_op *)operation[cor.map[((t_process *)get_from_vec(&cor.process, 1))->pos]])
	//ft_printf("\n%d\n", cor.map[0]);
	//uint8_t	buffer[4];
	//buffer[0] = cor.map[2];
	//buffer[1] = cor.map[3];
	//buffer[2] = cor.map[4];
	//buffer[3] = cor.map[5];
	//int y = bytecode_to_int32(buffer, 4);
	//ft_printf("---%d---", y);
	if (cor.flag.visual == FALSE)
	{
		print_intro(&cor);
		start_game(&cor);
	}
	//add(&cor, get_from_vec(&cor.process, 0));
	//print_arena(cor.map, 32);
	return 0;
}
//TODO Зависимость id игрока от положения на карте