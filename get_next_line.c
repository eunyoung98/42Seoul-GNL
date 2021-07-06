/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehwangbo <ehwangbo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:21:50 by ehwangbo          #+#    #+#             */
/*   Updated: 2021/06/04 16:30:33 by ehwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	chk_line(char **backup, char **line)
{
	char	*temp;
	char	*ptr;

	ptr = ft_strchr(*backup, '\n');
	if (ptr)
	{
		*line = ft_strndup(*backup, ptr - *backup);
		temp = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		free(*backup);
		*backup = temp;
		return (1);
	}
	else
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
}

static int	ft_backup(char **backup, char *buf, ssize_t rd_size)
{
	char	*temp;

	buf[rd_size] = '\0';
	if (*backup != 0)
	{
		temp = ft_strjoin(*backup, buf);
		free(*backup);
	}
	else
		temp = ft_strndup(buf, rd_size);
	if (temp == NULL)
	{
		free(*backup);
		return (-1);
	}
	*backup = temp;
	if (ft_strchr(*backup, '\n'))
		return (1);
	else
		return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*backup[OPEN_MAX];
	ssize_t		rd_size;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	rd_size = read(fd, buf, BUFFER_SIZE);
	while (rd_size >= 0)
	{
		if (ft_backup(&backup[fd], buf, rd_size) || rd_size == 0)
			break ;
		rd_size = read(fd, buf, BUFFER_SIZE);
	}
	if (rd_size < 0)
		return (-1);
	return (chk_line(&backup[fd], line));
}
