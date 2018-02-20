#ifndef __WAV_FILE_H__
#define __WAV_FILE_H__

typedef struct wav_riff {
    int chunkID;
    int chunkSize;
    int format;
} wav_riff;

typedef struct wav_fmt {
    int subChunk1ID;
    int subChunk1Size;
    short audioFormat;
    short numChannels;
    int sampleRate;
    int byteRate;
    short blockAlign;
    short bps;
} wav_fmt;

typedef struct wav_data_info {
    int subChunk2ID;
    int subChunk2Size;
} wav_data_info;

typedef struct wav_file {
    wav_riff descriptor;
    wav_fmt subChunk1;
    wav_data_info subChunk2;
    char *data;
} wav_file;

wav_file *read_wav(const char *path);
void free_wav(wav_file *file, int ownData);

wav_file *init_wav(int pcm, int countChannel, int sampleRate, int bps, int dataSize, void *data);

void write_wav(const char *path, wav_file *file);

#endif