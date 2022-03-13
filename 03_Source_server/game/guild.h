---Rechercher :

typedef struct SGuildMemberPacketData
{   
	DWORD pid;
	BYTE grade;
	BYTE is_general;
	BYTE job;
	BYTE level;
	DWORD offer;
	BYTE name_flag;
	char name[CHARACTER_NAME_MAX_LEN+1];
} TGuildMemberPacketData;
//////////////////////////////////////////////////////////////////////////////////////
Remplacer :

typedef struct SGuildMemberPacketData
{   
	DWORD pid;
	BYTE byGrade;
	BYTE byIsGeneral;
	BYTE byJob;
	int	 byLevel;
	DWORD dwOffer;
	BYTE byNameFlag;
} TGuildMemberPacketData;

#######################################################################

Rechercher :

void		ChangeMemberData(DWORD pid, DWORD offer, BYTE level, BYTE grade);

//////////////////////////////////////////////////////////////////////////////////////

Remplacer :

void		ChangeMemberData(DWORD pid, DWORD offer, int level, BYTE grade);

#######################################################################

---Rechercher :

SGuildMember(DWORD pid, BYTE grade, BYTE is_general, BYTE job, BYTE level, DWORD offer_exp, char* name);

//////////////////////////////////////////////////////////////////////////////////////

Remplacer :

SGuildMember(DWORD pid, BYTE grade, BYTE is_general, BYTE job, int level, DWORD offer_exp, char* name);

#######################################################################

--Rechercher :

	DWORD pid; // player Ĺ×ŔĚşíŔÇ id; primary key
	BYTE grade; // ±ćµĺ»óŔÇ ÇĂ·ąŔĚľîŔÇ °č±Ţ 1 to 15 (1ŔĚ ÂŻ)
	BYTE is_general;
	BYTE job;
	BYTE level;
	DWORD offer_exp; // °řÇĺÇŃ °ćÇčÄˇ
	BYTE _dummy;

//////////////////////////////////////////////////////////////////////////////////////

Remplacer :

	DWORD pid; // player Ĺ×ŔĚşíŔÇ id; primary key
	BYTE grade; // ±ćµĺ»óŔÇ ÇĂ·ąŔĚľîŔÇ °č±Ţ 1 to 15 (1ŔĚ ÂŻ)
	BYTE is_general;
	BYTE job;
	int level;
	DWORD offer_exp; // °řÇĺÇŃ °ćÇčÄˇ
	BYTE _dummy;

#######################################################################

---Rechercher:

void		LevelChange(DWORD pid, BYTE level);

//////////////////////////////////////////////////////////////////////////////////////

Remplacer :

void		LevelChange(DWORD pid, int level);
