#include "header.h"

struct section_64	**get_empty_sections_array_x64(void *ptr)
{
	size_t				i;
	size_t				count;
	struct load_command	*cmd;
	struct section_64	**res;

	i = 0;
	count = 0;
	cmd = ptr + sizeof(struct mach_header_64);
	while (i++ != ((struct mach_header_64 *) ptr)->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
			count += ((struct segment_command_64 *) cmd)->nsects;
		cmd = (void *) cmd + cmd->cmdsize;
	}
	res = malloc(sizeof(struct section_64 *) * (count + 1));
	if (res)
		ft_bzero(res, sizeof(struct section_64 *) * (count + 1));
	return (res);
}

void	fill_sections_array_from_segment_x64(\
		struct segment_command_64 *cmd, struct section_64 **sections_array)
{
	size_t				i;
	struct section_64	*section;

	while (*sections_array)
		sections_array++;
	i = 0;
	section = (void *) cmd + sizeof(struct segment_command_64);
	while (i++ < cmd->nsects)
	{
		*sections_array = section;
		sections_array++;
		section++;
	}
}

struct section_64	**get_sections_array_x64(void *ptr)
{
	struct section_64	**sections_array;
	struct section_64	**res;
	struct load_command	*cmd;
	size_t				i;

	i = 0;
	cmd = ptr + sizeof(struct mach_header_64);
	sections_array = get_empty_sections_array_x64(ptr);
	if (!sections_array)
		return (NULL);
	res = sections_array;
	while (i++ != ((struct mach_header_64 *) ptr)->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
			fill_sections_array_from_segment_x64(\
					(struct segment_command_64 *) cmd, sections_array);
		cmd = (void *) cmd + cmd->cmdsize;
	}
	return (res);
}

t_forprint	**fill_sections_print_table_x64(struct section_64 **sect_arr, \
		struct symtab_command *sym_cmd, \
		   char *sym_str, struct nlist_64 *nlist)
{
	t_forprint	**table;
	size_t		i;

	i = 0;
	table = malloc(sizeof(t_forprint *) * (sym_cmd->nsyms + 1));
	while (i != sym_cmd->nsyms)
	{
		table[i] = malloc(sizeof(t_forprint));
		table[i]->n_value = nlist->n_value;
		table[i]->letter = get_symbol_char_x64(nlist, sect_arr);
		table[i]->strx = ft_strdup(sym_str + nlist->n_un.n_strx);
		if (nlist->n_type & N_STAB)
			table[i]->debug = 1;
		else
			table[i]->debug = 0;
		table[i]->structure = 2;
		nlist = (void *) nlist + sizeof(struct nlist_64);
		i++;
	}
	table[i] = NULL;
	ft_qsort(table, sizeof(table), 0, (int)sym_cmd->nsyms - 1 , equality_check);
	return (table);
}

t_forprint	**get_sections_print_table_x64(void *raw_binary_info)
{
	struct section_64		**sections_array;
	struct symtab_command	*symtab_command;
	struct nlist_64			*nlist;
	char					*sym_str;
	t_forprint				**table;

	symtab_command = find_symtab_x64(raw_binary_info);
	sections_array = get_sections_array_x64(raw_binary_info);
	if (!sections_array || !symtab_command)
		return (NULL);
	nlist = raw_binary_info + symtab_command->symoff;
	sym_str = raw_binary_info + symtab_command->stroff;
	table = fill_sections_print_table_x64(\
			sections_array, symtab_command, sym_str, nlist);
	return (table);
}
