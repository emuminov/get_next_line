/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:26:15 by emuminov          #+#    #+#             */
/*   Updated: 2023/11/28 00:04:25 by emuminov         ###   ########.fr       */
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
	else \
	{ \
		printf("End of the file.\n"); \
		exit(0); \
	} \
	free(test); \
}

int	main(void)
{
	int fd = open("tests/file.txt", O_RDONLY);
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
