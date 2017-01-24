/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:46:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/24 14:59:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static t_list	*lst = NULL;
	t_fd			*fd_list;

	if (fd < 0 || fd > FD_MAX || line == NULL)
		return (READ_ERR);
	ft_lstnew(NULL, 0);

}
