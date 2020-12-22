#include <stdio.h>
#include <string.h>
#include "region.h"

Region regionCreate(char *name, char *capital, int population, float area){
    Region region;
    strcpy(region.name, name);
    strcpy(region.capital, capital);
    region.population = population;
    region.area = area;
    return region;
}

void regionPrint(Region region){
    printf("%s | %s | %d | %.3f", region.name, region.capital, region.population, region.area);
}