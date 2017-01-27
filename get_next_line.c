/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:46:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/27 20:39:43 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					get_fd(int fd, t_fd *fd_tab)
{
	t_char			*char_elem = NULL;
	t_list			**fd_lst = NULL;

	fd_tab[fd].fd = fd;
	if (!(fd_tab[fd].buffer))
	{
		if (!(char_elem = (t_char *)malloc(sizeof(t_char))))
			return (0);
		char_elem->next = NULL;
		(*fd_lst)->content = char_elem;
		(*fd_lst)->next = NULL;
		fd_tab[fd].buffer = (t_char **)fd_lst;
	}	
	printf("fd_lst %c\n", (fd_tab[fd].buffer->c);
	return (1);
}

int 				get_line(t_list **fd_lst, char *str)
{
	size_t 			i;
	size_t			getline;
	t_char			*curr_char;

	i = 0;
	getline = 0;
	while (str[i])
	{
		if (!(curr_char = ft_memalloc(sizeof(t_char))))
			return (READ_ERR);
		curr_char->c = str[i];
		curr_char->next = CHAR(fd_lst);
		CHAR(fd_lst) = curr_char;
		//	printf("list %c\n", CHAR(fd_lst)->c);
		if (str[i] == '\n')
			getline = 1;
		free(curr_char);
		i++;
	}
	return (getline);
}

int 				buffer_from_fd(t_list **fd_lst, char **line)
{
	int				ret;
	char			*str;

	printf("before %p\n",FD(fd_lst)->buffer);
	if (!(str = ft_strnew(BUFF_SIZE)))
		return (READ_ERR);
	while ((ret = read(FD(fd_lst)->fd, str, BUFF_SIZE)) > 0)
	{
		get_line(fd_lst, str);
		*line = ft_strjoin(*line, str);
		printf("%s\n", *line);
		printf("after %p\n",FD(fd_lst)->buffer);
		printf("first charac %c\n",FD(fd_lst)->buffer->c);
		free(str);
		if (ret)
			return (READ_OK);
	}
	free(str);
	if (ret < 0)
		return (READ_ERR);
	return (READ_EOF);
}

int					get_next_line(const int fd, char **line)
{
	static t_fd 	fd_tab[FD_MAX];

	if (fd < 0 || fd > FD_MAX || line == NULL)
		return (READ_ERR);
	if(!(get_fd(fd, fd_tab)))
		return (READ_ERR);
	return (buffer_from_fd(&fd_lst, line));
}
