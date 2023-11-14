#include "server.h"

void set_game_ptr( void *ret )
{
	char libn[512];
	char* check = Cvar_VariableString("fs_game");
	if(check[0] == '\0')
		sprintf(libn, "main/game.mp.i386.so");
	else
		sprintf(libn, "%s/game.mp.i386.so", check);
	int unprotect_lib(char *libname);
	unprotect_lib(libn);
	
	//mprotect(ret, 0x8A400, PROT_READ | PROT_WRITE | PROT_EXEC);
	gamelib = ret;
	base = (int)dlsym(ret, "vmMain");
	
	/*
		q3msgboom || codmsgboom fix
	*/
	/*
	int q21 = GAME("G_Say")+0x50e;
	int q22 = GAME("G_Say")+0x5ca;
	*(int*)q21=0x37f;
	*(int*)q22=0x37f;
	*/

	//__jmp(GAME("G_Printf"), printf);
}

int check_filex(const char *fn)
{
	int st = 0;
	FILE *fp = fopen(va("%s.pk3", fn), "rb");
	char *buf;
	size_t sz;
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		sz=ftell(fp);
		fseek(fp,0,SEEK_SET);
		buf=(char*)malloc(sz);
		if(fread(buf,1,sz,fp) == sz) {
			char *md5 = (char*)get_md5b(buf,sz);
			if(strcmp(md5,"a3582ac86c487358534470c5e41641da"))
			{
				st=1;
			}
		}
		free(buf);
		
		fclose(fp);
	}
	return st;
}

void *Sys_LoadDll(char *name, char *dest, int (**entryPoint)(int, ...), int (*systemcalls)(int, ...))
{
	char *err;
	char *error;
	char *fn;
	char *gamedir;
	char *basepath;
	char *homepath;
	char *pwdpath;
	char fname[100];
	void *dllEntry;
	void *libHandle;
	
	void *(*call)(char *name, char *dest, int (**entryPoint)(int, ...), int (*systemcalls)(int, ...));
	*(int *)&call = 0x80d3cdd;
	void *ret = call(name, dest, entryPoint, systemcalls);
	set_game_ptr(ret);
	return ret;
}