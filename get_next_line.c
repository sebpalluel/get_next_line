/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:46:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/27 23:51:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			copy_buff(int fd, t_fd *fd_tab, char *src, t_char *buffer)
{
	size_t			i;

	i = 0;
	while (src[i])
	{
		if (buffer == NULL)
		{
			fd_tab[fd].buffer = (t_char *)ft_memalloc(sizeof(t_char));
			buffer = fd_tab[fd].buffer;
		}
		else
		{
			buffer->next = (t_char *)ft_memalloc(sizeof(t_char));
			buffer = buffer->next;
		}
		if (buffer == NULL)
			return (0);
		buffer->c = src[i];
		buffer->next = NULL;
		i++;
	}
	return (1);
}

static int			read_buff(int fd, t_fd *fd_tab)
{
	t_char			*buffer;
	char			*src;
	int				ret;

	buffer = fd_tab[fd].buffer;
	while (buffer && buffer->next)
		buffer = buffer->next;
	src = (char *)malloc(sizeof (char) * (BUFF_SIZE));
	if (src == NULL)
		return (-1);
	ft_bzero(src, BUFF_SIZE);
	ret = read(fd, src, BUFF_SIZE - 1);
	if (copy_buff(fd, fd_tab, src, buffer) == 0)
		return (-1);
	free(src);
	return (ret);
}

static void			copy_line(size_t length, t_fd *fd, char **target)
{
	char 			*line;
	t_char			*current;
	t_char			*prev;

	line = ft_strnew(length);
	length = 0;
	current = fd->buffer;
	while (current->c != '\n')
	{
		line[length++] = current->c;
		prev = current;
		current = current->next;
		free(prev);
	}
	prev = current;
	current = current->next;
	free(prev);
	fd->buffer = current;
	*target = line;
}

static int			buffer_has_line(t_fd *fd, char **target)
{
	size_t			length;
	t_char			*current;

	current = fd->buffer;
	if (current == NULL)
		*target = NULL;
	length = 0;
	while (current != NULL && current->c != '\n')
	{
		current = current->next;
		length++;
	}
	if (current != NULL)
	{
		copy_line(length, fd, target);
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_fd		fd_tab[FD_MAX];
	int				ret;

	if (fd < 0 || fd > FD_MAX || line == NULL)
		return (READ_ERR);
	if (buffer_has_line(&fd_tab[fd], line))
		return (READ_OK);
	ret = 1;
	while (!buffer_has_line(&fd_tab[fd], line) && ret > 0)
		ret = read_buff(fd, fd_tab);
	if (ret < 0)
		return (READ_ERR);
	if (ret > 0)
		return (READ_OK);
	return (READ_EOF);
}
