/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsanabri <gsanabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:30:54 by gsanabri          #+#    #+#             */
/*   Updated: 2024/12/30 18:03:42 by gsanabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*gnl_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	if (!s)
	{
		return (NULL);
	}
	len = gnl_strlen(s);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*append_buffer(char *buffer, char *temp)
{
	char	*new_buffer;

	if (!buffer)
		buffer = gnl_strdup("");
	if (!buffer || !temp)
		return (NULL);
	new_buffer = gnl_strjoin(buffer, temp);
	free(buffer);
	return (new_buffer);
}

char	*read_append(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = (char *) malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = append_buffer(buffer, temp);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	free (temp);
	return (buffer);
}

char	*extract_line(char	*buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = gnl_substr(buffer, 0, i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_append(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	buffer = gnl_substr(buffer, i + 1, gnl_strlen(buffer) - i - 1);
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(int argc, char **argv) {
    int fd;
    char *line;

    if (argc < 2) {
        printf("Por favor, pase un archivo de texto como parámetro\n");
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
	int i = 1;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Numbers of calls: %d\n", i);
        printf("%s", line);
		
        free(line);
		i++;
    }
    close(fd);
    return 0;
} */
