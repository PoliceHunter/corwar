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
		if (process->live_last_cycle == -1 || cor->cycles_to_die <= 0) // && is_died(cor, process))
		{
			int i = process->id;
			int g = process->pos;
			remove_from_vec(&cor->process, index);
			if (cor->flag.visual)
			{
				//ft_printf("killed curs: %d pos %d\n", i, g);
				//ft_printf("cor->cycle: %d\n", cor->cycle); //// Delete becouse unusage in original program
			}
			cor->count_cursors--;
			index--;
		}
		else
			process->live_last_cycle = -1; //// Проверить на правильность ипспользования
	}
}

void 			make_check(t_cor *cor)
{
    cor->count_check++;
	kill_caretka(cor);
	if (cor->count_lives >= NBR_LIVE || cor->count_check == MAX_CHECKS)
	{
		cor->cycles_to_die -= CYCLE_DELTA;
		cor->count_check = 0;
	}
	cor->cycles_after_check = 0;
	cor->count_lives = 0;
}

int 			process_game_logic(t_cor *cor)
{
	cor->cycles_to_die = CYCLE_TO_DIE;
	while (cor->count_cursors > 0)
	{
		if (cor->flag.visual && cor->cycles_after_check == 0)
		{
			//ft_printf("---beg count_cursors: %d\n", cor->count_cursors);
		}
		check_flag(cor);
		cor->cycle++;
		game_in_cycle(cor);
		cor->cycles_after_check++;
		if (cor->flag.visual && cor->cycles_after_check == cor->cycles_to_die - 1)
		{
			//ft_printf("cycles_to_die: %d\n", cor->cycles_to_die); //// Delete becouse unusage in original program
			//ft_printf("count_lives: %d\n", cor->count_lives);
			//ft_printf("count_cursors: %d\n", cor->count_cursors);
			//ft_printf("cor->cycle: %d\n", cor->cycle); //// Delete becouse unusage in original program
		}
		if (cor->cycles_to_die == cor->cycles_after_check
		|| cor->cycles_to_die <= 0)
            make_check(cor);
		/*if (cor->count_cursors > 20000)
			return (1);*/
	}
	return (1);
}