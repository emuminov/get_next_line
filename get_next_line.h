/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:46:06 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/27 15:02:42 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 13

typedef struct s_node {
	struct s_node	*next;
	char 			*content;
	size_t			content_len;
}	t_node;

typedef struct s_linked_list {
	t_node	*head;
	t_node	*tail;
}	t_linked_list;

typedef struct s_file {
	int		line;
	int		file_ended;
	char	*leftovers;
	int		leftovers_len;
}	t_file;

char	*get_next_line(int fd);

#endif
