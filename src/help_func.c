#include "ft_nm.h"

void	delete_printable(t_forprint **printable_table)
{
	size_t	i;

	i = 0;
	while (printable_table[i])
	{
		ft_strdel(&(printable_table[i]->strx));
		free(printable_table[i]);
		i++;
	}
	free(printable_table[i]);
	free(printable_table);
}

int	equality_check(void *a, void *b)
{
	char	*a_str;
	char	*b_str;
	size_t	res;

	a_str = (*((t_forprint **) a))->strx;
	b_str = (*((t_forprint **) b))->strx;
	if (!a_str && !b_str)
		return (((t_forprint *) a)->n_value - ((t_forprint *) b)->n_value);
	if (!a_str)
		return -1;
	if (!b_str)
		return 1;
	res = ft_strcmp(a_str, b_str);
	if (res != 0)
		return ((int) res);
	else
		return ((*((t_forprint **) a))->n_value - (*((t_forprint **) b))->n_value);
}

void	*find_symtab_x32(void *header)
{
	struct load_command	*load_command;

	load_command = header + sizeof(struct mach_header);
	while (load_command->cmd != LC_SYMTAB)
		load_command = ((void *) load_command) + load_command->cmdsize;
	return (load_command);
}

void	*find_symtab_x64(void *header64)
{
	struct load_command	*load_command;
	int ncmds = 0;
	int i = 0;

	ncmds = ((struct mach_header_64*) header64)->ncmds;
	load_command = header64 + sizeof(struct mach_header_64);
	while (load_command->cmd != LC_SYMTAB)
	{
		if (i++ == ncmds)
		{
			ft_fdprintf(2, "no symbols\n");
			return NULL;
		}
		load_command = ((void *) load_command) + load_command->cmdsize;
	}
	return (load_command);
}