#pragma once

#include "list.h"
#include "map.h"

/**
 * @brief Loads patients information from a file into a list.
 * 
 * @param list [in] List to save information in.
 */
void loadp(PtList list);

/**
 * @brief Loads regions indormation from a file into a map.
 * 
 * @param map [in] Map to save information in.
 */
void loadr(PtMap map);

/**
 * @brief Clears the given map and list if they are not already empty.
 * 
 * @param list [in] List to clear.
 * @param map [in] Map to clear.
 */
void clear(PtList list, PtMap map);

/**
 * @brief Calculates the average age of deceased, isolated and released patients and prints it to the console.
 *        Patients that we can't calculate age from are not taken into account.
 * 
 * @param list [in] List to get information from.
 */
void average(PtList list);

/**
 * @brief Shows the contamination sequence of a given patient by his id.
 * 
 * @param list [in] List to get patient information from.
 */
void follow(PtList list);

/**
 * @brief Calculates and shows the percentage of each of the genders in the list.
 * 
 * @param list [in] List to get patient information from.
 */
void sex(PtList list);

/**
 * @brief Shows information about a patient given his id.
 * 
 * @param list [in] List to get the patient information from.
 */
void show(PtList list);

/**
 * @brief Shows the oldest patient of each gender accoding to their birthYear.
 * 
 * @param list [in] List to get patients information from.
 */
void oldest(PtList list);

/**
 * @brief Creates a matrix of 6x3 with the number of patients isolated, deceased and released by their age group.
 *        Age groups: [0-15], [16-30], [31-45], [46-60], [61-75], [76...[
 * 
 * @param list [in] Patient list to get information from.
 */
void matrix(PtList list);

/**
 * @brief This function prints all regions in alphabetical order to the console.
 * 
 * @param map [in] Map of regions to print.
 */
void regions(PtMap map);