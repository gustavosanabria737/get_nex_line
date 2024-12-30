/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsanabri <gsanabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:40:10 by gsanabri          #+#    #+#             */
/*   Updated: 2024/12/29 20:09:54 by gsanabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_next_line_utils.c
#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t		i;	
	int			j;
	char		*new_string;

	i = 0;
	new_string = (char *) malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!new_string)
		return (NULL);
	if (new_string)
	{
		while (i < gnl_strlen(s1))
		{
			new_string[i] = s1[i];
			i++;
		}
		j = 0;
		while (i < (gnl_strlen(s1) + gnl_strlen(s2)))
		{
			new_string[i++] = s2[j++];
		}
		new_string[i] = '\0';
	}
	return (new_string);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static char	*get_substr(char const *s, size_t len, unsigned int start)
{
	size_t	i;
	char	*substr;

	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;

	if (s == NULL)
	{
		return (NULL);
	}
	s_len = gnl_strlen(s);
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (substr == NULL)
		{
			return (NULL);
		}
		substr[0] = '\0';
		return (substr);
	}
	if (len > s_len - start)
	{
		len = s_len - start;
	}
	return (get_substr(s, len, start));
}
