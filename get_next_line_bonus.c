/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:20:10 by moboulan          #+#    #+#             */
/*   Updated: 2024/11/18 11:39:15 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read(int fd, char *buffer, char *storage)
{
	int		bytes_read;
	char	*new_storage;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(storage), NULL);
		if (bytes_read == 0)
			return (storage);
		buffer[bytes_read] = '\0';
		new_storage = ft_strjoin(storage, buffer);
		free(storage);
		if (!new_storage)
			return (NULL);
		storage = new_storage;
		if (ft_strchr(storage, '\n'))
			break ;
	}
	return (storage);
}

static char	*ft_get_line(char *storage)
{
	char	*line;
	int		len;

	if (!storage)
		return (NULL);
	len = 0;
	while (storage[len] && storage[len] != '\n')
		len++;
	line = ft_substr(storage, 0, len + 1);
	return (line);
}

static char	*ft_update_storage(char *storage)
{
	char	*new_storage;
	int		len;

	if (!storage)
		return (NULL);
	len = 0;
	while (storage[len] && storage[len] != '\n')
		len++;
	if (storage[len] == '\n')
		len++;
	new_storage = ft_strdup(&storage[len]);
	free(storage);
	if (new_storage && new_storage[0] == '\0')
		return (free(new_storage), NULL);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	storage[fd] = ft_read(fd, buffer, storage[fd]);
	free(buffer);
	line = ft_get_line(storage[fd]);
	storage[fd] = ft_update_storage(storage[fd]);
	return (line);
}
