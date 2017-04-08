#include "wordcount.h"

/*
 * Create new list element
 */
t_list	*list_new(const void *content, size_t content_size)
{
	t_list	*new_elem;

	new_elem = (t_list *)malloc(sizeof(t_list));
	if (new_elem)
	{
		if (content != 0)
		{
			new_elem->content = (void *)malloc(sizeof(void*) * content_size);
			memcpy(new_elem->content, content, content_size);
			new_elem->content_size = content_size;
		}
		else
		{
			new_elem->content = NULL;
			new_elem->content_size = 0;
		}
		new_elem->next = NULL;
	}
	return (new_elem);
}

/*
 * Add 'new' list element at the end of list 'begin'
 */
void	list_pushback(t_list **begin, t_list *new)
{
	t_list	*tmp;

	tmp = *begin;
	if (!tmp)
		*begin = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
 * Free all elements in list
 */
void	list_free(t_list **list)
{
	t_list *tmp;

	if (list)
	{
		while (*list)
		{
			tmp = (*list)->next;
			free((*list)->content);
			free(*list);
			*list = tmp;
		}
	}
}

/*
 * Call 'f' function on all 'list' elements
 */
void	list_iter(t_list *list, void (*f)(t_list *elem))
{
	while (list)
	{
		f(list);
		list = list->next;
	}
}
