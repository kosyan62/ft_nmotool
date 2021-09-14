#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

typedef struct s_forprint
{
	uint64_t	n_value;
	char		letter;
	char		*strx;
	char		debug;
	int			structure;
}	t_forprint;

typedef struct s_sym_map
{
	char	sect_name[16];
	char	sym;
}	t_sym_map;

char				**get_string_array_from_terminated_table(char *table, \
								size_t size);
char				get_symbol_char_x32(struct nlist *nlist, \
								struct section **sections_array);
char				get_symbol_char_x64(struct nlist_64 *nlist, \
								struct section_64	**sections_array);
t_forprint			**get_sections_print_table_x64(void *raw_binary_info);
t_forprint			**get_sections_print_table_x32(void *raw_binary_info);
int					equality_check(void *a, void *b);
void				delete_printable(t_forprint **printable_table);
t_forprint			**handle_fat_format(void *raw_binary_info, int arch_type);
void				*find_symtab_x32(void *header);
void				*find_symtab_x64(void *header);
void	print_pritty_element_symtab(t_forprint **pr);

#endif
