/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:46:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/25 19:20:02 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd 				*init_fd(int fd)
{
	t_fd			*fd_elem = NULL;

	if (!(fd_elem = (t_fd *)malloc(sizeof(t_fd))))
		return (NULL);
	fd_elem->fd = fd;
	fd_elem->buffer = NULL;
	return (fd_elem);
}

int					get_fd(int fd, t_list **fd_lst)
{
	if (!*fd_lst)
		*fd_lst = ft_lstnew(NULL, 0);
	if(!(*fd_lst)->content)
	{
		(*fd_lst)->content = init_fd(fd);
		(*fd_lst)->next = NULL;
	}	
	printf("fd_lst %d\n", FD(fd_lst)->fd);
	if (FD(fd_lst)->fd != fd)
		return (get_fd(fd, &(*fd_lst)->next));
	return (1);
}

int 				buffer_from_fd(t_list **fd_lst, char **line)
{
	int				ret;
	char			*str;

	if (!(str = ft_strnew(BUFF_SIZE)))
		return (READ_ERR);
	while ((ret = read(FD(fd_lst)->fd, str, BUFF_SIZE)) > 0)
	{
		str[ret] = '\0';
		*line = ft_strjoin(*line, str);
	}
	if (ret <= 0)
		return (READ_ERR);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*fd_lst = NULL;

	if (fd < 0 || fd > FD_MAX || line == NULL)
		return (READ_ERR);
	if(!(get_fd(fd, &fd_lst)))
		return (READ_ERR);
	//return (buffer_from_fd(fd_lst, line));
	return (0);
}
