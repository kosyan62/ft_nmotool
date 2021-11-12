#include "ft_nm.h"

struct section	**get_empty_sections_array_x32(void *ptr)
{
	size_t				i;
	size_t				count;
	struct load_command	*cmd;
	struct section		**res;

	i = 0;
	count = 0;
	cmd = ptr + sizeof(struct mach_header);
	while (i++ != ((struct mach_header *) ptr)->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
			count += ((struct segment_command *) cmd)->nsects;
		cmd = (void *) cmd + cmd->cmdsize;
	}
	res = malloc(sizeof(struct section *) * (count + 1));
	if (res)
		ft_bzero(res, sizeof(struct section *) * (count + 1));
	return (res);
}

void	fill_sections_array_from_segment_x32(struct segment_command *cmd, \
												struct section **sections_array)
{
	size_t			i;
	struct section	*section;

	while (*sections_array)
		sections_array++;
	i = 0;
	section = (void *) cmd + sizeof(struct segment_command);
	while (i++ < cmd->nsects)
	{
		*sections_array = section;
		sections_array++;
		section++;
	}
}

struct section	**get_sections_array_x32(void *ptr)
{
	struct section		**sections_array;
	struct section		**res;
	struct load_command	*cmd;
	size_t				i;

	i = 0;
	cmd = ptr + sizeof(struct mach_header);
	sections_array = get_empty_sections_array_x32(ptr);
	if (!sections_array)
		return (NULL);
	res = sections_array;
	while (i++ != ((struct mach_header *) ptr)->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
			fill_sections_array_from_segment_x32(\
					(struct segment_command *) cmd, sections_array);
		cmd = (void *) cmd + cmd->cmdsize;
	}
	return (res);
}

t_forprint	**fill_sections_print_table_x32(struct section **sect_arr, \
											struct symtab_command *sym_cmd, \
											char *sym_str, struct nlist *nlist)
{
	t_forprint	**table;
	size_t		i;

	i = 0;
	table = malloc(sizeof(t_forprint *) * (sym_cmd->nsyms + 1));
	while (i != sym_cmd->nsyms)
	{
		table[i] = malloc(sizeof(t_forprint));
		table[i]->n_value = nlist->n_value;
		table[i]->letter = get_symbol_char_x32(nlist, sect_arr);
		table[i]->strx = ft_strdup(sym_str + nlist->n_un.n_strx);
		if (table[i]->strx == NULL)
			ft_printf("Fuck\n");
		if (nlist->n_type & N_STAB)
			table[i]->debug = 1;
		else
			table[i]->debug = 0;
		table[i]->structure = 1;
		nlist = (void *) nlist + sizeof(struct nlist);
		i++;
	}
	table[i] = NULL;
	ft_qsort(table, sizeof(table), 0, (int)sym_cmd->nsyms - 1 , equality_check);
	return (table);
}

t_forprint	**get_sections_print_table_x32(void *raw_binary_info)
{
	struct section			**sections_array;
	struct symtab_command	*sym_cmd;
	struct nlist			*nlist;
	char					*sym_str;
	t_forprint				**table;

	sym_cmd = find_symtab_x32(raw_binary_info);
	sections_array = get_sections_array_x32(raw_binary_info);
	if (!sections_array)
		return (NULL);
	nlist = raw_binary_info + sym_cmd->symoff;
	sym_str = raw_binary_info + sym_cmd->stroff;
	table = fill_sections_print_table_x32(\
							sections_array, sym_cmd, sym_str, nlist);
	return (table);
}
