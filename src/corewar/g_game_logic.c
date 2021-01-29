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

static _Bool	is_died(t_cor *cor, t_process *proc)
{
	return (cor->cycles_to_die <= 0
	        || cor->cycle - proc->live_last_cycle >= cor->cycles_to_die);
}

void 			kill_caretka(t_cor *cor)
{
	//1 - удалить из структуры данную каретку, очистить память
	//free(proc); //возможно не надо
	t_process *process;
	int index;

	index = -1;
	while (++index < cor->count_cursors)
	{
		process = get_from_vec(&cor->process, index);
		if (process->live_last_cycle == -1 && is_died(cor, process))
		{
			remove_from_vec(&cor->process, index);
			cor->count_cursors--;
			index--;
		}
		else
			process->live_last_cycle = -1; //// Проверить на правильность ипспользования
	}
}

void 			proverka(t_cor *cor)
{
	int 		index;
	t_process	*process;

	index = 0;
	cor->count_check++;
	kill_caretka(cor);
	if (cor->count_lives >= NBR_LIVE || cor->count_check == MAX_CHECKS)
	{
		cor->cycles_to_die -= CYCLE_DELTA;
		cor->count_check = 0;
	}
	cor->cycles_after_check = 0;
	cor->count_lives = 0; //// Wast ist das?
}

int 			game_logic(t_cor *cor)
{
	cor->cycles_to_die = CYCLE_TO_DIE;
	while (cor->count_cursors > 0)
	{
		check_flag(cor);
		if (cor->flag.dump64 == 0 && cor->flag.dump32 == 0)
			ft_printf("cor->cycle: %d\n", cor->cycle); //// Delete becouse unusage in original program
		game_in_cycle(cor);
		cor->cycle++;
		cor->cycles_after_check++;
		if (cor->cycles_to_die == cor->cycles_after_check
		|| cor->cycles_to_die <= 0)
			proverka(cor);
	}
	return (1);
}