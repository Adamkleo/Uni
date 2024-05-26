#!/bin/bash

for i in {1..15}; do
    formatted_number=$(printf "%02d" $i)
    if command -v python &> /dev/null; then
        python CSPParking.py "./CSP-tests/parking$formatted_number"
    elif command -v python3 &> /dev/null; then
        python3 CSPParking.py "./CSP-tests/parking$formatted_number"
    else
        echo "No suitable Python interpreter found."
        exit 1
    fi
done


