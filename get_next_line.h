/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:07:02 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/26 23:27:35 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define BUFF_SIZE 	32

# define FD_MAX		256

# define READ_OK	1
# define READ_EOF	0
# define READ_ERR	-1

# define CHAR(x) ((t_char *)(*x)->content)
# define FD(x) ((t_fd *)(*x)->content)

typedef struct		s_char
{
	char			c;
	struct s_char	*next;
}					t_char;

typedef struct		s_fd
{
	int				fd;
	t_char			*buffer;
}					t_fd;

int		get_next_line(const int fd, char **line);
#endif
