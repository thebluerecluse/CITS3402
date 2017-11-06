#include "project2.h"

int send_length(int size, char sob)
{
	int tmp = 0;
	if (sob == 's')
	{
		tmp = SITE_R*SITE_C/size;
	}
	else
	{
		tmp = BOND_R*BOND_C/size;
	}
	return tmp;
}
