# include "wavefront/wavefront_align.h"

// Configure alignment attributes
wavefront_aligner_attr_t attributes = wavefront_aligner_attr_default;
attributes.distance_metric = gap_affine;
attributes.affine_penalties.mismatch = 4;
attributes.affine_penalties.gap_opening = 6;
attributes.affine_penalties.gap_extension = 2;
// Initialize Wavefront Aligner
wavefront_aligner_t* const wf_aligner = wavefront_aligner_new(&attributes);


char* pattern = "TCTTTACTCGCGCGTTGGAGAAATACAATAGT";
char* text = "TCTATACTGCGCGTTTGGAGAAATAAAATAGT";
wavefront_align(wf_aligner, pattern, strlen(pattern), text, strlen(text)); // Align
// Display CIGAR & score
cigar_print_pretty(stderr, pattern, strlen(pattern), text, strlen(text),
    &wf_aligner->cigar, wf_aligner->mm_allocator);
fprintf(stderr, "Alignment Score %d\n", wf_aligner->cigar.score);

wavefront_aligner_delete(wf_aligner); // Free

