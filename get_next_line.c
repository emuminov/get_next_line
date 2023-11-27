/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:46:03 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/27 15:11:43 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO DELETERTAJKLH DSJKH DKJAHS DKJASG DJHAGS DHJk
#include <stdio.h>
#include "get_next_line.h"

char	*linked_list_str_join(t_linked_list *list)
{
	t_node	*curr;
	size_t	res_len;
	size_t	i;
	size_t	j;
	char	*res;

	curr = list->head;
	res_len = 0;
	while (curr)
	{
		res_len += curr->content_len;
		curr = curr->next;
	}
	res = malloc(sizeof(char) * (res_len + 1));
	if (!res)
		return (0);
	curr = list->head;
	i = 0;
	while (curr)
	{
		j = 0;
		while (j < curr->content_len)
			res[i++] = curr->content[j++];
		curr = curr->next;
	}
	res[i] = '\0';
	return (res);
}

void	create_leftovers(char *buff, ssize_t index, ssize_t sz, t_file *f)
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

char	*create_node_content(ssize_t sz, char *buff, t_file *f, t_node *node)
{
	char	*res;
	ssize_t	i;

	res = malloc(sizeof(char) * (sz + 1));
	if (!res)
		return (0);
	i = 0;
	while (buff[i] && buff[i] != '\n' && i < sz)
	{
		res[i] = buff[i];
		i++;
	}
	if (buff[i] == '\0')
		f->file_ended = 1;
	else if (buff[i] == '\n')
	{
		create_leftovers(buff, i, sz, f);
		res[i++] = '\n';
		f->line++;
	}
	res[i] = '\0';
	node->content = res;
	node->content_len = i;
	return (res);
}

void	free_linked_list(t_linked_list *list)
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

t_node	*create_new_node(ssize_t sz, t_file *f, char *buff, t_linked_list *list)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		free_linked_list(list);
		free(buff);
		return (0);
	}
	if (!create_node_content(sz, buff, f, node))
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

t_linked_list	*init_linked_list(t_file *f)
{
	t_linked_list	*list;
	t_node			*node;

	list = malloc(sizeof(t_linked_list));
	if (!list)
	{
		if (f->leftovers)
			free(f->leftovers);
		return (0);
	}
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

t_linked_list	*read_line(int fd, int cl, t_file *f, char buff[BUFFER_SIZE])
{
	ssize_t			sz;
	t_linked_list	*list;

	list = init_linked_list(f);
	if (!list)
		return (0);
	while (cl == f->line)
	{
		sz = read(fd, buff, BUFFER_SIZE);
		if (sz <= 0)
			return (0);
		if (!create_new_node(sz, f, buff, list))
		{
			free_linked_list(list);
			return (0);
		}
	}
	return (list);
}

char	*get_next_line(int fd)
{
	static t_file	f;
	t_linked_list	*list;
	char			*res;
	char			buff[BUFFER_SIZE];

	if (BUFFER_SIZE <= 0 || fd == -1)
	{
		if (f.leftovers)
			free(f.leftovers);
		return (0);
	}
	list = read_line(fd, f.line, &f, buff);
	if (!list)
	{
		if (f.leftovers)
			free(f.leftovers);
		return (0);
	}
	res = linked_list_str_join(list);
	if (!res && f.leftovers)
		free(f.leftovers);
	free_linked_list(list);
	return (res);
}
