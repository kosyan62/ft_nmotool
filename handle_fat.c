#include "header.h"
#include "parse_macho/parse_macho.h"
#include <mach-o/fat.h>
#include <stdio.h>

int	is_swaped(uint64_t num)
{
	if (num == FAT_CIGAM || num == FAT_CIGAM_64)
		return (1);
	else
		return (0);
}

void	*x32_find_macho_start(void *raw)
{
	uint32_t		structure_count;
	struct fat_arch	*arch;
	size_t			offset;
	cpu_type_t		cputype;

	structure_count = (((struct fat_header *) raw)->nfat_arch);
	if (is_swaped(*(uint32_t *) raw))
		structure_count = ft_swap_uint32(structure_count);
	arch = raw + sizeof(struct fat_header);
	while (structure_count--)
	{
		if (is_swaped(*(uint32_t *) raw))
			cputype = ft_swap_uint32(arch->cputype);
		if (cputype == CPU_TYPE_X86_64)
		{
			offset = arch->offset;
			if (is_swaped(*(uint32_t *) raw))
				offset = ft_swap_uint32(offset);
			return (raw + offset);
		}
		arch = (void *) arch + sizeof(struct fat_arch);
	}
	return (NULL);
}

void	*x64_find_macho_start(void *raw)
{
	uint32_t			structure_count;
	struct fat_arch_64	*arch;
	size_t				offset;
	cpu_type_t			cputype;

	structure_count = (((struct fat_header *) raw)->nfat_arch);
	if (is_swaped(*(uint64_t *) raw))
		structure_count = ft_swap_uint32(structure_count);
	arch = raw + sizeof(struct fat_header);
	while (structure_count--)
	{
		if (is_swaped(*(uint64_t *) raw))
			cputype = ft_swap_uint32(arch->cputype);
		if (cputype == CPU_TYPE_X86_64)
		{
			offset = arch->offset;
			if (is_swaped(*(uint64_t *) raw))
				offset = ft_swap_uint32(offset);
			return (raw + offset);
		}
		arch = (void *) arch + sizeof(struct fat_arch);
	}
	return (NULL);
}

t_forprint	**handle_fat_format(void *raw_binary_info, int arch_type)
{
	void	*macho_start;

	if (arch_type == 3)
		macho_start = x32_find_macho_start(raw_binary_info);
	else
		macho_start = x64_find_macho_start(raw_binary_info);
	arch_type = get_architecture_type(macho_start);
	if (arch_type == 1)
		return (get_sections_print_table_x32(macho_start));
	else if (arch_type == 2)
		return (get_sections_print_table_x64(macho_start));
	else
		return (NULL);
}
