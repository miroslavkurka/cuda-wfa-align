//
// Created by Miro Kurka on 17/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/commons.h"
#include "wavefront/wavefront_align.h"

#define NUM_SEQ 10
#define SEQ_LENGTH 3000
#define NUM_PENALTY_CHANGES 10

// Define sequence data structure
typedef struct {
    char* seq;
    char* name;
} Sequence;

// Function to initialize sequences with random data
void init_sequences(Sequence sequences[]) {
    char bases[] = "ACGT";
    for (int i = 0; i < NUM_SEQ; ++i) {
        sequences[i].name = (char*)malloc(10 * sizeof(char));
        sprintf(sequences[i].name, "Seq%d", i+1);
        sequences[i].seq = (char*)malloc((SEQ_LENGTH + 1) * sizeof(char));
        for (int j = 0; j < SEQ_LENGTH; ++j) {
            sequences[i].seq[j] = bases[rand() % 4];
        }
        sequences[i].seq[SEQ_LENGTH] = '\0';
    }
}

// Function to free allocated memory for sequences
void free_sequences(Sequence sequences[]) {
    for (int i = 0; i < NUM_SEQ; ++i) {
        free(sequences[i].name);
        free(sequences[i].seq);
    }
}

// Function to perform alignment
void perform_alignment(wavefront_aligner_t* wf_aligner, char* pattern, char* text,
                       wavefront_aligner_attr_t attributes, FILE* file) {
    wavefront_align(wf_aligner, pattern, strlen(pattern), text, strlen(text));
    fprintf(file, "Alignment with pattern: %s\n", pattern);
    fprintf(file, "Text: %s\n", text);
    fprintf(file, "Score: %d\n", wf_aligner->cigar->score);
    cigar_print_pretty(file, wf_aligner->cigar, pattern, strlen(pattern), text, strlen(text));
    fprintf(file, "\n");
}

int main(int argc, char* argv[]) {
    // Initialize sequences
    Sequence sequences[NUM_SEQ];
    init_sequences(sequences);

    // Configure alignment attributes
    wavefront_aligner_attr_t attributes = wavefront_aligner_attr_default;
    attributes.distance_metric = gap_affine;
    attributes.affine_penalties.match = 0;
    attributes.affine_penalties.mismatch = 4;
    attributes.affine_penalties.gap_opening = 6;
    attributes.affine_penalties.gap_extension = 2;

    // Create a file to write results
    FILE* output_file = fopen("alignment_results.txt", "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return 1;
    }

    // Initialize Wavefront Aligner
    wavefront_aligner_t* const wf_aligner = wavefront_aligner_new(&attributes);

    // Perform alignment for each sequence
    for (int i = 0; i < NUM_SEQ; ++i) {
        perform_alignment(wf_aligner, sequences[i].seq, sequences[i].name, attributes, output_file);
    }

    // Change penalties multiple times and perform alignment each time
    for (int change = 1; change <= NUM_PENALTY_CHANGES; ++change) {
        fprintf(output_file, "Changing penalties %d...\n", change);
        attributes.affine_penalties.match += 1;
        attributes.affine_penalties.mismatch -= 2;
        attributes.affine_penalties.gap_opening -= 3;
        attributes.affine_penalties.gap_extension -= 1;

        // Perform alignment with new penalties
        for (int i = 0; i < NUM_SEQ; ++i) {
            perform_alignment(wf_aligner, sequences[i].seq, sequences[i].name, attributes, output_file);
        }
    }

    // Close file, free memory and exit
    fclose(output_file);
    wavefront_aligner_delete(wf_aligner);
    free_sequences(sequences);

    return 0;
}
