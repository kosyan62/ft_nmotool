#include "header.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include "parse_macho/parse_macho.h"

#define ER "nm {red}error:{eoc} %s. Can't read input file\n"
#define EV "nm {red}error:{eoc} %s Was not recognized as valid object file\n"
#define ED "nm {red}error:{eoc} %s. Permission denied\n"

void	print_pritty_element_symtab(t_forprint **pr)
{
	size_t	i;
	int		indent;

	i = 0;
	while (pr[i])
	{
		if (pr[i]->structure == 2)
			indent = 16;
		else
			indent = 8;
		if (!pr[i]->debug)
		{
			if (pr[i]->n_value)
				printf("%0*llx ", indent, pr[i]->n_value);
			else
				printf("%*s ", indent, "");
			printf("%c %s\n", pr[i]->letter, pr[i]->strx);
		}
		i++;
	}
}

void	*get_raw_binary_info(char *filename)
{
	int			fd;
	struct stat	fd_stat;
	void		*rb_info;

	fd = open(filename, O_RDONLY);
	stat(filename, &fd_stat);
	if (!(S_IRWXU & fd_stat.st_mode))
	{
		ft_fdprintf(2, ED, filename);
		return (NULL);
	}
	if (fd_stat.st_size < sizeof(struct mach_header))
	{
		ft_fdprintf(2, \
		EV, filename);
		return (NULL);
	}
	rb_info = mmap(0, fd_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	if (!rb_info)
	{
		ft_printf(ER, filename);
		return (NULL);
	}
	return (rb_info);
}

void	ft_nm(char *filename)
{
	void		*raw_binary_info;
	int			arch_type;
	t_forprint	**printable_table;

	raw_binary_info = get_raw_binary_info(filename);
	arch_type = get_architecture_type(raw_binary_info);
	if (!arch_type)
	{
		ft_fdprintf(2, ER, filename);
		return ;
	}
	else if (arch_type == 1)
		printable_table = get_sections_print_table_x32(raw_binary_info);
	else if (arch_type == 2)
		printable_table = get_sections_print_table_x64(raw_binary_info);
	else
		printable_table = handle_fat_format(raw_binary_info, arch_type);
	if (!printable_table)
		return ;
	print_pritty_element_symtab(printable_table);
	delete_printable(printable_table);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		ft_printf("to few args\n");
	else
		ft_nm(argv[1]);
	return (0);
}
