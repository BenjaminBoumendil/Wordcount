#include "wordcount.h"

/*
 * Open and read 'file', execute 'f' function on each line
 * Return -1 in case of error, otherwise 0
 */
static int	read_file(t_env *env, char *file, void(*f)(t_env *env, char *line))
{
	char	*line;
	int		ret;
	int		fd;

	line = 0;
	fd = open(file, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		f(env, line);
		free(line);
	}
	close(fd);
	return (ret);
}

static void	wordcount(t_env *env, char **argv)
{
	int		ret;

	// parse dictfile
	ret = read_file(env, *argv, parse_dictfile);
	if (ret == -1)
	{
		fprintf(stderr, "Error: Can't read file: %s.\n", *argv);
		return ;
	}
	argv++;

	// parse inputfile
	while (*argv)
	{
		ret = read_file(env, *argv, parse_inputfile);
		if (ret == -1)
			fprintf(stderr, "Error: Can't read file: %s.\n", *argv);
		argv++;
	}

	print_result(env);
}

/*
 * Init t_env struct
 */
static void	init_env(t_env *env)
{
	bzero(env, sizeof(t_env));
	env->total_words = 0;
}

/*
 * Free t_word struct
 */
static void	free_word(t_list *elem)
{
	free(((t_word*)elem->content)->word);
}

/*
 * Free t_env struct
 */
static void	free_env(t_env *env)
{
	list_iter(env->dict_list, free_word);
	list_free(&(env->dict_list));
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
	{
		fputs("Error: Missing Dictfile argument.\n", stderr);
		return (-1);
	}

	init_env(&env);
	wordcount(&env, ++argv);
	free_env(&env);
	return (0);
}
