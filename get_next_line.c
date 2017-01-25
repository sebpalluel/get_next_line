/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:46:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/25 18:05:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int 				init_fd(t_fd *fd_elem, int fd)
{
	if (!(fd_elem = (t_fd *)malloc(sizeof(t_fd))))
		return (0);
	fd_elem->fd = fd;
	fd_elem->buffer = NULL;
	return (1);
}

int					get_fd(int fd, t_list **fd_lst)
{
	t_fd			*fd_new = NULL;

	if (!(fd_new = (t_fd *)ft_memalloc(sizeof(t_fd))) || \
			!(init_fd(fd_new, fd)))
		return (0);
	ft_lstaddend(fd_lst, ft_lstnew(fd_new, sizeof(fd_new)));
	if (FD(fd_lst)->fd != fd)
		return (get_fd(fd, &(*fd_lst)->next));
	return (1);
}

int 				buffer_from_fd(t_list **fd_lst, char **line)
{
	int				ret;
	//char			*str;


}

int					get_next_line(const int fd, char **line)
{
	static t_list	**fd_lst = NULL;

	*fd_lst = NULL;
	if (fd < 0 || fd > FD_MAX || line == NULL)
		return (READ_ERR);
	if(!(get_fd(fd, fd_lst)))
		return (READ_ERR);
	return (buffer_from_fd(fd_lst, line));
}
