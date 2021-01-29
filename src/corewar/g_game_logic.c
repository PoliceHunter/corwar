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

void 			kill_caretka(t_cor *cor, t_process *proc, int index)
{
	//1 - удалить из структуры данную каретку, очистить память
	//free(proc); //возможно не надо
	remove_from_vec(&cor->process, index);
	cor->count_cursors--;
	proc = NULL;
}

void 			proverka(t_cor *cor)
{
	int 		index;
	//int 		mem;
	t_process	*process;

	index = 0;
	//mem = cor->count_cursors;
	while (index < cor->count_cursors)
	{
		process = get_from_vec(&cor->process, index);
		//ft_printf("process->player_id: %d\n", process->player_id);
		//ft_printf("process->live_last_cycle: %d\n", process->live_last_cycle);
		//ft_printf("cor->cycles_to_die: %d\n", cor->cycles_to_die);
		//ft_printf("if (process->live_last_cycle > cor->cycles_to_die)\n");
		if (process->live_last_cycle == -1)
		{
			kill_caretka(cor, process, index);
			index--;
		}
		else
			process->live_last_cycle = -1;
		index++;
	}
	cor->count_lives = 0; //
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

	t_process *proc1;
	t_process *process2;
	int f = -1;//\


	cor->cycles_to_die = CYCLE_TO_DIE;
	while (cor->count_cursors != 0) //&& f++ < 2)
	{
		//ft_printf("\ncor->cycles_to_die: %d\n", cor->cycles_to_die);
		while (cor->cycles_to_die > 0) // && f++ < 2) //перепроверю
		{
			one_cycle_to_die = 0;
			//ft_printf("\ncor->cycles_to_die: %d\n", cor->cycles_to_die);
			while (one_cycle_to_die++ < cor->cycles_to_die) // && ++f < 928) //cor->cycles_to_die
			{
				if (cor->flag.dump64 == 0 && cor->flag.dump32 == 0)
					ft_printf("cor->cycle: %d\n", cor->cycle);
			//	ft_printf("\none_cycle_to_die: %d\n", one_cycle_to_die - 1);
				game_in_cycle(cor);
				cor->cycle++;
				proc1 = get_from_vec(&cor->process, 0);
				process2 = get_from_vec(&cor->process, 1);
				if (check_flag(cor) == 1)
					return (1);
			}
			//ft_printf("\nproverka, cycle = %d\n", cor->cycle);
			//ft_printf("count_lives = %d count_check = %d \n", cor->count_lives, cor->count_check);
			minus = count_minus(cor);
			proverka(cor);
			cor->cycles_to_die = cor->cycles_to_die - minus;
			//if (cor->cycles_to_die < 50)
			//	minus = minus;
			if ((cor->flag.dump32 > 0 && (int) cor->cycle == cor->flag.dump32)|| (cor->flag.dump64 > 0 && (int) cor->cycle == cor->flag.dump64))
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