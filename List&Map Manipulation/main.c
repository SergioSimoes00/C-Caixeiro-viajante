/* PROJETO ATAD 2019-20
* Identificação dos alunos:
*
*      Número: 180221033 | Nome: Fábio Oliveira
*      Número: 180221008 | Nome: Sérgio Simões
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "commands.h"
#include "utils.h"

// Defines a ney char array type of size 255 called String.
typedef char String[255];

/**
 * @brief Prints the commands menu to the console.
 * 
 */
void printCommandsMenu();

/**
 * @brief Asks the user to press ENTER to continue using with the program.
 * 
 */
void continueCheck();

/*
* This program loads information of patients and regions from files into collections and
* let's the user use various commands/indicators to get statistics and information about those
* patients and regions.
*/
int main(int argc, char** argv) {
	system("clear");

	// Collections to be used throughout the program.
	PtList patientList = listCreate(3100);
	PtMap regionsMap = mapCreate(18);

	// Command interpreter.
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit) {
		system("clear");
		printCommandsMenu();
		fgets(command, sizeof(command), stdin);

		command[strlen(command) - 1] = '\0';
        
		if (equalsStringIgnoreCase(command, "QUIT")) {
			system("clear");
			quit = 1;
		}
		else if (equalsStringIgnoreCase(command, "LOADP")) {
			system("clear");
			loadp(patientList);
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "LOADR")) {
			system("clear");
			loadr(regionsMap);
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			system("clear");
			clear(patientList, regionsMap);
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE")) {
			system("clear");
			average(patientList);
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW")) {
			system("clear");
			follow(patientList);
			while( getchar() != '\n' );
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "SEX")) {
			system("clear");
			sex(patientList);
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			system("clear");
			show(patientList);
			while( getchar() != '\n' );
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "TOP5")) {
			system("clear");
			printf("Comando TOP5 nao implementado.\n");
			//top5(patientList);
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "OLDEST")) {
			system("clear");
			oldest(patientList);
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "GROWTH")) {
			system("clear");
			printf("Comando GROWTH nao implementado.\n");
			//growth(patientList);
			//while( getchar() != '\n' );
			continueCheck();
		}	
		else if (equalsStringIgnoreCase(command, "MATRIX")) {
			system("clear");
			matrix(patientList);
			continueCheck();
		}
		else if (equalsStringIgnoreCase(command, "REGIONS")) {
			system("clear");
			regions(regionsMap);
			continueCheck();
		}	
		else if (equalsStringIgnoreCase(command, "REPORT")) {
			system("clear");
			printf("Comando REPORT nao implementado.\n");
		}
		else {
			system("clear");
			printf("\n%s : Comando não encontrado.\n", command);
		}
	}

	// Release of memory allocated by the colections.
	listDestroy(&patientList);
	mapDestroy(&regionsMap);

	printf("\nProgram closed, bye!\n\n");

	return (EXIT_SUCCESS);
}

void continueCheck(){
	printf("\nPress Enter to Continue\n");
	while( getchar() != '\n' );
}

void printCommandsMenu() {
	printf("\n===================================================================================");
	printf("\n                          	PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOADP, LOADR, CLEAR).");
	printf("\nB. Simple Indicators and searches (AVERAGE, FOLLOW, MATRIX, OLDEST, RELEASED, SEX, SHOW, TOP5, GROWTH).");
	printf("\nC. Advanced indicators (REGIONS, REPORTS).");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}