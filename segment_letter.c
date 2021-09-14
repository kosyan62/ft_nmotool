#include "header.h"

static char	get_section_char(uint8_t type, const char *sectname)
{
	static const t_sym_map	sym_map[3] = {
			{SECT_TEXT, 'T'},
			{SECT_DATA, 'D'},
			{SECT_BSS, 'B'}
	};
	uint8_t					cnt;

	cnt = 0;
	while (cnt < 3)
	{
		if (!ft_strcmp(sym_map[cnt].sect_name, sectname))
		{
			if (!(type & N_EXT))
				return ((char) ft_tolower(sym_map[cnt].sym));
			return (sym_map[cnt].sym);
		}
		cnt++;
	}
	if (!(type & N_EXT))
		return ('s');
	return ('S');
}

static char	get_known_char(uint8_t type_mask)
{
	if (type_mask & N_ABS)
	{
//		if (!(type_mask & N_EXT))
//			return ('a');
//		else
			return ('A');
	}
	else if (type_mask & N_PBUD)
		return ('Z');
	else if (type_mask & N_INDR)
		return ('i');
	else
		return ('U');
}

char	get_symbol_char_x64(struct nlist_64 *nlist, \
					struct section_64 **sections_array)
{
	struct section_64	*sect;
	uint8_t				type_mask;

	if ((N_TYPE & nlist->n_type) == N_SECT)
	{
		sect = sections_array[nlist->n_sect - 1];
		return (get_section_char(nlist->n_type, sect->sectname));
	}
	else
	{
		type_mask = nlist->n_type & N_TYPE;
		return (get_known_char(type_mask));
	}
}

char	get_symbol_char_x32(struct nlist *nlist, \
					struct section **sections_array)
{
	struct section	*sect;
	uint8_t			type_mask;

	if (nlist->n_sect != NO_SECT)
	{
		sect = sections_array[nlist->n_sect - 1];
		return (get_section_char(nlist->n_type, sect->sectname));
	}
	else
	{
		type_mask = nlist->n_type & N_TYPE;
		return (get_known_char(type_mask));
	}
}
