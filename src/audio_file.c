#include <audio_file.h>
#include <file.h>

CCreebiesAudioInfo _read_info(CCreebiesFile* file) {
	CCreebiesAudioInfo info;
	
	read_file(file, &info.size, 4, 1);
	read_file(file, &info.bps, 4, 1);
	read_file(file, &info.channel, 4, 1);
	read_file(file, &info.rate, 4, 1);
	read_file(file, &info.unknown5, 4, 1);
	
	char filenamelen; read_file(file, &filenamelen, 1, 1);
	
	info.name = malloc(filenamelen + 1);
	
	read_file(file, info.name, 1, filenamelen); info.name[filenamelen] = '\0';
	read_file(file, &info.offset, 4, 1);
	
	return info;
}

CCreebiesAudioInfoChunk get_data_info(const char* path) {
	CCreebiesAudioInfoChunk chunk;
	CCreebiesFile* file = open_file(path, read);
	
	short useless; 
	
	read_file(file, &useless, 2, 1);
	read_file(file, &chunk.count, 4, 1);
	
	chunk.infos = malloc(chunk.count * sizeof(CCreebiesAudioInfo));
	
	for (uint32_t i = 0; i < chunk.count; i++) {
		chunk.infos[i] = _read_info(file);
	}
	
	close_file(file);
	
	return chunk;
}

void free_data_info(CCreebiesAudioInfoChunk chunk) {
	for (uint32_t i = 0; i < chunk.count; i++) {
		free(chunk.infos[i].name);
	}
	
	free(chunk.infos);
}