/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_buff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 04:25:06 by dcapers           #+#    #+#             */
/*   Updated: 2020/12/20 03:52:11 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "asm_op.h"
#include "asm_errors.h"
#include "libft.h"

void			resize_buff(t_parser *p)
{
	p->code_size += CHAMP_MAX_SIZE;
	if (!(p->code = (char *)realloc(p->code, p->code_size + STATEMENT_LEN)))
		kill_exe(ERR_STR_INIT);
}

void			update_types_code(int8_t *types_code, int8_t type, int arg_num)
{
	int		arg_code;

	arg_code = (type == T_DIR ? DIR_CODE : 
			(type == T_REG ? REG_CODE : IND_CODE));
	(*types_code) |= (arg_code << 2 * (4 - arg_num - 1));
}

t_op			*get_op(char *name)
{
	int			op_num;
	int			i;

	op_num = sizeof(g_op) / sizeof(t_op);
	i = 0;
	while (i < op_num)
	{
		if (!ft_strcmp(g_op[i].name, name))
			return (&g_op[i]);
		i++;
	}
	return (NULL);
}
