/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:46:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/27 22:33:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					read_buff(int fd, t_fd *fd_tab)
{
	t_char			*buffer;
	char			src[BUFF_SIZE + 1] = {'\0'};
	int				ret;
	size_t			i;

	buffer = fd_tab[fd].buffer;
	while (buffer && buffer->next)
		buffer = buffer->next;
	//ft_bzero(src, BUFF_SIZE + 1);
	ret = read(fd, src, BUFF_SIZE);
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
		buffer->c = src[i];
		buffer->next = NULL;
		i++;
	}
	return (ret);
}

int					buffer_has_line(t_fd *fd, char **target)
{
	size_t			length;
	t_char 			*current;
	t_char			*prev;
	t_char			*buffer;
	char 			*line;

	buffer = fd->buffer;
	if (buffer == NULL)
		*target = NULL;
	current = buffer;
	length = 0;
	while (current != NULL && current->c != '\n')
	{
		current = current->next;
		length++;
	}
	if (current && current->c == '\n')
	{
		line = ft_strnew(length);
		length = 0;
		while (buffer->c != '\n')
		{
			line[length++] = buffer->c;
			prev = buffer;
			buffer = buffer->next;
			free(prev);
		}
		prev = buffer;
		buffer = buffer->next;
		free (prev);
		fd->buffer = buffer;
		*target = line;
		return (1);
	}
	return (0);
}

int					read_line(int fd, t_fd *fd_tab, char **line)
{
	int				ret;

	ret = 1;
	while (!buffer_has_line(&fd_tab[fd], line) && ret > 0)
		ret = read_buff(fd, fd_tab);
	if (ret == 0)
		return (READ_EOF);
	if (ret > 0)
		return (READ_OK);
	return (READ_ERR);
}

int					get_next_line(const int fd, char **line)
{
	static t_fd 	fd_tab[FD_MAX];

	if (fd < 0 || fd > FD_MAX || line == NULL)
		return (READ_ERR);
	if (buffer_has_line(&fd_tab[fd], line))
		return (READ_OK);
	return (read_line(fd, fd_tab, line));
}
