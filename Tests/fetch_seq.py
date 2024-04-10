import requests
from Bio import SeqIO

def fetch_dna_sequences(source, number_of_sequences=5):
    """Fetches DNA sequences from the given source.

    Args:
        source (str): URL or path to the source of DNA sequences.
        number_of_sequences (int, optional): Number of sequences to fetch. Defaults to 5.

    Returns:
        list: A list of fetched DNA sequences as strings.
    """

    sequences = []

    if source.startswith("http"):  # Handle URLs
        response = requests.get(source)
        sequences = list(SeqIO.parse(response.text, "fasta"))
    else:  # Assume local file path
        with open(source, "r") as handle:
            sequences = list(SeqIO.parse(handle, "fasta"))

    return sequences[:number_of_sequences]

#sequences = fetch_dna_sequences("https://www.ncbi.nlm.nih.gov/nucleotide/", number_of_sequences=10)  # Adjust source and number as needed

for seq in sequences:
    print(seq.format("fasta"))
