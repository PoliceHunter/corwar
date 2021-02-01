/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjohnsie <mjohnsie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:40:59 by dcapers           #+#    #+#             */
/*   Updated: 2021/01/29 20:13:23 by mjohnsie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"
#include "op.h"
#include "libft.h"

char			*take_lebel(char *s)
{
	char		**split;
	int			len;

	len = 0;
	split = ft_strsplit(s, ',');
	return (split[0]);
}

t_label			*find_label(t_label *label, char *name)
{
	while (label)
	{
		if (!ft_strcmp(take_lebel(label->name), take_lebel(name)))
			return (label);
		label = label->next;
	}
	return (label);
}

void			push_mention(t_label *label, t_mention *mention)
{
	if (label->mention_last)
		label->mention_last->next = mention;
	label->mention_last = mention;
	if (!label->mention)
		label->mention = mention;
}

t_mention		*create_mention(int32_t op_pos, int32_t pos,
			t_token *t, size_t size)
{
	t_mention	*mention;

	if (!(mention = (t_mention *)malloc(sizeof(t_mention))))
		kill_exe(ERR_MENTION_INIT);
	mention->pos = pos;
	mention->op_pos = op_pos;
	mention->row = t->row;
	mention->col = t->col;
	mention->size = size;
	mention->next = NULL;
	return (mention);
}

t_label			*create_label(char *name, int32_t pos)
{
	t_label		*label;

	if (!(label = (t_label *)malloc(sizeof(t_label))))
		kill_exe(ERR_LABEL_INIT);
	label->name = name;
	label->mention = NULL;
	label->mention_last = NULL;
	label->op_pos = pos;
	label->next = NULL;
	return (label);
}
