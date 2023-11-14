#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <execinfo.h>
#include "server.h"

void uCoDExtended()
{
	static int freed = 0;
	if(freed)
		return;
	freed = 1;
}
void COD_Destructor()
{
	uCoDExtended();
}

void SV_ConnectionlessPacket( netadr_t from, msg_t *msg );
void Cbuf_Init( void );
void crash_handler(int sig)
{
	printf("####### crash_handler \n");
	void *array[10];
	size_t size = backtrace(array, 10);
	
	fprintf(stderr, "Error: signal: 0x%x {%d}\n", sig, sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

int main(int argc, char **argv)
{
	return ((int(*)(int,char**))0x80d4875)(argc, argv);
}

char *Scr_AddSourceBuffer(char *filename, char* a2, int a3);

void CoDExtended()
{
	static int loaded = 0;
	if(loaded)
		return;
	loaded = 1;

	unsetenv("LD_PRELOAD");
	signal(SIGSEGV, crash_handler);
	setbuf(stdout, NULL);
	mprotect((void *)0x08048000, 0x135000, PROT_READ | PROT_WRITE | PROT_EXEC);
	*(int*)0x8049ed8 = (int)main;
	srand (time(NULL));

	#if 0//CODPATCH == 1
	__call(0x8094C54, (int)Scr_GetCustomFunction);
	__call(0x80951C4, (int)Scr_GetCustomMethod);
	void *Sys_LoadDll(char *name, char *dest, int (**entryPoint)(int, ...), int (*systemcalls)(int, ...));
	__call(0x8092122, (int)Sys_LoadDll); //.text:08092122                 call    sub_80C5FE4
	__call(0x806BA27, (int)Cbuf_Init);
	__call(0x806C724, (int)Cbuf_Init);
	*(byte*)0x80854FF = 0xeb; //skip protocol check
	//jz      short loc_808C42E (patch rcon time)
	*(unsigned char*)0x808C41F = 0xeb;
	/*
		q3infoboom fix
	*/
	*(byte*)0x807f459 = 1;
	/*
		end 
	*/
	qboolean SV_ClientCommand(client_t*, msg_t*);
	__call(0x8087473, (int)SV_ClientCommand);
	//sendservercommand e game command > dropclient EXE_DISCONNECTED
	*(byte*)0x8085DBE = 0xeb;
	/*
		Direction Type Address         Text               
		--------- ---- -------         ----               
		Down      p    sub_808CDF8+35A call    sub_808CCCC
		Down      p    .text:0808D492  call    sub_808CCCC
	*/
	//0806CC80                 call    sub_808A94C
	//
	__call(0x808C8A1, (int)SV_ConnectionlessPacket);
	void SV_Shutdown(char *finalmsg);
	__call(0x806B831, (unsigned)SV_Shutdown);
	__call(0x806B888, (unsigned)SV_Shutdown);
	__call(0x806B8F1, (unsigned)SV_Shutdown);
	__call(0x806BADC, (unsigned)SV_Shutdown);
	__call(0x806D956, (unsigned)SV_Shutdown);
	__call(0x806DC85, (unsigned)SV_Shutdown);
	void SV_SpawnServer(char*);
	__call(0x8083DA4, (unsigned)SV_SpawnServer);
	__call(0x8083EA4, (unsigned)SV_SpawnServer);
	qboolean    Sys_GetPacket( netadr_t *net_from, msg_t *net_message );
	__jmp(0x80C71F0, (int)Sys_GetPacket);
	__call(0x808D258, (int)SV_MasterHeartBeat); //COD-1
	__call(0x808D280, (int)SV_MasterHeartBeat); //flatline
	//hooking the "quit" commands and when server shutdowns basically for reasons that lib_unload was being a prick
	__call(0x0806B8CE, (int)COD_Destructor);
	//0806CB0C to D since push offset <shutdown offset>
	*(int*)0x0806CB0D = (int)COD_Destructor;
	#endif
	
	//1.5
	void *Sys_LoadDll(char *name, char *dest, int (**entryPoint)(int, ...), int (*systemcalls)(int, ...));
	__call(0x809ae28, (int)Sys_LoadDll);
	qboolean SV_ClientCommand(client_t*, msg_t*);
	__call(0x808cfa6, (int)SV_ClientCommand);
	__call(0x80713bf, (int)SV_Init);
	__call(0x8093AD7, (int)SV_ConnectionlessPacket);

	//void (*SV_ExecuteClientMessage)(client_t*, msg_t*);
	//void custom_SV_ExecuteClientMessage(client_t* cl, msg_t* msg);  // Forward declaration
	//SV_ExecuteClientMessage = custom_SV_ExecuteClientMessage;
	//__jmp(0x808cdd0, (int)SV_ExecuteClientMessage);
}