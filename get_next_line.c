/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:46:03 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/25 16:23:42 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_linked_list	*linked_list_append(t_linked_list *list, t_node *node)
{
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

t_node	*create_new_node(t_linked_list *list, size_t size, char *str)
{
	t_node	*node;
	char	*content;
	size_t	i;

	content = malloc(size);
	if (!content)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n' && i < BUFFER_SIZE)
	{
		content[i] = str[i];
		i++;
	}
	if (str[i] == '\0')
		list->file_ended = 1;
	else if (str[i] == '\n')
	{
		content[i++] = '\n';
		list->line++;
	}
	content[i + 1] = '\0';
	node = malloc(sizeof(t_node));
	if (!node)
	{
		free(content);
		return (0);
	}
	node->content = content;
	node->next = NULL;
	node->content_len = i;
	linked_list_append(list, node);
	return (node);
}

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

#include <stdio.h>
char	*get_next_line(int fd)
{
	static t_linked_list	line_list;
	t_node					*line_node;
	char					buff[BUFFER_SIZE];
	ssize_t					size;
	size_t					current_line;

	if (BUFFER_SIZE <= 0 || fd == -1)
		return (0);
	current_line = line_list.line;
	while (current_line == line_list.line)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size <= 0)
			return (0);
		line_node = create_new_node(&line_list, size, buff);
		if (!line_node)
			return (0);
	}
	t_node *curr = line_list.head;
	while (curr)
	{
		printf("%s\n", curr->content);
		printf("%zu\n", curr->content_len);
		printf("\n");
		curr = curr->next;
	}
	printf("%zu\n", line_list.line);
	char *res = linked_list_str_join(&line_list);
	printf("%s\n", res);
	return "1";
}
