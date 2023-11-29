/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:26:15 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/29 21:12:08 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "../get_next_line.h"

#ifndef TEST_FILE
# define TEST_FILE "tests/file.txt"
#endif
#define get_next_line_test(fd) \
{ \
	char *test = get_next_line(fd); \
	if (test) \
	{ \
		printf("%s", test); \
		free(test); \
	} \
	else \
	{ \
		printf("File ended.\n"); \
		exit(0); \
	} \
}

int	main(void)
{
	int fd = open(TEST_FILE, O_RDONLY);
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
