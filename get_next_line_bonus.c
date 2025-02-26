/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:36:15 by emuminov          #+#    #+#             */
/*   Updated: 2023/12/04 02:12:58 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	linked_list_calculate_content_len(t_list *list)
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

char	*linked_list_content_join(t_list *list)
{
	t_node	*curr;
	size_t	l;
	size_t	i;
	size_t	j;
	char	*res;

	l = linked_list_calculate_content_len(list);
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

void	*cleanup(t_list *list, char *buff, t_file *f, int free_leftovers)
{
	if (buff)
		free(buff);
	if (f && f->leftovers && (f->file_ended || free_leftovers))
	{
		free(f->leftovers);
		f->leftovers = NULL;
	}
	if (list)
		linked_list_free(list);
	return (0);
}

t_list	*read_line(int fd, int cl, t_file *f, char *buff)
{
	ssize_t	sz;
	t_list	*list;
	size_t	i;

	list = linked_list_init(f);
	if (!list)
		return (0);
	while (cl == f->line && !f->file_ended)
	{
		i = 0;
		while (i < BUFFER_SIZE + 1)
			buff[i++] = 0;
		sz = read(fd, buff, BUFFER_SIZE);
		if (sz == -1 || (sz == 0 && !list->head))
		{
			f->file_ended = 1;
			return (cleanup(list, NULL, NULL, 0));
		}
		else if (sz == 0 && list->head)
			f->file_ended = 1;
		if (!linked_list_new_node(sz, f, buff, list))
			return (cleanup(list, NULL, NULL, 0));
	}
	return (list);
}

char	*get_next_line(int fd)
{
	static t_file	files[4096];
	t_list			*list;
	char			*res;
	char			*buff;

	if (fd == -1 || fd > 4096)
		return (0);
	if (BUFFER_SIZE <= 0 || files[fd].file_ended)
		return (cleanup(NULL, NULL, &files[fd], 1));
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (cleanup(NULL, NULL, &files[fd], 1));
	list = read_line(fd, files[fd].line, &files[fd], buff);
	if (!list)
		return (cleanup(NULL, buff, &files[fd], 1));
	res = linked_list_content_join(list);
	cleanup(list, buff, &files[fd], 0);
	return (res);
}
