#ifndef SERVER_H
#define SERVER_H

/*
    Still not quite happy with the including of some files.
    //richard
*/

#include "shared.h"
#include <sys/time.h>

#define svsclients_ptr 0x83CCD90
#define clientsize 371124

#define SVF_NOCLIENT       		0x00000001
#define SVF_BROADCAST      		0x00000020
#define SVF_CAPSULE        		0x00000200  // use capsule for collision detection
#define SVF_SINGLECLIENT   		0x00000800 // only send to a single client (entityShared_t->singleClient)
#define SVF_NOTSINGLECLIENT		0x00002000 // send entity to everyone but one client

#define svs_time (*(int*)0x83CCD88)

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

typedef struct {
  int idk33[4];
  int svFlags;
  int singleClient;
  char pad[256];
  int idk;
} entityShared_t;

typedef struct {
  entityState_t s;
  entityShared_t r;
} sharedEntity_t;

typedef enum {
	NA_BOT,
	NA_BAD,                 // an address lookup failed
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	NA_IPX,
	NA_BROADCAST_IPX
} netadrtype_t;

typedef struct {
	netadrtype_t type;
	union {
		byte ip[4];
		unsigned int _ip;
	};
	byte ipx[10];

	unsigned short port;
} netadr_t; //size = 0x14 (20)

#define MAX_CHALLENGES 1024

typedef sharedEntity_t* (*SV_GentityNum_t)( int num );
extern SV_GentityNum_t SV_GentityNum;

void SV_Init( void );
void SV_AuthorizeIpPacket( netadr_t from );

extern cvar_t  *sv_maxclients;
extern cvar_t *sv_privateClients;
extern cvar_t *g_gametype;
extern cvar_t *mapname;
extern cvar_t *sv_hostname;
extern cvar_t *sv_maxRate;
extern cvar_t *sv_maxPing;
extern cvar_t *sv_minPing;
extern cvar_t *sv_floodProtect;
extern cvar_t *sv_allowAnonymous;
extern cvar_t *sv_showCommands;
extern cvar_t *sv_pure;
extern cvar_t *sv_serverid;
extern cvar_t *rconPassword;
extern cvar_t *sv_privatePassword;
extern cvar_t *sv_fps;
extern cvar_t *sv_timeout;
extern cvar_t *sv_zombietime;
extern cvar_t *sv_allowDownload;
extern cvar_t *sv_master1;
extern cvar_t *sv_master2;
extern cvar_t *sv_master3;
extern cvar_t *sv_master4;
extern cvar_t *sv_master5;
extern cvar_t *sv_reconnectlimit;
extern cvar_t *sv_showloss;
extern cvar_t *sv_padPackets;
extern cvar_t *sv_killserver;
extern cvar_t *sv_onlyVisibleClients;
extern cvar_t *sv_showAverageBPS;
extern cvar_t *sv_mapRotation;
extern cvar_t *sv_mapRotationCurrent;
extern cvar_t *shortversion;
extern cvar_t *protocol;
extern cvar_t* dedicated;
extern cvar_t* sv_running;
extern cvar_t *sv_disableClientConsole;

extern cvar_t *cl_allowDownload; //the client will locally change any cvars to match the SYSTEMINFO cvars

#define MAX_MASTER_SERVERS 5
extern cvar_t* sv_master[MAX_MASTER_SERVERS];

typedef void (QDECL *NET_OutOfBandPrint_t)( netsrc_t net_socket, netadr_t adr, const char *format, ... );
extern NET_OutOfBandPrint_t NET_OutOfBandPrint;

typedef qboolean (*NET_StringToAdr_t)( const char *s, netadr_t *a );
extern NET_StringToAdr_t NET_StringToAdr;

extern netadr_t authorizeAddress;
extern netadr_t masterAddress;

typedef enum {
	CS_FREE,        // can be reused for a new connection
	CS_ZOMBIE,      // client has been disconnected, but don't reuse connection for a couple seconds
	CS_CONNECTED,   // has been assigned to a client_t, but no gamestate yet
	CS_PRIMED,      // gamestate has been sent, but client hasn't sent a usercmd
	CS_ACTIVE       // client is fully in game
} clientState_t;

typedef struct {
	netsrc_t sock;
	int dropped;
	netadr_t remoteAddress;
	int qport;
	/* lot more bs here */
} netchan_t;

typedef struct client_s
{
  int state;
  int unknown4;
  int unknown8;
  char userinfo[1024];
  char field_40C;
  char gap_40D[66047];
  int reliableSequence;
  int reliableAcknowledge;
  char gap_10614;
  char gap_10615[7];
  int gamestateMessageNum;
  int challenge;
  usercmd_t lastUsercmd;
  int lastClientCommand;
  char lastClientCommandString[1024];
  unsigned int gentity;
  char name[32];
  char downloadName[64];
  int download;
  int downloadSize;
  int downloadCount;
  int junk;
  int gap_10AB4;
  char gap_10AB8[84];
  int lastPacketTime;
  int lastConnectTime;
  int nextSnapshotTime;
  char gap_10B18[269704];
  int ping;
  int rate;
  int snapshotMsec;
  int pureAuthentic;
  netchan_t netchan;
  char lazy_to_figure_out_so_fill_it_up[32996];
} client_t;

/*
from 1.5

typedef enum {
  UCMD_BUTTONS = 8, //for messagemode/console, cl_run (+speed) (aim down the sight)
  UCMD_WBUTTONS, //+reload, +leanright +leanleft
  UCMD_FORWARDMOVE = 23,
  UCMD_RIGHTMOVE,
  UCMD_UPMOVE
} usercmd_offset;


typedef struct usercmd_s {
	int serverTime;
	byte buttons;
	byte wbuttons;
	byte weapon;
	byte flags;
    byte unknown1[13];
    / *
        forward = 127
        back = 129
        right = 127
        left = 129
        up = 127
        prone = 129
    * /
	signed char forwardmove, rightmove, upmove;
	byte doubleTap;             // Arnout: only 3 bits used

	// rain - in ET, this can be any entity, and it's used as an array
	// index, so make sure it's unsigned
	byte identClient;           // NERVE - SMF
} usercmd_t;
*/

extern client_t** clients;
extern cvar_t  *sv_maxclients;

typedef void (*SV_DropClient_t)(client_t*, const char* reason);
extern SV_DropClient_t SV_DropClient;

client_t* getclient(int);

typedef void (*getuserinfo_t)( int index, char *buffer, int bufferSize );
typedef void (*setuserinfo_t)(int,const char*);

extern getuserinfo_t getuserinfo;
extern setuserinfo_t setuserinfo;

#endif // SERVER_H
