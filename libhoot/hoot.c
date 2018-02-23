#include "hoot.h"
#include <stdio.h>

int dosomethinghoot(int x)
{
	int retVal=0;
	if(x)
	{
		retVal = 1;
		printf("it is hoot true");
	}
	else
	{
		printf("it is not hoot true");
	}

	return retVal;
}

