/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:46:03 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/26 23:12:46 by emuminov         ###   ########.fr       */
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

size_t	ft_strlen(char *str)
{
	size_t	l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

char	*create_leftovers(char *content, ssize_t index)
{
	ssize_t	i;
	char	*res;

	res = malloc(ft_strlen(&content[index + 1]));
	if (!res)
		return (0);
	i = 0;
	while (content[i + index + 1])
	{
		res[i] = content[index + i + 1];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*create_node_content(ssize_t size, char *buff, t_file *file)
{
	char	*content;
	size_t	i;

	content = malloc(size);
	if (!content)
		return (0);
	i = 0;
	while (buff[i] && buff[i] != '\n' && i < BUFFER_SIZE)
	{
		content[i] = buff[i];
		i++;
	}
	if (buff[i] == '\0')
		file->file_ended = 1;
	else if (buff[i] == '\n')
	{
		file->leftovers = create_leftovers(content, i);
		content[i++] = '\n';
		file->line++;
	}
	content[i] = '\0';
	return (content);
}

t_linked_list	*create_new_node(char *content, t_linked_list *list)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		// free list
		free(content);
		return (0);
	}
	node->content = content;
	node->next = NULL;
	node->content_len = ft_strlen(content);
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
		return (list);
	}
	list->tail->next = node;
	list->tail = node;
	return (list);
}

t_linked_list	*read_line(int fd, int current_line, t_file *file, char buff[BUFFER_SIZE])
{
	char			*content;
	ssize_t 		size;
	t_linked_list 	*list;

	list = malloc(sizeof(t_linked_list));
	if (!list)
		return (0);
	list->head = NULL;
	list->tail = NULL;
	if (file->leftovers)
	{
		content = create_node_content(ft_strlen(file->leftovers), file->leftovers, file);
		create_new_node(content, list);
	}
	while (current_line == file->line)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size <= 0)
			return (0);
		content = create_node_content(size, buff, file);
		if (!content)
		{
			// free linked list
			return (0);
		}
		if (!create_new_node(content, list))
			return (0);
	}
	return (list);
}
// \n\0
// hehe\nheh\0

// jaksyhdjihasd\nkjhasjkdha\0
char	*get_next_line(int fd)
{
	static t_file	file;
	t_linked_list	*list;
	char			*res;
	char			buff[BUFFER_SIZE];

	if (BUFFER_SIZE <= 0 || fd == -1)
	{
		if (file.leftovers)
			free(file.leftovers);
		// free linked list
		return (0);
	}
	list = read_line(fd, file.line, &file, buff);
	if (!list)
	{
		if (file.leftovers)
			free(file.leftovers);
		return (0);
	}
	// find and assign leftovers to file
	res = linked_list_str_join(list);
	if (!res && file.leftovers)
		// free linked list
		free(file.leftovers);
	printf("%zu\n", ft_strlen(res));
	// free linked list
	return (res);
}
