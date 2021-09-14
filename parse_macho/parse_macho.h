//
// Created by Maxon Gena on 3/20/21.
//

#ifndef NM_OTOOL_PARSE_MACHO_H
#define NM_OTOOL_PARSE_MACHO_H

#include <mach-o/loader.h>


int get_architecture_type(void *file);

#endif //NM_OTOOL_PARSE_MACHO_H
