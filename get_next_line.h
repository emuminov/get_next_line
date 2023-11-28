/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:46:06 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/28 15:49:50 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 3

typedef struct s_node {
	struct s_node	*next;
	char			*content;
	size_t			content_len;
}	t_node;

typedef struct s_list {
	t_node	*head;
	t_node	*tail;
}	t_list;

typedef struct s_file {
	int		line;
	int		file_ended;
	char	*leftovers;
	int		leftovers_len;
}	t_file;

char	*get_next_line(int fd);
void	free_linked_list(t_list *list);
t_node	*create_new_node(ssize_t sz, t_file *f, char *buff, t_list *ls);
t_list	*init_list(t_file *f, char *buff);

#endif
