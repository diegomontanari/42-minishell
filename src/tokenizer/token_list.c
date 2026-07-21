#include "minishell.h"
/* add_token_to_list
 This function adds a new token to the end of a token list.
 - If head or new_token is NULL, do nothing.
 - If the list is empty, set head to the new token.
 - Otherwise, iterate through the list until the last token.
 - Link the new token to the end of the list. */
void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

/*
** get_last_token
**
** This function returns the last token in a linked list of tokens.
** - If the list is empty (head is NULL), return NULL.
** - Otherwise, iterate through the list until the last node
**   (where next is NULL).
** - Return a pointer to the last token found.
*/
t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
