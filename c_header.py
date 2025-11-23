import csv

with open("019HexaSmal.csv", newline="", encoding="utf-8") as f:
    reader = csv.DictReader(f, delimiter=";") 
    print("Colonnes détectées :", reader.fieldnames)
    with open("codes_postaux.h", "w", encoding="utf-8") as out:
        out.write("#ifndef CODES_POSTAUX_H\n#define CODES_POSTAUX_H\n\n")
        out.write("typedef struct {\n")
        out.write("    const char *insee;\n")
        out.write("    const char *commune;\n")
        out.write("    const char *code_postal;\n")
        out.write("    const char *acheminement;\n")
        out.write("} CodePostal;\n\n")
        out.write("static const CodePostal codes_postaux[] = {\n")
        for row in reader:
            out.write(f'    {{ "{row["Code_commune_INSEE"]}", "{row["Nom_de_la_commune"]}", "{row["Code_postal"]}", "{row["Libellé_d_acheminement"]}" }},\n')
        out.write("};\n\n")
        out.write("static const int codes_postaux_count = sizeof(codes_postaux) / sizeof(codes_postaux[0]);\n\n")
        out.write("#endif\n")
