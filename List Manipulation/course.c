#include "course.h"

Course courseCreate(String code, String programName, String name, int year, String period, int enrollments[4], double prevision) {
	Course newCourse;
	strcpy_s(newCourse.code, sizeof(newCourse.code), code);
	strcpy_s(newCourse.programName, sizeof(newCourse.programName), programName);
	strcpy_s(newCourse.name, sizeof(newCourse.name), name);
	newCourse.year = year;
	strcpy_s(newCourse.period, sizeof(newCourse.period), period);
	newCourse.enrollments[4] = enrollments[4];
}

void coursePrint(Course course){
	printf("Código: %s\n", course.code);
	printf("Nome do curso: %s\n", course.programName);
	printf("Nome da disciplina: %s\n", course.name);
	printf("Ano a ser lecionado: %d\n", course.year);
	printf("Semestre a ser lecionado: %s\n", course.period);
	printf("Inscrições das unidades curriculares: %d", course.enrollments);
	printf("Ano de previsão %d", course.prevision);
}