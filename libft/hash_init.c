/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash..c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:59:17 by mgena             #+#    #+#             */
/*   Updated: 2020/03/06 17:53:50 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ht_item		*new_ht_item(char *key, char *value)
{
	t_ht_item *new;

	if (!(new = ft_memalloc(sizeof(t_ht_item))))
		return (NULL);
	if (!(new->key = ft_strdup(key)))
		return (NULL);
	if (!(new->value = ft_strdup(value)))
		return (NULL);
	new->next = NULL;
	return (new);
}

t_hash_table	*new_hash_table(unsigned int size)
{
	t_hash_table	*table;
	t_ht_item		**items;
	size_t			i;

	i = 0;
	if (!(table = ft_memalloc(sizeof(t_hash_table))))
		return (NULL);
	if (!size)
	{
		table->size = 0;
		table->items = NULL;
		return (table);
	}
	if (!(items = ft_memalloc(sizeof(t_ht_item*) * size)))
		return (NULL);
	while (i != size)
		items[i++] = NULL;
	table->items = items;
	table->size = size;
	return (table);
}

void			ht_del_item(t_ht_item *item)
{
	if (item->next)
		ht_del_item(item->next);
	free(item->key);
	free(item->value);
	free(item);
}

void			del_hash_table(t_hash_table *table)
{
	size_t		i;
	t_ht_item	*item;

	i = 0;
	while (i != table->size)
	{
		item = table->items[i];
		if (item)
			ht_del_item(item);
		i++;
	}
	free(table->items);
	free(table);
}

void			ht_del_elem(t_hash_table *table, char *key)
{
	unsigned int	index;
	t_ht_item		*item;

	index = hash_funct(key, HASH_WEIGHT, table->size);
	item = table->items[index];
	while (item)
	{
		if (!ft_strcmp(item->key, key))
		{
			ht_del_item(item);
			break ;
		}
		item = item->next;
	}
}
