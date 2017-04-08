#include "wordcount.h"

/*
 * Return size of string in 'str' from 'start' to character 'c'
 */
static int	strsublen(const char *str, int start, char c)
{
	int		i;

	i = 0;
	while (str[start] && str[start] != c)
	{
		++start;
		++i;
	}
	return (i);
}

/*
 * Return new string in 's' from 'start' of size 'len'
 */
static char	*strsub(const char *s, size_t start, size_t len)
{
	size_t	c;
	char	*str;

	c = 0;
	if (!s)
		return (0);
	str = (char *)malloc(sizeof(char) * (len + 1));
	bzero(str, len + 1);
	while (c != len)
	{
		str[c] = s[start + c];
		c++;
	}
	return (str);
}

/*
 * Join string 's1' to string 's2'
 */
static char	*strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	c;

	if (s1 && s2)
	{
		c = strlen(s1) + strlen(s2);
		str = (char *)malloc(sizeof(char) * (c + 1));
		bzero(str, c);
		str = strcat(str, s1);
		str = strcat(str, s2);
		return (str);
	}
	return (0);
}

/*
 * Return line length
 */
static int	find_new_line(const char *remains)
{
	const char *str;

	if (remains)
	{
		str = remains;
		while (*str)
		{
			if (*str == '\n')
				return (str - remains);
			++str;
		}
	}
	return (-1);
}

/*
 * Clear consumed line from 'remains'
 */
static void	clear_remains(char **remains, int cur_line)
{
	char	*tmp;
	int		len;

	if (*remains)
	{
		len = strlen(*remains);
		tmp = strsub(*remains, cur_line + 1, len - cur_line);
		free(*remains);
		*remains = tmp;
		if (cur_line == -1)
		{
			free(*remains);
			*remains = 0;
		}
	}
}

/*
 * Read a file descriptor line by line
 * Store current line in char **line
 * Return 0 at EOF otherwise 1
 * Return -1 if read error
 */
int			get_next_line(const int fd, char **line)
{
	ssize_t		ret;
	char		buf[BUFF_SIZE + 1];
	static char	*remains = NULL;
	int			cur_line;

	ret = 1;
	bzero(buf, BUFF_SIZE + 1);
	while ((cur_line = find_new_line(remains)) < 0 && ret)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		else if (*buf != '\0')
			remains = remains ? strjoin(remains, buf) : strdup(buf);
	}
	if (!remains || strlen(remains) == 0)
		return (0);
	*line = strsub(remains, 0, strsublen(remains, 0, '\n'));
	clear_remains(&remains, cur_line);
	return (1);
}
