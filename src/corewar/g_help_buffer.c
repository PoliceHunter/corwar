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

void make_buffer_codes(t_cor *cor)
{
	int	i;

	i = 0;
	cor->buffer_codes = (int *)malloc(sizeof(int) * 4);
	while (i < 4)
	{
		cor->buffer_codes[i] = 0;
		i++;
	}
	cor->buffer_counter = 0;
	i = 0;
	cor->buffer_sizes = (int *)malloc(sizeof(int) * 4);
	while (i < 4)
	{
		cor->buffer_sizes[i] = 0;
		i++;
	}
}

void	fill_buffer_with_zeros(t_cor *cor)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cor->buffer_codes[i] = 0;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		cor->buffer_sizes[i] = 0;
		i++;
	}
	cor->buffer_counter = 0;
}

void	check_flag(t_cor *cor)
{
	if (cor->flag.dump64 == (int) cor->cycle && cor->flag.dump64 != 0)
		print_arena(cor->map, 64);
	if (cor->flag.dump32 == (int) cor->cycle && cor->flag.dump32 != 0)
		print_arena(cor->map, 32);
}

void	*get_from_vec1(t_vector *vec, int index)
{
	if (index >= vec->size)
		return (NULL);
	return (vec->data + (index * vec->elem_size));
}