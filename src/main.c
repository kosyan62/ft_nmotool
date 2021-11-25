#include "ft_nm.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define ER "nm {red}error:{eoc} %s. The file was not recognized as a valid object file\n"
#define EV "nm {red}error:{eoc} %s Was not recognized as valid object file\n"
#define ED "nm {red}error:{eoc} %s. Permission denied\n"
#define EE "nm {red}error:{eoc} %s. No such file or directory.\n"
#define FD "nm {red}error:{eoc} %s. Is a directory.\n"

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
				ft_printf("%0*llx ", indent, pr[i]->n_value);
			else
				ft_printf("%*s ", indent, "");
			ft_printf("%c %s\n", pr[i]->letter, pr[i]->strx);
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
	if (!stat(filename, &fd_stat))
	{
		if (S_ISDIR(fd_stat.st_mode))
		{
			ft_fdprintf(2, FD, filename);
			return (NULL);
		}
		if (S_IRWXU & fd_stat.st_mode)
		{
			ft_fdprintf(2, ED, filename);
			return (NULL);
		}
		else
		{
			ft_fdprintf(2, EE, filename);
			return (NULL);
		}
	}
	else
	{
			ft_fdprintf(2, EE, filename);
			return (NULL);
	}
	if ((unsigned long) fd_stat.st_size < sizeof(struct mach_header))
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
	if (!raw_binary_info)
		return ;
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
	int i;

	i = 1;
	if (argc == 1)
		ft_printf("to few args\n");
	else if (argc == 2)
		ft_nm(argv[1]);
	else
		{
		while (i != argc)
			{
				ft_printf("\n%s:\n", argv[i]);
				ft_nm(argv[i++]);
			}
		}
	return (0);
}
