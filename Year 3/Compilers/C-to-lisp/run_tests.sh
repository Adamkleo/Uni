#!/bin/bash

# Create the test_results directory if it doesn't exist
mkdir -p test_results

# Loop through each directory (00, 01, 02, 03)
for dir in tests/00 tests/01 tests/02 tests/03; do
    # Create a corresponding directory in test_results
    mkdir -p test_results/$(basename $dir)

    # Loop through each .c file in the directory
    for cfile in $dir/*.c; do
        # Generate the output file path
        outfile="test_results/$(basename $dir)/$(basename -s .c $cfile).lsp"
        # Process the file with ./trad and save the output
        cat $cfile | ./trad > $outfile
    done
done

echo "Processing complete."

