#ifndef __AUDIO_FILE_H__
#define __AUDIO_FILE_H__
	
#include <stdint.h>
	
/* 
 * READING INFO AND LOAD RAW AUDIO DATA OF CREEBIES
*/

//SYMBIAN OS USES LITTLE-ENDIAN - NO CONVERSION REQUIRED!

//CCreebiesAudioInfo - the structure used in Creebies for loading audio info files
typedef struct CCreebiesAudioInfo {
	char gap0[8];  //?
	char* name;    //The name of the audio eg START.WAV
	char gap1[16]; //?
	int  offset;   //Where the audio appears on cache.dat
	char gap2[32]; //?
	int size;      //Size of the file
	int bps;       //Bits per sample - usally 16 (0x00000010)
	int channel;   //Number of channels - 1 = Mono, 2 = Stereo
	int rate;      //Rate - Hz of audio file. Usually what you see is 16000Hz (0x00003e80)
	int unknown5;  //Unknown - usually 0
} CCreebiesAudioInfo;

//Not what Creebies use, but this represents the audio.dat file
//The first two bytes of audio.dat are useless
typedef struct CCreebiesAudioInfoChunk {
	size_t count;
	CCreebiesAudioInfo* infos;
} CCreebiesAudioInfoChunk;

//typedef struct CCreebiesAudioFile

CCreebiesAudioInfoChunk get_data_info(const char* path);
void                    free_data_info(CCreebiesAudioInfoChunk chunk);

#endif