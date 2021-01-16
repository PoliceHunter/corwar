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

#include "corwar.h"
#include "g_corewar_op.h"

void 			kill_caretka(t_cor *cor, t_process *process)
{
	//1 - удалить из структуры данную каретку, очистить память
	cor->count_cursors--;
}

void 			proverka(t_cor *cor)
{
	int 		index;
	int 		mem;
	t_process	*process;

	index = 0;
	mem = cor->count_cursors;
	while (index < mem)
	{
		process = get_from_vec(&cor->process, index);;
		if (process->live_last_cycle > cor->cycles_to_die)
			kill_caretka(cor, process);
		else
			process->live_last_cycle = 0;
		index++;
	}
	cor->count_lives = 0;
	cor->count_check++;
}

int 			count_minus(t_cor *cor)
{
	int			minus;

	minus = 0;
	if (cor->count_lives >= NBR_LIVE || cor->count_check == MAX_CHECKS)
	{
		minus = CYCLE_DELTA;
		cor->count_check = 0;
	}
	return (minus);
}

int 			game_logic(t_cor *cor)
{
	int32_t		one_cycle_to_die;
	int 		minus;

	int f = 0;

	cor->cycles_to_die = CYCLE_TO_DIE;
	while (cor->count_cursors != 0 && f++ < 2)
	{
		while (cor->cycles_to_die > 0  && f++ < 2) //перепроверю
		{
			one_cycle_to_die = 0;
			ft_printf("\ncor->cycles_to_die: %d\n", cor->cycles_to_die);
			while (one_cycle_to_die++ < 50) //cor->cycles_to_die
			{
				ft_printf("\ncor->cycle: %d", cor->cycle);
				ft_printf("\none_cycle_to_die: %d\n", one_cycle_to_die - 1);
				game_in_cycle(cor);
				cor->cycle++;
			}
			proverka(cor);
			minus = count_minus(cor);
			cor->cycles_to_die = cor->cycles_to_die - minus;
			if ((cor->flag.dump32 > 0 && cor->cycle == cor->flag.dump32)|| (cor->flag.dump64 > 0 && cor->cycle == cor->flag.dump64))
			{
				//print  // - вывести состояние текущего цикла
				return (2);
			}
		}
		if (cor->cycles_to_die <= 0)
		{
			game_in_cycle(cor);
			proverka(cor);
		}
	}
	return (1);
}