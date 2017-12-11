#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#include "file.h"

typedef enum creebies_file_type {
	unassign = 0,
	read = 1,
	write = 2
} _creebies_file_type;

typedef struct creebies_file {
	void* destruct_func;
	FILE* handle;
	uint32_t size;
	creebies_file_type type;
} _creebies_file;

creebies_file* allocate_creebies_file(uint16_t num) {
	_creebies_file* _file = malloc(num * sizeof(_creebies_file));
	
	return (creebies_file*)_creebies_file;
}

creebies_file* null_creebies_file(creebies_file* file){
	(_creebies_file*)file->size = 0;
	(_creebies_file*)file->type = 0;
	(_creebies_file*)file->handle = 0;
	
	return file;
}

creebies_file* empty_creebies_file(creebies_file* file) {
	if (file->type) {
		fclose((_creebies_file*)file->handle);
		file = null_creebies_file(file);
	}
	
	return file;
}

uint32_t tell_file_size(creebies_file* file) {
	if (!file->size) {
			uint32_t v = ftell((_creebies_file*)file->handle);
			fseek((_creebies_file*)file->handle, 0, SEEK_END);
			uint32_t v1 = ftell(f(_creebies_file*)ile->handle);
			fseek((_creebies_file*)file->handle, v, SEEK_BEG);
			
			return v1;
	}
	
	return file->size;
}

creebies_file* load_read_type_creebies_file(creebies_file* file, const char* name, const char* om){
	_creebies_file* _file = (_creebies_file*)file;
	
	empty_creebies_file(file);
	_file->handle = fopen(name, om);
	
	if (_file->handle){
		_file->size = tell_file_size(file);
		_file->type = read;
	}
	
	return file;

}
creebies_file* load_write_type_creebies_file(creebies_file* file, const char* name, const char* om) {
	_creebies_file* _file = (_creebies_file*)file;
	
	empty_creebies_file(file);	
	_file->handle = fopen(name, om);
	
	if (_file_handle){
		_file->size = 0;
		_file->type = 2;
	}
	
	return file;
}

creebies_file* load_creebies_file(creebies_file* file, const char* name, const char* om) {
	if (name != NULL && *om) {
		if (*om == 'r') 
			file = load_read_type_creebies_file(file,name,om);
		else
			file = load_write_type_creebies_file(file,name,om);
	}
	else
		return NULL;
	
	return file;
}