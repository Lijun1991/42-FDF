/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:57 by lwang             #+#    #+#             */
/*   Updated: 2016/12/08 20:32:21 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_stock_nl(char **stock, char **line, int fd)
{
	char *check;

	check = ft_strchr(stock[fd], (int)'\n');
	if (check != NULL)
	{
		*check = '\0';
		*line = ft_strdup(stock[fd]);
		stock[fd] = ft_strdup(check + 1);
		return (2);
	}
	return (0);
}

int		check_buf_nl(char *buf, char **stock, char **line, int fd)
{
	char *check;

	check = ft_strchr(buf, (int)'\n');
	if (check != NULL)
	{
		*check = '\0';
		*line = ft_strmerge(stock[fd], buf);
		stock[fd] = ft_strdup(check + 1);
		return (2);
	}
	return (0);
}

int		the_end(int fd, char *buf, char **stock, char **line)
{
	free(buf);
	buf = NULL;
	if (stock[fd] == NULL || ft_strcmp(stock[fd], "") == 0)
		return (0);
	*line = ft_strdup(stock[fd]);
	stock[fd] = NULL;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*stock[MAX_FD];

	if (fd < 0 || fd > MAX_FD)
		return (-1);
	if (stock[fd] != NULL || ft_strlen(stock[fd]) != 0)
		if (check_stock_nl(stock, line, fd) == 2)
			return (1);
	if (!stock[fd])
		stock[fd] = "";
	buf = ft_strnew(BUFF_SIZE + 1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (check_buf_nl(buf, stock, line, fd) == 2)
			return (1);
		stock[fd] = ft_strmerge(stock[fd], buf);
		buf = ft_strnew(BUFF_SIZE + 1);
	}
	if (ret == -1)
		return (-1);
	return (the_end(fd, buf, stock, line));
}
