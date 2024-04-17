# cuda-wfa-align

WFA-2 library is implemented by https://github.com/smarco/WFA2-lib


This project should just hot swap some parts with CUDA kernels 
Similar results have been achieved by https://github.com/quim0/WFA-GPU

For more precise references please consult the original papers:
[1] Santiago Marco-Sola, Juan Carlos Moure, Miquel Moreto, Antonio Espinosa, Fast gap-affine pairwise alignment using the wavefront algorithm, Bioinformatics, Volume 37, Issue 4, February 2021, Pages 456–463, https://doi.org/10.1093/bioinformatics/btaa777

[2] Aguado-Puig, Q. et al. (2023) ‘WFA-GPU: Gap-affine pairwise alignment using GPUs’. bioRxiv. Available at: https://doi.org/10.1101/2022.04.18.488374.

## Implementation of WFA alignment algorithm using CUDA 
Overview of project located at https://miroslavkurka.github.io/thesis.html

### How to build 

```
nvcc
```
