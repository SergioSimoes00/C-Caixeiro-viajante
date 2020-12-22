#pragma once

typedef struct region{
    char name[40];      // Name
    char capital[40];   // Capital
    int population;     // Population count
    float area;         // Area
} Region;

/**
 * @brief Creates an instance of region.
 * 
 * @param name [in] Name.
 * @param capital [in] Capital.
 * @param population [in] Population count.
 * @param area [in] Area.
 * @return Region Instance of region.
 */
Region regionCreate(char *name, char *capital, int population, float area);

/**
 * @brief Prints information about a given region to the console.
 * 
 * @param region [in] Region to get information from.
 */
void regionPrint(Region region);