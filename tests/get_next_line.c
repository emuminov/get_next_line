/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:26:15 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/29 19:53:34 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "../get_next_line.h"

#define get_next_line_test(fd) \
{ \
	char *test = get_next_line(fd); \
	if (test) \
		printf("%s", test); \
	free(test); \
}

int	main(void)
{
	int fd = open("tests/small_file.txt", O_RDONLY);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	get_next_line_test(fd);
	close(fd);
}
