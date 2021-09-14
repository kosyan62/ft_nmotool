#include "parse_macho.h"
#include <stdint.h>
#include <mach-o/fat.h>

int get_architecture_type(void *file)
{
	uint32_t magic;

	magic = ((struct mach_header_64*) file)->magic;
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return 1;
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return 2;
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return 3;
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return 4;
	else
		return 0;
}