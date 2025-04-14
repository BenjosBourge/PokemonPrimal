#!/bin/bash

# Chemin vers le fichier du rapport de couverture
COVERAGE_FILE="./tests/results.txt"

if [ -e "$COVERAGE_FILE" ]; then

    cat "$COVERAGE_FILE"

    # Extraire le pourcentage de couverture de la dernière ligne
    COVERAGE_PERCENTAGE=$(tail -n 2 "$COVERAGE_FILE" | awk '{print $4}' | tr -d '%')

    # Seuil de couverture
    THRESHOLD=5

    # Vérifier si le pourcentage de couverture est supérieur ou égal au seuil
    if (( $(echo "$COVERAGE_PERCENTAGE >= $THRESHOLD" | bc -l) )); then
        echo "coverage > or = $THRESHOLD%. Perfect"
        exit 0
    else
        echo "coverage = at $COVERAGE_PERCENTAGE it's < at $THRESHOLD%"
        exit 84
    fi
else
    echo "file $COVERAGE_FILE don't find. Please launch 'just coverage' and retry"
fi
