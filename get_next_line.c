/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoami <whoami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 22:57:27 by whoami            #+#    #+#             */
/*   Updated: 2026/04/28 23:12:02 by whoami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	int		bytes;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[bytes] = '\0';
		stash = ft_strjoin_and_free(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char    *get_next_line(int fd)
{
    static char    *stash;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = read_to_stash(fd, stash);
    if (!stash)
        return (NULL);
    line = ft_strdup_modified(stash);
    stash = clean_stash(stash);
    return (line);
}
