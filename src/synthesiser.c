#include <math.h>

#include "constants.h"

// oo, as in Who
double oo[17] = {10/40.0, 10/40.0, 10/40.0, 7/40.0, 6/40.0, 2/40.0, 2/40.0, 1/40.0, 1/40.0, 1/40.0, 0/40.0, 2/40.0, 1/40.0, 1/40.0, 1/40.0, 1/40.0, 1/40.0};

double add_synth(int t, double fundamental, int no_overtones, double *amplitudes){
    double output = 0;
    for (int i = 0; i < no_overtones; ++i){
        output += amplitudes[i] * sin(t/SAMP_RATE * TAU * fundamental * (i + 1));
    }
    return output;
}

double phoneme(int t, double freq){
    // guaranteed to be random.
    return 4;
}

void write_samples(short *output, int num_samples){
    double sample = 0;
    for (int t = 0; t < num_samples; ++t){
        sample = add_synth(t, 110, 17, oo);

        output[t] = (sample * 32767.5);
    }
}
