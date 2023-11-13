#include "shell.h"

/**
 * add_node - this adds a new node to the start of the linked list.
 *
 * @head: this addresses of the pointer to the head node.
 * @str: this is string to be stored in the node.
 * @num: this node index used for history.
 *
 * Return: this a pointer to the newly added node.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = this_my_strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - this adds a new node to the end of the linked list.
 *
 * @head: this addresses of the pointer to the head node.
 * @str: this is a string to be stored in the node.
 * @num: this the node index used for history.
 *
 * Return: this pointer to the newly added node.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = this_my_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;

		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_list_str - this prints only the 'str' element of a list_t linked list.
 *
 * @h: this the pointer to the first node.
 *
 * Return: this the size of the linked list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		this_my_puts(h->str ? h->str : "(nil)");
		this_my_puts("\n");
		h = h->next;
		i++;
	}

	return (i);
}

/**
 * delete_node_at_index - this deletes the node at the given index.
 *
 * @head: this the address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}

		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list - this frees all nodes of a linked list.
 *
 * @head_ptr: this the address of the pointer to the head node.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}
