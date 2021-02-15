/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:33:41 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/12 13:32:06 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"
#include "../../includes/g_corewar_op.h"

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
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			cor->player[id].id, cor->player[id].code_size, cor->player[id].name,
			cor->player[id].comment);
}

void		print_log(t_cor *cor, t_process *process, int log_id)
{
	if (log_id == 0)
		return ;
	if (log_id == 1 && log_id == cor->flag.visual && cor->count_cursors != 0)
	{
		ft_printf("op_code: %2d | ", g_op[process->real_op_code].op_code);
		ft_printf("cycle %5d | proc_id %3d | fplayer_id: %d | pos: %5d |"
		"carry %d| coursors %d | liv %d\n", cor->cycle, process->id,
		process->player_id, process->pos, process->carry, cor->count_cursors,
		cor->count_lives);
	}
	else if (log_id == 2 && log_id == cor->flag.visual &&
									cor->count_cursors != 0)
		ft_printf("killed curs: %4d fplayer_id: %d pos %5d cycle: %d\n",
		process->id, process->player_id, process->pos, cor->cycle);
	else if (log_id == 3 && log_id == cor->flag.visual)
		ft_printf("cor->cycle: %5d | count_cursors: %4d | cycles_to_die: %4d"
			"| count_lives: %d \n", cor->cycle, cor->count_cursors,
				cor->cycles_to_die, cor->count_lives);
}
