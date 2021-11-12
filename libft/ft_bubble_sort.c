#include "libft.h"

void	ft_bubble_sort(void **array, size_t len, int(*func)(void *, void *))
{
	size_t	i;
	size_t	k;
	void	*swap;

	i = 0;
	while (i < len - 1)
	{
		k = 0;
		while (k < len - i - 1)
		{
			if (func(array[k], array[k + 1]) > 0)
			{
				swap = array[k];
				array[k] = array[k + 1];
				array[k + 1] = swap;
			}
			k++;
		}
		i++;
	}
}
