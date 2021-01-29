/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljacquet <ljacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:56:21 by ljacquet          #+#    #+#             */
/*   Updated: 2020/12/18 14:48:30 by ljacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"
#include "../../includes/g_corewar_op.h"

//Циклы до исполнения 10

void				live(t_cor *cor, t_process *proc)
{
	int32_t 		player_id;
	int				i;
	int				valid;

	i = -1;
	valid = -1;
	proc->live_last_cycle = cor->cycle;
	player_id = byte_to_int32(cor, proc, 0, cor->buffer_sizes[0]);
	while (++i < cor->count_players)
		if (cor->player[i].id == -player_id)
			valid++;
	if (valid > -1)
	{
		cor->last_live_player = proc->player_id;
		cor->count_lives++;
	}
	/*if (cor->flag.dump64 == 0 && cor->flag.dump32 == 0)
	{
		ft_printf("cycle: %d curs: %d pos %d live %d\n", cor->cycle, proc->id, proc->pos, proc->live_last_cycle);
		//ft_printf("cor->cycle: %d\n", cor->cycle); //// Delete becouse unusage in original program
	}*/
}
