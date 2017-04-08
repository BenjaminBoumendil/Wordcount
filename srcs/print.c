#include "wordcount.h"

/*
 * Print t_word structure
 */
static void	print_word(t_list *elem)
{
	printf("%zu\t%s\n", ((t_word*)elem->content)->count, ((t_word*)elem->content)->word);
}

/*
 * Print end result
 */
void	print_result(t_env *env)
{
	list_iter(env->dict_list, print_word);
	printf("%zu\tTotal words\n", env->total_words);
}
