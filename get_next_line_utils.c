/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:46:08 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/29 15:00:19 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	create_leftovers(char *buff, ssize_t index, ssize_t sz, t_file *f)
{
	char	*res;
	ssize_t	i;

	res = malloc(sizeof(char) * (sz - index));
	if (!res)
	{
		if (f->leftovers)
			free(f->leftovers);
		f->leftovers = NULL;
		return ;
	}
	i = 0;
	while ((i + 1) < (sz - index))
	{
		res[i] = buff[index + i + 1];
		i++;
	}
	res[i] = '\0';
	if (f->leftovers)
		free(f->leftovers);
	f->leftovers = res;
	f->leftovers_len = i;
}

static char	*create_content(ssize_t sz, char *buff, t_file *f, t_node *node)
{
	char	*res;
	ssize_t	i;

	res = malloc(sizeof(char) * (sz + 1));
	if (!res)
		return (0);
	i = 0;
	while (buff[i] && i < sz)
	{
		res[i] = buff[i];
		if (buff[i] == '\n')
		{
			create_leftovers(buff, i++, sz, f);
			f->line++;
			break ;
		}
		i++;
	}
	res[i] = '\0';
	node->content = res;
	node->content_len = i;
	return (res);
}

void	free_linked_list(t_list *list)
{
	t_node	*next;
	t_node	*curr;

	curr = list->head;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
			free(curr->content);
		free(curr);
		curr = next;
	}
	free(list);
}

t_node	*create_new_node(ssize_t sz, t_file *f, char *buff, t_list *list)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		free_linked_list(list);
		return (0);
	}
	if (!create_content(sz, buff, f, node))
	{
		free_linked_list(list);
		return (0);
	}
	node->next = NULL;
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
		return (node);
	}
	list->tail->next = node;
	list->tail = node;
	return (node);
}

t_list	*init_list(t_file *f)
{
	t_list	*list;
	t_node	*node;

	list = malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->head = NULL;
	list->tail = NULL;
	if (f->leftovers)
	{
		node = create_new_node(f->leftovers_len, f, f->leftovers, list);
		if (!node)
		{
			if (f->leftovers)
				free(f->leftovers);
			free(list);
			return (0);
		}
	}
	return (list);
}
