#include <stdio.h>
#include "watches.h"

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        fprintf(stderr, "Not enough args\n");
        return -1;
    }


    FILE* file1 = fopen(argv[1], "rb");
    
    if (file1 == NULL) {
        fprintf(stderr, "No such file: %s\n", file1);
        return -2;
    }

    FILE* file2 = fopen(argv[2], "wb");

    if (file2 == NULL) {

        fprintf(stderr, "No such file: %s\n", file2);
        fclose(file1);
        return -3;
    
    }
    

    int c;
    while ((c = fgetc(file1)) != EOF)
        if (c == '\n') 
            break;

    watches w;

    int count;
    
    while ((count = fscanf(file1, "%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,],%d,%d,%[^,],%d\n", 
        w.brand, w.model, w.mekanism_type, w.case_material, &w.case_diameter, &w.case_thickness, 
        w.glass_type, &w.water_resistance, &w.power_reserve, w.bracelet_type, &w.price)) != EOF) {

            if (count != 11) {
                
                fprintf(stderr, "Not enough args to read: less than %d\n", count);
                fclose(file1); fclose(file2);
                return -4;

            } 

            if (fwrite(&w, sizeof(watches), 1, file2) != 1) {
                
                fprintf(stderr, "Can't write into the file %s\n", file2);
                fclose(file1); fclose(file2);
                return -5;

            }
        }
        
    fclose(file1); fclose(file2);
}
