#include <stdio.h>

/* print Celsius-Fahrenheit table
	for celsius = 0, 10, ..., 150 */
main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;		/* lower limit of temperature table */
	upper = 150;	/* upper limit */
	step = 10;		/* step size */

	printf("Degrees Celsius\n");
	printf("     Degrees Fahrenheit\n");
	celsius = lower;
	while (celsius <= upper) {
		fahr = celsius / (5.0/9.0) + 32.0;
		printf("%3.0f %6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
