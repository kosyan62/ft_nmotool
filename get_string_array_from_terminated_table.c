#include "ft_nm.h"

char	**get_string_array_from_terminated_table(char *table, size_t size)
{
	int		i;
	char	**res;

	res = malloc(sizeof(char *) * size + 1);
	i = 0;
	while (i != size)
	{
		res[i] = table;
		i++;
		table += ft_strlen(table) + 1;
	}
	return (res);
}
