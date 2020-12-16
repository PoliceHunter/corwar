#include "corwar.h"

void init_cor(t_cor *cor, char **av)
{
	cor->cycles_to_die = CYCLE_TO_DIE;
	cor->files = av;
	cor->count_players = 0;
	cor->flag.visual = 0;
	cor->flag.dump = 0;
}

void parse_dump_flag(t_cor *cor, char *num, int *i, int ac)
{
	long tmp;

	if ((*i + 3) > ac)
		exterminate(cor, FEW_AC_DUMP);
	*i += 1;
	tmp = atol(num); ///TODO write ft_atol
	if (tmp > INT_MAX || tmp < 0)
		exterminate(cor, INVALID_FLAG_D);
	cor->flag.dump = (int)tmp;
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
		exterminate(cor, FEW_AC_N);
	*i += 2;
	tmp = atol(num); ///TODO write ft_atol
	if (tmp > INT_MAX || tmp < INT_MIN)
		exterminate(cor, INVALID_FLAG_N);
	if (check_duplicate_num(cor, tmp))
		exterminate(cor, DUPLICATE_NUM_N);
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

int			is_filename(const char *filename, const char *ext)
{
	if (filename && ext && ft_strlen(filename) >= ft_strlen(ext))
		return (!ft_strcmp(ft_strchr(filename, '\0') - ft_strlen(ext), ext));
	else
		return (FALSE);
}

void visual(t_cor *cor, int ac, int *i)
{
	if ((*i + 2) > ac)
		exterminate(cor, FEW_AC_V);
	cor->flag.visual = 1;
	*i += 1;
}

void	parse_flags(t_cor *cor, int ac, char **av)
{
	int i;

	i = 1;
	if (ft_strcmp(av[i], "-dump") == 0)
		parse_dump_flag(cor, av[i + 1], &i, ac);
	else if (ft_strcmp(av[i], "-visual") == 0)
		visual(cor, ac, &i);
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

int main(int ac, char **av)
{
	t_cor cor;
	if (ac == 1)
		error_usage();
	init_cor(&cor, av);
	parse_flags(&cor, ac, av);
	parse_champion_file(&cor);
	return 0;
}
