#include <stdio.h> 

main()
{	
	int i = 1;
	while (getchar() != 'h')
		i++;
	
	int j = -1;
	while (getchar() != 'h')
		j++;

	if (i >= j)
		printf("go");
	else 
		printf("no");
}