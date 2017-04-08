#include "wordcount.h"

/*
 * Return 1 if line should be ignored otherwise 0
 */
static int	ignore_line(const char *line)
{
	if (*line == '\0' || *line == '#' || word_in_line(line, ' ') > 1)
		return (1);
	return (0);
}

void	parse_dictfile(t_env *env, char *line)
{
	t_word	word;

	while(*line == ' ' || *line == '\t')
		line++;

	if (ignore_line(line) == 1)
		return ;

	word.word = strdup(line);
	word.count = 0;
	list_pushback(&(env->dict_list), list_new(&word, sizeof(t_word)));
}
