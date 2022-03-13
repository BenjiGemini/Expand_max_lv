---Rechercher :
#######################################################################

BYTE	bLevel;
//(typedef struct SMember)

Remplacer par :
#######################################################################

int	bLevel;

---Chercher :
#######################################################################

		BYTE		GetMemberMaxLevel();
		BYTE		GetMemberMinLevel();

Changer en :
#######################################################################

		int		GetMemberMaxLevel();
		int		GetMemberMinLevel();

---Modifier :
#######################################################################

		void		RequestSetMemberLevel(DWORD pid, BYTE level);
		void		P2PSetMemberLevel(DWORD pid, BYTE level);

Comme ca :
#######################################################################

		void		RequestSetMemberLevel(DWORD pid, int level);
		void		P2PSetMemberLevel(DWORD pid, int level);
