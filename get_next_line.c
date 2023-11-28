/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:46:03 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/28 18:30:32 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	calculate_len_of_linked_list_strs(t_list *list)
{
	size_t	res_len;
	t_node	*curr;

	curr = list->head;
	res_len = 0;
	while (curr)
	{
		res_len += curr->content_len;
		curr = curr->next;
	}
	return (res_len);
}

char	*linked_list_str_join(t_list *list)
{
	t_node	*curr;
	size_t	l;
	size_t	i;
	size_t	j;
	char	*res;

	l = calculate_len_of_linked_list_strs(list);
	res = malloc(sizeof(char) * (l + 1));
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

t_list	*read_line(int fd, int cl, t_file *f, char buff[BUFFER_SIZE])
{
	ssize_t	sz;
	t_list	*list;

	list = init_list(f, buff);
	if (!list)
		return (0);
	while (cl == f->line)
	{
		sz = read(fd, buff, BUFFER_SIZE);
		if (sz <= 0)
		{
			f->file_ended = 1;
			free_linked_list(list);
			return (0);
		}
		if (!create_new_node(sz, f, buff, list))
		{
			free_linked_list(list);
			return (0);
		}
		if (sz < BUFFER_SIZE)
			f->file_ended = 1;
	}
	return (list);
}

static void	free_leftovers(t_file *f)
{
	if (f->leftovers)
	{
		free(f->leftovers);
		f->leftovers = NULL;
	}
}

char	*get_next_line(int fd)
{
	static t_file	f;
	t_list			*list;
	char			*res;
	char			buff[BUFFER_SIZE];

	if (BUFFER_SIZE <= 0 || fd == -1 || f.file_ended)
	{
		free_leftovers(&f);
		return (0);
	}
	list = read_line(fd, f.line, &f, buff);
	if (!list)
	{
		free_leftovers(&f);
		return (0);
	}
	res = linked_list_str_join(list);
	if (!res && f.leftovers)
		free_leftovers(&f);
	free_linked_list(list);
	if (f.file_ended)
		free_leftovers(&f);
	return (res);
}
