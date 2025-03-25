#include <stdio.h>
#include <string.h>
#include "watches.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "No file or scenario");
        return -1;
    }

    
    FILE *file = fopen(argv[1], "rb");

    if (file == NULL) {
        fprintf(stderr, "No such file: %s\n", file);
        return -2;
    }
    

    char scenario[10];
    strcpy(scenario, argv[2]);

    char add_scenario[10];
    if (argv[3] != NULL)   
        strcpy(add_scenario, argv[3]);
    
    int count = 0;

    printf("\n");

    watches w;


    if (!strcmp(scenario, "data_base")) {

        if (fread(&w, sizeof(watches), 1, file) != 1) {
            
            fprintf(stderr, "Can't read your file %s\n", file);
            fclose(file);
            return -3;
        
        }        

        while (fread(&w, sizeof(watches), 1, file) == 1) {

            count++;

            printf("#%d   Brand: %s \n\t Model: %s \n\t Mechanism Type: %s \n\t Case Material: %s \n\t Case Diameter: %d \n\t Case Thickness: %d \n\t Glass Type: %s \n\t Water Resistance: %d m \n\t Power Reserve: %d hours \n\t Bracelet Type: %s \n\t Price: %d USD\n\n", 
            count, w.brand, w.model, w.mekanism_type, w.case_material, w.case_diameter, 
            w.case_thickness, w.glass_type, w.water_resistance, w.power_reserve, 
            w.bracelet_type, w.price);

            if (!strcmp(add_scenario, "short") && count == 15) 
                return 1;

        }
    }

    else if (!strcmp(scenario, "stats")) {

        if (fread(&w, sizeof(watches), 1, file) != 1) {

            fprintf(stderr, "Can't read your file %s\n", file);
            fclose(file);
            return -3;
        
        }        
        
        double price = 0.0;
        
        while (fread(&w, sizeof(watches), 1, file) == 1) {
            price += w.price;
            count++;
        }

        double avg_price = (double) price / count;

        rewind(file);

        watches excellent;
        int max_wr = 0;
        int price_of_excellent = avg_price;

        while (fread(&w, sizeof(watches), 1, file) == 1) {
            
            if (w.water_resistance >= max_wr && w.price < price_of_excellent) {
            
                max_wr = w.water_resistance;
                excellent = w;
                price_of_excellent = w.price;
            
            }
        }

        fclose(file);

        printf("Our excellent for diving watches are:\n\n");
        printf("\tBrand: %s\n", excellent.brand);
        printf("\tModel: %s\n", excellent.model);
        printf("\tWR Class: %d m\n", excellent.water_resistance);
        printf("\tPrice: %d USD\n", price_of_excellent);
        printf("\n");

    }
}
