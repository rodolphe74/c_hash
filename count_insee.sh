#!/bin/bash

# Fichier CSV
CSV="019HexaSmal.csv"

# # Extraire la première colonne (Code_commune_INSEE), ignorer l'entête,
# # trier et compter les valeurs uniques
# count=$(tail -n +2 "$CSV" | cut -d';' -f1 | sort -u | wc -l)

# echo "Nombre de Code_commune_INSEE différentes : $count"



awk -F';' 'NR>1 {seen[$1]++} END {print "Nombre de Code_commune_INSEE différentes :", length(seen)}' "$CSV"