#include "foo.h"
#include <stdio.h>

int dosomethingfoo(int x)
{
	int retVal=0;
	if(x)
	{
		retVal = 1;
		//printf("it is foo true");
	}
	else
	{
		//printf("it is not foo true");
	}

	return retVal;
}

