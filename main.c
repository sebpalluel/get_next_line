/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:27:52 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/23 14:57:29 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

typedef struct		s_fdp
{
	int				fd;
	int				ret;
}					t_fdp;

void	gnl(int fd, char **line)
{
	int		ret;

	while ((ret = get_next_line(fd, line)))
	{
		ft_putendl(*line);
		free(*line);
	}
	close(fd);
}

int		still_reading(t_fdp *fds, int length)
{
	for (int i = 0; i < length; i++)
		if (fds[i].ret == 1)
			return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdp	fds[256] = {{ 0, 1 }};
	char	*line = NULL;

	if (argc == 1)
		gnl(0, &line);
	else if (argc == 2)
		gnl(open(argv[1], O_RDONLY), &line);
	else
	{
		for (int i = 0; i < argc - 1; i++)
			fds[i].fd = open(argv[i + 1], O_RDONLY);
		while (still_reading(fds, argc))
		{
			for (int i = 0; i < argc - 1; i++)
			{
				fds[i].ret = get_next_line(fds[i].fd, &line);
				if (fds[i].ret == 1)
				{
					ft_putendl(line);
					free(line);
				}
			}
		}
		for (int i = 0; i < argc - 1; i++)
			close(fds[i].fd);
	}
	while (42);
	return (0);
}
// valgrind --tool=memcheck --leak-check=full app arg1 arg2
