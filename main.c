#include "corwar.h"

void init_cor(t_cor *cor, char **av)
{
	cor->cycles_to_die = CYCLE_TO_DIE;
	cor->files = av;
	cor->count_players = 0;
	cor->flag.visual = 0;
	cor->flag.dump32 = 0;
	cor->flag.dump64 = 0;
	cor->count_cursors = 0;
	cor->cycle = 0;
	cor->cycle_to_check = 0;
	cor->last_live_player = 0;
}

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

int			is_filename(const char *filename, const char *ext)
{
	if (filename && ext && ft_strlen(filename) >= ft_strlen(ext))
		return (!ft_strcmp(ft_strchr(filename, '\0') - ft_strlen(ext), ext));
	else
		return (FALSE);
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

static int32_t	bytecode_to_int32(const uint8_t *bytecode, size_t size)
{
	int32_t	result;
	_Bool	sign;
	int		i;

	result = 0;
	sign = (_Bool)(bytecode[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

static int32_t	parse_int32(t_cor *cor, int fd)
{
	ssize_t	size;
	uint8_t	buffer[4];

	size = read(fd, &buffer, 4);
	if (size == -1)
		exterminate(cor, FAIL_READ);
	if (size < 4)
		exterminate(cor, ERR_FILE);
	return (bytecode_to_int32(buffer, 4));
}

static char		*parse_str(t_cor *cor, int fd, size_t len)
{
	ssize_t	size;
	char	*buffer;

	if (!(buffer = ft_strnew(len)))
		exterminate(cor, ERR_STR_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		exterminate(cor, FAIL_READ);
	if (size < (ssize_t)len)
		exterminate(cor, ERR_FILE);
	return (buffer);
}

static uint8_t	*parse_code(t_cor *cor, int fd, size_t len)
{
	long int size;
	uint8_t	*buffer;
	uint8_t	byte;

	if (!(buffer = malloc(len)))
		exterminate(cor, ERR_CODE_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		exterminate(cor, FAIL_READ);
	if (size < (ssize_t)len || read(fd, &byte, 1) != 0)
		exterminate(cor, ERR_FILE);
	return (buffer);
}

void parse_champion_file(t_cor *cor)
{
	int index;
	int fd;

	index = -1;
	while (++index < cor->count_players)
	{
		if (ft_strlen(cor->files[cor->player[index].index_player_ac]) <= 4)
			exterminate(cor, INVALID_PARAM);
		if ((fd = open(cor->files[cor->player[index].index_player_ac], O_RDONLY)) < 0)
			exterminate(cor, FAIL_OPEN);
		if (parse_int32(cor, fd) != COREWAR_EXEC_MAGIC)
			exterminate(cor, ERR_MAGIC);
		cor->player[index].name = parse_str(cor, fd, PROG_NAME_LENGTH);
		if (parse_int32(cor, fd) != 0)
			exterminate(cor, ERR_NO_NULL);
		if ((cor->player[index].code_size = parse_int32(cor, fd)) < 0 || cor->player[index].code_size > CHAMP_MAX_SIZE)
			exterminate(cor, INVALID_CODE_SIZE);
		cor->player[index].comment = parse_str(cor, fd, COMMENT_LENGTH);
		if (parse_int32(cor, fd) != 0)
			exterminate(cor, ERR_NO_NULL);
		cor->player[index].code = parse_code(cor, fd, cor->player[index].code_size);
		close(fd);
	}
}

void	error_usage(void)
{
	ft_putstr_fd("Usage:\n \
	Example: ./corewar -visual -n -1 filename.cor\n \
	GUI: ./corewar -visual [Players]\n \
	Default Player Numbers: 1, 2, 3, 4...\n \
	Change Player Number: -n -1 filename.cor\n \
	Dump: ./corewar -dump 300 [Players](prints the memory after 300 cycles)\n \
	Game on! 👾 🤖 🔫 \n", 2);
	exit(1);
}

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

void init_arena(t_cor *cor)
{
	int index;
	uint32_t pos;

	pos = 0;
	index = -1;
	while (++index != cor->count_players)
	{
		ft_memcpy(&(cor->map[pos]), cor->player[index].code, (size_t)cor->player[index].code_size);
		cor->player[index].position_on_map = pos;
		pos += MEM_SIZE / cor->count_players;
	}
}

t_process *init_process(int32_t pos, t_vector process)
{
	t_process *proc;

	proc = malloc(sizeof(t_process));
	proc->carry = FALSE;
	proc->cycle_to_exec = 0;
	proc->live_last_cycle = 0;
	proc->live_last_id = 0;
	proc->pos = pos;
	proc->op_code = 0;
	proc->id = process.size; // Указываем id процесса по размеру вектора
	proc->player_id = 0;

	return (proc);
}

void init_processes(t_cor *cor)
{
	int index;
	int32_t pos;
	t_vector process;

	pos = 0;
	process = new_vector(cor->count_cursors, sizeof(t_process));
	index = -1;
	while (++index != cor->count_cursors)
	{
		push_back_vec(&process, init_process(pos, process));
		pos += MEM_SIZE / cor->count_players;
	}
	cor->process = process;
}

void		print_intro(t_cor *cor)
{
	int32_t id;

	id = -1;
	ft_printf("Introducing contestants...\n");
	while (++id != cor->count_players)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", id, cor->player[id].code_size, cor->player[id].name, cor->player[id].comment);
}

void make_op(t_process *proc, t_cor *cor)
{

}

void check_cycle(t_cor *cor)
{
	int index;

	index = 0;
	cor->cycle++;
	cor->cycle_to_check++;
	while (cor->process.size > index)
		make_op(get_from_vec(&cor->process, index), cor);
}

void start_game(t_cor *cor)
{
	while (cor->process.size != 0)
	{
		if (cor->flag.dump64 == cor->cycle)
			print_arena(cor->map, 64);
		if (cor->flag.dump32 == cor->cycle)
			print_arena(cor->map, 32);
		check_cycle(cor);

	}
}

void op_add(t_cor *cor, t_process *cursor)
{

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
	if (cor.flag.visual == FALSE)
	{
		print_intro(&cor);
		//start_game(&cor);
	}
	op_add(&cor, get_from_vec(&cor.process, 2));
	print_arena(cor.map, 32);
	return 0;
}
//TODO Зависимость id игрока от положения на карте