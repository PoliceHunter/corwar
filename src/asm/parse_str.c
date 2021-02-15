/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:49:21 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/10 10:36:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"
#include "libft.h"

char			*str_join_free(char *s1, char *s2)
{
	char		*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin_by(s1, s2, '\n');
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (res);
}

int				get_sym(char *str, char sym)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sym)
			count++;
		i++;
	}
	return (count);
}

char			*strchr_inc(const char *s, int c, t_parser *p)
{
	while (s[p->col] != '\0')
	{
		if (s[p->col] == (char)c)
			return ((char*)s + p->col);
		p->col++;
	}
	if (s[p->col] == (char)c)
		return ((char*)s + p->col);
	else
		return (NULL);
}

void			parse_str(t_parser *p, char **row, t_token *t)
{
	unsigned	start;
	char		*end;
	size_t		size;

	t->col = p->col;
	t->row = p->row;
	start = ++p->col;
	if (get_sym(*row, '\"') != 2)
		lexical_error(p->row, t->col);
	end = strchr_inc(*row, STR_CHR, p);
	t->content = get_content(p, *row, start);
	while (!end && get_row(p, row) > 0)
	{
		end = strchr_inc(*row, STR_CHR, p);
		t->content = str_join_free(t->content, get_content(p, *row, 0));
	}
	if (!end)
		lexical_error(p->row, t->col);
	p->col++;
	add_token(p, t);
}
