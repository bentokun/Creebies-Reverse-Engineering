#ifndef __FILEH__
#define __FILEH__
	
/* 
 * READING AND WRITING CREEBIES DATA
 * PRETTIED FROM PSEUDO C CODE OF ASM IN CREEBIES DISASSMEBLE
*/

#include <stddef.h>

typedef creebies_file creebies_file;
typedef creebies_file_type creebies_file_type;

creebies_file* allocate_creebies_file(uint16_t num);
creebies_file* empty_creebies_file(creebies_file* file) ;
creebies_file* null_creebies_file(creebies_file* file) ;
creebies_file* load_creebies_file(creebies_file* file, const char* name, const char* om);
	
creebies_file* load_read_type_creebies_file(creebies_file* file, const char* name, const char* om);
creebies_file* load_write_type_creebies_file(creebies_file* file, const char* name, const char* om);

uint32_t tell_file_size(creebies_file* file);
	
#endif