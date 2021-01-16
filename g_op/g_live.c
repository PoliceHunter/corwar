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

//Циклы до исполнения 10

void				live(t_cor *vm, t_process *proc)
{
//	//переменные
//	//id игрока - int32_t player_id;
//
//	//движение дальше
//	// шаг курсора - прибавляем стандартный
//
//	//получение данных
//	//получаем 1 агрумент T_DIR из операции - это id игрока - проверяем, что этот номер совпадает с номером игрока
//
//	//изменения в структуре каретки
//	// в инт "ласт лайв" записываем текущий цикл
//
//	//изменения в общей структуре vm
//	//нам в структуре нужен инт последнего игрока "live" - перезаписываем номер этого игрока
//	//перезаписываем в структуре кол-во "live"
//
//	//печать
//	//в зависимости от флага выводим в печать - id курсора, id игрока, ft_printf("P %4d | live %d\n")
//	//др флаг - ft_printf("Player %d (%s) is said to be alive\n",
//	//			  player_id,
//	//			  player_name);
}
//
//
//
//void				op_live(t_cor *vm)
//{
//	int32_t		player_id;
//	t_player	*player;
//
//
//	cursor->step += OP_CODE_LEN;
//	player_id = get_op_arg(vm, cursor, 1, false);
//	vm->lives_num++;
//	cursor->last_live = vm->cycles;
//	player = NULL;
//	if (player_id <= -1 && player_id >= -((int32_t)vm->players_num))
//	{
//		player = vm->players[INDEX(FT_ABS(player_id))];
//		player->last_live = vm->cycles;
//		player->current_lives_num++;
//		vm->last_alive = player;
//		if (vm->vs)
//		{
//			vm->vs->map[cursor->pc].wait_cycles_live = CYCLE_TO_WAIT;
//			vm->vs->map[cursor->pc].player_live = player;
//		}
//	}
//	if (vm->log & OP_LOG)
//		log_live(cursor->id, player_id);
//	if (vm->log & LIVE_LOG && player)
//		log_live_msg(FT_ABS(player_id), player->name);
//}
//
//////
//void	carriage_live_hub(t_carriage *carriage, unsigned char *arena)
//{
//	carriage->jump =
//			calculate_jump(carriage->current_opcode, arena, carriage->current_position);
//	carriage_live(carriage, extract_4_bytes(carriage->current_position + 1));
//	carriage_jump(carriage);
//}
//
//void	valid_id_player(t_players **players, int id)
//{
//	int		i;
//	int		l_flag;
//
//	i = 0;
//	l_flag = save_l_flag(NULL);
//	if (l_flag != 1)
//		return ;
//	while (i < 4 && players[i] != NULL)
//	{
//		if (players[i]->id == (id * -1))
//		{
//			ft_printf("A process shows that player %d (%s) is alive\n",
//					  players[i]->id, players[i]->name);
//			break ;
//		}
//		i++;
//	}
//}
//
///*
//** @desc If 'live' command is executed by carriage,
//** @desc then it's cycle that it was reported live is updated.
//** @desc It also reports this to function that counts overall
//** @desc how many times 'live' has been called in last
//** @desc cycles_do_die cycles.
//** @param t_carriage *carriage - carriage structure
//** @param int id - id of player whose carriage reported it 'live'
//** @return void
//*/
//
//void	carriage_live(t_carriage *carriage, int id)
//{
//	int			i;
//	t_players	**players;
//
//	i = 0;
//	players = save_players(NULL);
//	carriage->cycle_live_reported = number_of_cycles(0);
//	number_of_live_performed(1);
//	last_player_live_id(id);
//	valid_id_player(players, id);
//}