#ifndef watches_h
#define watches_h

typedef struct {

    char brand[20];
    char model[20];
    char mekanism_type[20];
    char case_material[20];
    int case_diameter;
    int case_thickness;
    char glass_type[10];
    int water_resistance;
    int power_reserve;
    char bracelet_type[10];
    int price;

} watches;

#endif