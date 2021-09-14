#include "libft.h"

uint32_t	ft_swap_uint32(uint32_t n)
{
	long res;

	res = ((n >> 24) & 0xff) | \
              ((n << 8) & 0xff0000) | \
              ((n >> 8) & 0xff00) | \
              ((n << 24) & 0xff000000);
	return res;
}
