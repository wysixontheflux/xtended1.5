#include "server.h"

void SV_Init( void )
{
	void (*init)( void );
	*(int*)&init = 0x80913B3;

	init();
	
	if (clientsize != sizeof(client_t))
	{
		cprintf(PRINT_UNDERLINE | PRINT_ERR, "ERROR: client_t size doesn't fit clientsize!!! %i != %i\n", sizeof(client_t), clientsize);
	}
	else
	{
		cprintf(PRINT_UNDERLINE | PRINT_GOOD, "GOOD: SIZE IS SAME OF CLIENT\n");
	}
}