//
// Created by Maxon Gena on 8/31/21.
//
#include "libft.h"

void	swap(void *v1, void *v2, int size)
{
	char	buffer[size];

	ft_memcpy(buffer, v1, size);
	ft_memcpy(v1, v2, size);
	ft_memcpy(v2, buffer, size);
}

void	ft_qsort(void *v, int size, int left, int right,
			  int (*comp)(void *, void *))
{
	void *vt;
	void *v3;
	void *vl;
	void *vr;

	int i, last, mid = (left + right) / 2;
	if (left >= right)
		return;

	vl = (char *)(v + (left * size));
	vr = (char *)(v + (mid * size));
	swap(vl, vr, size);
	last = left;
	for (i = left + 1; i <= right; i++) {

		vt = (char *)(v + (i * size));
		if ((*comp)(vl, vt) > 0) {
			++last;
			v3 = (char *)(v + (last * size));
			swap(vt, v3, size);
		}
	}
	v3 = (char *)(v + (last * size));
	swap(vl, v3, size);
	ft_qsort(v, size, left, last - 1, comp);
	ft_qsort(v, size, last + 1, right, comp);
}
