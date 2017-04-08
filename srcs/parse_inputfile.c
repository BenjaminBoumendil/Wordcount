#include "wordcount.h"

/*
 * Return total number of words in 'line' delimited by 'c'
 */
size_t	word_in_line(const char *line, const char c)
{
	size_t	len;

	len = 0;
	while (*line)
	{
		while (*line == c)
			line++;
		if (*line)
			len++;
		while (*line && *line != c)
			line++;
		if (*line)
			line++;
	}
	return (len);
}

/*
 * Return word size in 's' delimited by 'c'
 */
static size_t	word_length(const char *s, const char c)
{
	const char	*is;

	is = s;
	while (*is && *is != c)
		is++;
	return (is - s);
}

/*
 * Count occurence for 'word' in dictlist
 */
static void	count_occurrence(t_env *env, const char *word)
{
	t_list	*list;

	list = env->dict_list;
	while (list)
	{
		if (strcmp(((t_word*)list->content)->word, word) == 0)
			((t_word*)list->content)->count++;
		list = list->next;
	}
}

void	parse_inputfile(t_env *env, char *line)
{
	size_t	word_count;
	size_t	word_len;
	char	*word;

	word_count = word_in_line(line, ' ');
	env->total_words += word_count;
	while (*line)
	{
		word_len = word_length(line, ' ');
		if (word_len)
		{
			word = strndup(line, word_len);
			count_occurrence(env, word);
			free(word);
			line += word_len;
		}
		if (*line)
			line++;
	}
}
