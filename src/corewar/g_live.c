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

	proc->live_last_cycle = cor->cycle;
	player_id = byte_to_int32(cor, proc, 0, cor->buffer_sizes[0]);
	if (player_id <= -1 && player_id >= -((int32_t)cor->count_players))
	{
		cor->last_live_player = proc->player_id;
		cor->count_lives++;
	}
}
