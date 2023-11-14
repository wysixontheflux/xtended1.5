#include "shared.h"

void CoDExtended();

int __attribute__((visibility ("default"))) codextended_module_load()
{
	CoDExtended();
	return BUILDNUMBER;
}
void __attribute__ ((constructor)) __attribute__((visibility ("default"))) codextended_load(void)
{
	CoDExtended();
}
// Odd, isn't it? 1.5 destructor works (apparently it should work but the stdout is closed or something... cba to rewrite for now)
void __attribute__ ((destructor)) __attribute__((visibility ("default"))) codextended_unload( void )
{
	COD_Destructor();
}