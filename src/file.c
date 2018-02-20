#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#include <file.h>

const char* _translate_mode(CCreebiesFileType type) {
	if (type == read) {
		return "rb";
	}
	
	return "wb";
}

size_t _get_size(FILE* file) {
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	
	fseek(file, 0, SEEK_SET);
	
	return size;
}

CCreebiesFile* open_file(const char* path, CCreebiesFileType type) {
	FILE* file = fopen(path, _translate_mode(type));
	
	if (file == NULL) {
		return NULL;
	}
	
	CCreebiesFile* cfile = malloc(sizeof(CCreebiesFile));
	
	cfile->handle = file;
	
	if (type == read) {
		cfile->size = _get_size(file);
	} else {
		cfile->type = type;
	}
	
	return cfile;
}

void close_file(CCreebiesFile* file) {
	fclose(file->handle);
	file->handle = NULL;
	free(file);
}

int tell_file(CCreebiesFile* file) {
	return ftell(file->handle);
}

size_t read_file(CCreebiesFile* file, void* dest, size_t esize, size_t count) {
	if (file->type == write) { return 0; }
	
	return fread(dest, esize, count, file->handle);
}

size_t write_file(CCreebiesFile* file, void* src, size_t esize, size_t count) {
    if (file->type == read) { return 0; }
	return fwrite(src, esize, count, file->handle);
}

int seek_file(CCreebiesFile* file, int offset, int origin) {
	return fseek(file->handle, offset, origin);
}