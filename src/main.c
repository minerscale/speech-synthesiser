#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "constants.h"
#include "synthesiser.h"

// Writes 16 bit mono little endian audio data
// into a wav header
void write_wav(short *input, int num_samples, char *output){
	// Magic number "RIFF"
	*(int *)  (output)      = 0x46464952;
	// Chunk size
	*(int *)  (output + 4)  = 36 + 2*num_samples;
	// Magic number "WAVE"
	*(int *)  (output + 8)  = 0x45564157;
	// Magic number "fmt "
	*(int *)  (output + 12) = 0x20746d66;
	// Subchunk1Size
	*(int *)  (output + 16) = 16;
	// Audio Format (PCM)
	*(short *)(output + 20) = 1;
	// Number of channels
	*(short *)(output + 22) = 1;
	// Sample rate
	*(int *)  (output + 24) = SAMP_RATE;
	// Byte rate
	*(int *)  (output + 28) = 2*SAMP_RATE;
	// Block align
	*(short *)(output + 32) = 2;
	// Bits per sample
	*(short *)(output + 34) = 16;
	// Magic number "data"
	*(int *)  (output + 36) = 0x61746164;
	// Subchunk2Size
	*(int *)  (output + 40) = 2*num_samples;
	// Data
	memcpy (output + 44, input, 2*num_samples);
}


int main(){
	int num_samples = SAMP_RATE * 30;
	short *audio = malloc(2*num_samples);
	write_samples(audio, num_samples);

	char *wav = malloc(44 + 2*num_samples);
	write_wav(audio, num_samples, wav);
	FILE *wav_file = fopen("./output.wav", "w");
	if (wav_file == NULL){
		return 1;
	}
	fwrite (wav, 1, 44 + 2*num_samples, wav_file);
	fclose(wav_file);
}
