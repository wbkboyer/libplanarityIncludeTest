#ifndef TEST_H
#define TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

// NOTE: If this include fails, you need to update your
// tasks.json -I linker flag with the correct includedir
// for planarity on your distribution. On Debian linux,
// this is /usr/local/include, which has a subdirectory
// called planarity that contains the project header files.
#include <planarity/graphLib.h>

#endif