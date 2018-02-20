#include <audio_file.h>
#include <wav_file.h>
#include <file.h>
#include <stdio.h>

char* cache_path = "cache.dat";
char* output_dir = "";
int dump = 0;
int wav = 1;

void dump_audio_file_info(CCreebiesAudioInfo info) {
	printf("Audio name = %s , size = %d , offset = %d , sample rate = %d\n", info.name, info.size, info.offset, info.rate);
}

int parse_args(int argc, char** argv) {
	for (int i = 1; i < argc-1; i++) {
		if (argv[i][0] == '-') {
			if (argv[i] == "-raw") {
				wav = 0;
			}
			else if (argv[i] == "-o") {
				output_dir = argv[i+1];
			}
			else if (argv[i] == "-d") {
				dump = 1;
			}
			else if (argv[i] == "-src") {
				cache_path = argv[i+1];
			}
		}
	}

	return 1;
}

void write_raw_m(char* append_path, CCreebiesAudioInfo info, char* data) {
	int al = strlen(append_path);
	int nl = strlen(info.name);
	
    char* temp_path = malloc(al+nl+1);
	char* extension = "RAW";
	
	memcpy(temp_path, append_path, strlen(append_path));
	strcat(temp_path, info.name);
	memcpy(temp_path + al - 3, extension, 3); 
	
	CCreebiesFile* temp_raw_file = open_file(temp_path, write);
    write_file(temp_raw_file, data, 1, info.size);
    close_file(temp_raw_file);
	
	free(temp_path);
}

void write_wav_m(char* append_path, CCreebiesAudioInfo info, char* data) {
	int al = strlen(append_path);
	int nl = strlen(info.name);
	
    char* temp_path = calloc(al+nl, al + nl);
	
	memcpy(temp_path, append_path, strlen(append_path));
	strcat(temp_path, info.name);
	
	wav_file* wfile = init_wav(1, info.channel, info.rate,
					info.bps, info.size, data);
	
	write_wav(temp_path, wfile);
	free_wav(wfile, 0);
	
	free(temp_path);
}

int main(int argc, char** argv) {
	if (argc <= 1) {
		printf("Path not specified.");
		return 0;
	}

	parse_args(argc, argv);
	
	CCreebiesAudioInfoChunk chunk = get_data_info(argv[argc-1]);

	if (chunk.count == 0) {
		printf("Invalid file. Size is zero");
		return 0;
	}
	
	if (dump) {
		for (uint32_t i = 0; i < chunk.count; i++) {
			dump_audio_file_info(chunk.infos[i]);
		}
	}

	if (cache_path == NULL) {
		printf("Cache not specified. use default");
		//return 0;
	}

	CCreebiesFile* cache_file = open_file(cache_path, read);

	for (int i = 0; i <chunk.count; i++) {
		if (chunk.infos[i].offset < 0) {
			continue;
		}

		char* temp_data = malloc(chunk.infos[i].size); 

		seek_file(cache_file, chunk.infos[i].offset, SEEK_SET);
		read_file(cache_file, temp_data, 1, chunk.infos[i].size);	
		
		if (!wav) {
			write_raw_m(output_dir, chunk.infos[i], temp_data);
		} else {
			write_wav_m(output_dir, chunk.infos[i], temp_data);
		}
		
		free(temp_data);
	}
	
	free_data_info(chunk);

	close_file(cache_file);
	
	return 0;
}