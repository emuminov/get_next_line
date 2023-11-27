/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:46:03 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/27 15:06:27 by emuminov         ###   ########.fr       */
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

void	create_leftovers(char *buff, ssize_t index, ssize_t size, t_file *file)
{
	char	*res;
	ssize_t	i;

	res = malloc(sizeof(char) * (size - index));
	if (!res)
	{
		if (file->leftovers)
			free(file->leftovers);
		file->leftovers = NULL;
		return ;
	}
	i = 0;
	while ((i + 1) < (size - index))
	{
		res[i] = buff[index + i + 1];
		i++;
	}
	res[i] = '\0';
	if (file->leftovers)
		free(file->leftovers);
	file->leftovers = res;
	file->leftovers_len = i;
}

char	*create_node_content(ssize_t size, char *buff, t_file *file, t_node *node)
{
	char	*res;
	ssize_t	i;

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (0);
	i = 0;
	while (buff[i] && buff[i] != '\n' && i < size)
	{
		res[i] = buff[i];
		i++;
	}
	if (buff[i] == '\0')
		file->file_ended = 1;
	else if (buff[i] == '\n')
	{
		create_leftovers(buff, i, size, file);
		res[i++] = '\n';
		file->line++;
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

t_node	*create_new_node(ssize_t size, t_file *file, char *buff, t_linked_list *list)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		free_linked_list(list);
		free(buff);
		return (0);
	}
	if (!create_node_content(size, buff, file, node))
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

t_linked_list	*init_linked_list(t_file *file)
{
	t_linked_list	*list;
	t_node			*node;
	list = malloc(sizeof(t_linked_list)); if (!list)
	{
		if (file->leftovers)
			free(file->leftovers);
		return (0);
	}
	list->head = NULL;
	list->tail = NULL;
	if (file->leftovers)
	{
		node = create_new_node(file->leftovers_len, file, file->leftovers, list);
		if (!node)
		{
			if (file->leftovers)
				free(file->leftovers);
			free(list);
			return (0);
		}
	}
	return (list);
}

t_linked_list	*read_line(int fd, int current_line, t_file *file, char buff[BUFFER_SIZE])
{
	ssize_t 		size;
	t_linked_list 	*list;

	list = init_linked_list(file);
	if (!list)
		return (0);
	while (current_line == file->line)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size <= 0)
			return (0);
		if (!create_new_node(size, file, buff, list))
		{
			free_linked_list(list);
			return (0);
		}
	}
	return (list);
}

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
		return (0);
	}
	list = read_line(fd, file.line, &file, buff);
	if (!list)
	{
		if (file.leftovers)
			free(file.leftovers);
		return (0);
	}
	res = linked_list_str_join(list);
	if (!res && file.leftovers)
		free(file.leftovers);
	free_linked_list(list);
	return (res);
}
