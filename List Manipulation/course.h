typedef char String[258];

typedef struct course {
	char code[256]; // INF32144
	String programName; // INF
	String name; // Matematica I
	int year; // 1
	String period; // 1
	int enrollments[4];
	double prevision;
} Course;

Course courseCreate(String code, String programName, String name, int year, String period, int enrollments[4], double prevision);

void coursePrint(Course course);
