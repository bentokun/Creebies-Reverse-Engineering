#include <wav_file.h>
#include <file.h>

wav_riff _read_riff(CCreebiesFile* file) {
    wav_riff riff;
	
    read_file(file, &riff.chunkID, 4, 1);
	read_file(file, &riff.chunkSize, 4, 1);
	read_file(file, &riff.format, 4, 1);
	
	return riff;
}

wav_fmt _read_fmt(CCreebiesFile* file) {
	wav_fmt fmt;
	
	read_file(file, &fmt.subChunk1ID, 4, 1);
	read_file(file, &fmt.subChunk1Size, 4, 1);
	read_file(file, &fmt.audioFormat, 2, 1);
	read_file(file, &fmt.numChannels, 2, 1);
	read_file(file, &fmt.sampleRate, 4, 1);
	read_file(file, &fmt.byteRate, 4, 1);
	read_file(file, &fmt.blockAlign, 2, 1);
	read_file(file, &fmt.bps, 2, 1);
	
	return fmt;
}

wav_data_info _read_data_info(CCreebiesFile* file) {
	wav_data_info info;
	
	read_file(file, &info.subChunk2ID, 4, 1);
	read_file(file, &info.subChunk2Size, 4, 1);
	
	return info;
}

wav_file* read_wav(const char* path) {
    CCreebiesFile* file = open_file(path, read);
    wav_file* wfile = malloc(sizeof(wav_file)); 
	
	int magic_number = 0;
	
	read_file(file, &magic_number, 4, 1);
	
	wfile->descriptor = _read_riff(file);
	wfile->subChunk1 = _read_fmt(file);
	wfile->subChunk2 = _read_data_info(file);
	
	wfile->data = malloc(wfile->subChunk2.subChunk2Size);
	
	read_file(file, wfile->data, 1, wfile->subChunk2.subChunk2Size);
	
	close_file(file);
	
	return file;
}

void      free_wav(wav_file* file, int ownData)  {
	if (ownData) {
		free(file->data);
	}
	
	free(file);
}

wav_file* init_wav(int pcm, int countChannel, int 
	sampleRate, int bps, int dataSize, void* data) {
	wav_file* file = malloc(sizeof(wav_file));

	/* Fix for corrupted audio played by WMP */
	if (bps > 8) bps = 8;

	file->descriptor.chunkID = 0x46464952;
	file->descriptor.format = 0x45564157;
	
	file->subChunk1.subChunk1ID = 0x20746d66;
	file->subChunk1.subChunk1Size = pcm ? 16 : 32;
	file->subChunk1.audioFormat = pcm ? 1 : 2;
	file->subChunk1.numChannels = countChannel;
	file->subChunk1.sampleRate = sampleRate;
	file->subChunk1.byteRate = sampleRate * countChannel * bps / 8;
	file->subChunk1.blockAlign = countChannel * bps / 8;
	file->subChunk1.bps = bps;
	
	file->subChunk2.subChunk2ID = 0x61746164;
	file->subChunk2.subChunk2Size = dataSize;
	file->data = (char*)(data);

	file->descriptor.chunkSize = 36 + dataSize;
	
	return file;
}

void      write_wav(const char* path, wav_file* file) {
	CCreebiesFile* wfile = open_file(path, write);
	
	write_file(wfile, &file->descriptor, sizeof(wav_riff), 1);
	write_file(wfile, &file->subChunk1, sizeof(wav_fmt), 1);
	write_file(wfile, &file->subChunk2.subChunk2ID, 4, 1);
	write_file(wfile, &file->subChunk2.subChunk2Size, 4, 1);
	write_file(wfile, file->data, 1, file->subChunk2.subChunk2Size);
	
	close_file(wfile);
}