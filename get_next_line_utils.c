/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschebly <aschebly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 22:58:16 by whoami            #+#    #+#             */
/*   Updated: 2026/05/02 14:07:42 by aschebly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_and_free(char *stash, char *buf)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!stash)
	{
		stash = malloc(1 * sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	if (!stash || !buf)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buf) + 1));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	if (stash)
		while (stash[++i])
			res[i] = stash[i];
	while (buf[j])
		res[i++] = buf[j++];
	res[i] = '\0';
	free(stash);
	return (res);
}

char	*ft_strdup_modified(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash || !stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';	
	return (line);
}
/*#include "get_next_line.h"

int	main(void)
{
    int		fd;
    char	*line;

    fd = open("file.txt", O_RDWR);
    if (fd == -1)
        return (1);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    close(fd);
    return (0);
}*/
