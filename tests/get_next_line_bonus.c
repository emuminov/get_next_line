/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 01:41:45 by emuminov          #+#    #+#             */
/*   Updated: 2023/12/04 01:49:03 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "../get_next_line.h"

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
	} \
}

int	main(void)
{
	int fd1 = open("tests/empty_file.txt", O_RDONLY);
	int fd2 = open("tests/file.txt", O_RDONLY);
	int fd3 = open("tests/one_line_file.txt", O_RDONLY);
	int fd4 = open("tests/small_file.txt", O_RDONLY);
	int fd5 = open("tests/super_small_file.txt", O_RDONLY);
	get_next_line_test(fd1);
	get_next_line_test(fd2);
	get_next_line_test(fd3);
	get_next_line_test(fd4);
	get_next_line_test(fd5);
	get_next_line_test(fd1);
	get_next_line_test(fd2);
	get_next_line_test(fd3);
	get_next_line_test(fd4);
	get_next_line_test(fd5);
	get_next_line_test(fd1);
	get_next_line_test(fd2);
	get_next_line_test(fd3);
	get_next_line_test(fd4);
	get_next_line_test(fd5);
	// get_next_line_test(fd);
	// get_next_line_test(fd);
	// get_next_line_test(fd);
	// get_next_line_test(fd);
	// get_next_line_test(fd);
	// get_next_line_test(fd);
	// get_next_line_test(fd);
	// get_next_line_test(fd);
	// get_next_line_test(fd);
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	close(fd5);
}
