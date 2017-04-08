#ifndef WORDCOUNT_H
# define WORDCOUNT_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

/*
 * Read buffer
 */
# define BUFF_SIZE 1024


/*
 * Typedef
 */
typedef struct s_list	t_list;
typedef struct s_env	t_env;
typedef struct s_word	t_word;

/*
 * Linked list
 */
struct			s_list
{
	void		*content;
	size_t		content_size;
	t_list		*next;
};

t_list			*list_new(const void *content, size_t content_size);
void			list_pushback(t_list **begin, t_list *new);
void			list_free(t_list **list);
void			list_iter(t_list *list, void (*f)(t_list *elem));

/*
 * Program env
 */
struct			s_env
{
	t_list		*dict_list;
	size_t		total_words;
};

/*
 * Represent data for each word to count
 */
struct			s_word
{
	char		*word;
	size_t		count;
};

/*
 * Parser
 */
void			parse_dictfile(t_env *env, char *line);
void			parse_inputfile(t_env *env, char *line);

int				get_next_line(const int fd, char **line);

/*
 * Count word in 'line'
 */
size_t			word_in_line(const char *line, const char c);

/*
 * Print t_env struct
 */
void			print_result(t_env *env);

#endif
