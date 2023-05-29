#include <stdio.h>


int main(int argc, char **argv)
{
	int i = 1;
	if (argc == 1)
	{
		printf("ARGS: Empty");
		printf("\nARGS COUNT: 0\n");
		return (0);
	}
	printf("ARGS: ");
	while(argv[i])
	{
		printf("%s, ", argv[i]);
		i++;
	}
	printf("\nARGS COUNT: %d\n", argc - 1);
	return (0);
}
