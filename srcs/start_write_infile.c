/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_write_infile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkorniie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:15:14 by vkorniie          #+#    #+#             */
/*   Updated: 2018/11/08 13:15:16 by vkorniie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

int		if_not_cmd(char *ptr, t_c *p, int i, int k)
{
	char *p2;

	while (ft_isalnum(ptr[k]) || ptr[k] == '_')
		k++;
	if (ptr[k] == ':')
	{
		p->checker2 = 10;
		if ((p2 = ft_strstr(ptr + k, g_optab[i].c_name)))
		{
			p->checker2 = 42;
			return (1);
		}
	}
	return (0);
}

void	count_comma(t_c *p, int j)
{
	while (p->line[++j])
	{
		if (p->line[j] == ',')
			p->counter++;
		if (p->line[j] == ',' && p->line[j + 1] == ',')
			error(8);
	}
}

t_cmd	*find_label(t_cmd *t, char *label)
{
	t_cmd			*temp;
	t_label			*tl;

	temp = t;
	while (temp)
	{
		tl = temp->label;
		while (tl)
		{
			if (!ft_strcmp(label, tl->label))
				return (temp);
			tl = tl->next;
		}
		temp = temp->next;
	}
	return (NULL);
}

void	find_this_label(t_c *p, t_cmd *t, t_args *ar)
{
	t_cmd			*temp;

	if (!(temp = find_label(p->cmd_p, ar->label)))
	{
		if (p->tmp && !ft_strcmp(ar->label, p->tmp->label))
		{
			temp = p->cmd_p;
			while (temp->next)
				temp = temp->next;
			ar->ar_n = temp->size_before + temp->cmd_s - t->size_before;
			return ;
		}
		else
		{
			printf("label = %s | cmd->number = %d\n", ar->label, t->number);
			error(15);
		}
	}
	ar->ar_n = temp->size_before - t->size_before;
	printf("label = %s. temp->number = %d t->cmd_s = %d temp->size_before = %d this->size_before = %d | ar->ar_n = %d\n", ar->label,temp->number,t->cmd_s, temp->size_before, t->size_before, ar->ar_n);
}

void	find_label_instruct(t_c *p)
{
	t_cmd	*temp;
	t_args	*argum;

	temp = p->cmd_p;
	while (temp)
	{
		argum = temp->args;
		while (argum)
        {
			if (argum->label) {

			    ft_printf("%s\n", g_optab[temp->number].c_name);
                find_this_label(p, temp, argum);
            }
			argum = argum->next;
		}
		temp = temp->next;
	}
}
