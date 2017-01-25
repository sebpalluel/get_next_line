
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:27:52 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/25 19:32:37 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <fcntl.h>

void	 process_file_input(int fd, char *argv, char *line)
{
	fd = open(argv, O_RDONLY);
	printf("fd main %d\n",fd);
	while (get_next_line(fd, &line) == 1)
		ft_putendl(line);
	close(fd);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line = NULL;

	if (argc == 1)
		fd = 0;
	if (argc == 2)
		process_file_input(fd, argv[1], line);
	if (argc == 3)
	{
		process_file_input(fd, argv[1], line);
		process_file_input(fd, argv[2], line);
	}
	free(line);
	return (1);
}

