---Chercher :
#######################################################################

	struct FPartyTotaler
	{
		int		total;

Remplacer par :
#######################################################################

	struct FPartyTotaler
	{
		long		total;

---Chercher :
#######################################################################

	struct FPartyDistributor
	{
		int		total;
		LPCHARACTER	c;
		int		x, y;
		DWORD		_iExp;
		int		m_iMode;
		int		m_iMemberCount;

		FPartyDistributor(LPCHARACTER center, int member_count, int total, DWORD iExp, int iMode) 

Remplacer :
#######################################################################

	struct FPartyDistributor
	{
		long		total;
		LPCHARACTER	c;
		int		x, y;
		DWORD		_iExp;
		int		m_iMode;
		int		m_iMemberCount;

		FPartyDistributor(LPCHARACTER center, int member_count, long total, DWORD iExp, int iMode) 
