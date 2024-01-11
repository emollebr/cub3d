/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:44:30 by emollebr          #+#    #+#             */
/*   Updated: 2023/02/22 14:47:01 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	clean(char	*next, char	*line)
{
	if (next)
		free(next);
	if (line)
		free(line);
}

char	*store_buffer(char *line, char *next)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (next[i] != '\0' && next[i] != '\n')
		i++;
	if (next[i] == '\0')
	{
		free(next);
		return (NULL);
	}
	i++;
	s = ft_calloc(sizeof(char), (ft_strlen(next) - ft_strlen(line) + 1));
	if (!s)
		return (clean(next, line), NULL);
	while (next[i] != '\0')
	{
		s[j] = next[i];
		i++;
		j++;
	}
	s[j] = '\0';
	free(next);
	return (s);
}

char	*return_line(char *next)
{
	int		i;
	char	*line;

	i = 0;
	if (!next[i])
		return (NULL);
	while (next[i] != '\0' && next[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (clean(next, line), NULL);
	i = 0;
	while (next[i] != '\0' && next[i] != '\n')
	{
		line[i] = next[i];
		i++;
	}
	if (next[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_file(int fd, char *next)
{
	char	*buf;
	int		ret;
	char	*tmp;

	ret = 1;
	while (ret > 0 && !ft_strchr(next, '\n'))
	{
		buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buf)
			return (clean(next, buf), NULL);
		ret = read(fd, (void *)buf, BUFFER_SIZE);
		if (ret == -1)
			return (clean(next, buf), NULL);
		tmp = ft_strjoin(next, buf);
		if (ft_strlen(tmp) == 0)
		{
			free(tmp);
			return(clean(next, buf), NULL);
		}
		clean(next, buf);
		next = tmp;
	}
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*next[1024];
	char		*line;

	line = NULL;
	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!next[fd])
	{
		next[fd] = ft_calloc(1, BUFFER_SIZE + 1);
		if (!next[fd])
			return (NULL);
	}
	next[fd] = read_file(fd, next[fd]);
	if (!next[fd])
		return (clean(next[fd], line), NULL);
	line = return_line(next[fd]);
	if (!line)
		return (NULL);
	next[fd] = store_buffer(line, next[fd]);
	return (line);
}
/*
int	main()
{
	char	*s;

	int fd1 = open("out", O_RDONLY);
	s = "hey";
	while  (s != NULL)
	{
		s = get_next_line(fd1);
		printf("%s\n", s);
		free(s);
	}
	close(fd1);
}
*/
