---Rechercher :
#######################################################################

void CParty::P2PSetMemberLevel(DWORD pid, BYTE level)

Remplacer par :
#######################################################################

void CParty::P2PSetMemberLevel(DWORD pid, int level)

---Rechercher :
#######################################################################

BYTE CParty::GetMemberMaxLevel()
{
	BYTE bMax = 0;

Remplacer :
#######################################################################

int CParty::GetMemberMaxLevel()
{
	int bMax = 0;

---Rechercher :
#######################################################################

BYTE CParty::GetMemberMinLevel()
{
	BYTE bMin = PLAYER_MAX_LEVEL_CONST;

Remplacer par :
#######################################################################

int CParty::GetMemberMinLevel()
{
	int bMin = PLAYER_MAX_LEVEL_CONST;

---Rechercher :
#######################################################################

void CParty::RequestSetMemberLevel(DWORD pid, BYTE level)

Modifier :
#######################################################################

void CParty::RequestSetMemberLevel(DWORD pid, int level)
