Chercher :

BYTE level = (BYTE)strtoul(row[4], (char**) NULL, 10);

Remplacer :

int level = (int)strtoul(row[4], (char**) NULL, 10);

#######################################################################

Chercher :

sys_log(0, "GUILD: AddMember PID %u, grade %u, job %u, level %u, offer %u, name %s ptr %p",

Remplacer :

sys_log(0, "GUILD: AddMember PID %u, grade %u, job %u, level %d, offer %u, name %s ptr %p",

#######################################################################
        
Remplacer la fonction :

void CGuild::ChangeMemberData(DWORD pid, DWORD offer, BYTE level, BYTE grade)

Par ceci :

void CGuild::ChangeMemberData(DWORD pid, DWORD offer, int level, BYTE grade)
{
	TGuildMemberContainer::iterator cit = m_member.find(pid);

	if (cit == m_member.end())
		return;

	cit->second.offer_exp = offer;
	cit->second.level = level;
	cit->second.grade = grade;
	cit->second._dummy = 0;

	TPacketGCGuild pack;
	TGuildMemberPacketData mbData;
	pack.header = HEADER_GC_GUILD;
	pack.subheader = GUILD_SUBHEADER_GC_LIST;
	pack.size = sizeof(TPacketGCGuild);
	pack.size += sizeof(TGuildMemberPacketData);

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPDESC d = (*it)->GetDesc();
		if (d)
		{
			TEMP_BUFFER buf;

			buf.write(&pack, sizeof(pack));

			mbData.byNameFlag = 0;
			mbData.byGrade = cit->second.grade;
			mbData.byIsGeneral = cit->second.is_general;
			mbData.byJob = cit->second.job;
			mbData.byLevel = cit->second.level;
			mbData.dwOffer = cit->second.offer_exp;
			mbData.pid = cit->second.pid;
			buf.write(&mbData, sizeof(TGuildMemberPacketData));

			d->Packet(buf.read_peek(), buf.size());
		}
	}
}

        #######################################################################
        
Remplacer la fonction :

void CGuild::LevelChange(DWORD pid, BYTE level)

Par ceci :

void CGuild::LevelChange(DWORD pid, int level)
{
	TGuildMemberContainer::iterator cit = m_member.find(pid);

	if (cit == m_member.end())
		return;

	cit->second.level = level;

	TPacketGuildChangeMemberData gd_guild;

	gd_guild.guild_id = GetID();
	gd_guild.pid = pid;
	gd_guild.offer = cit->second.offer_exp;
	gd_guild.grade = cit->second.grade;
	gd_guild.level = level;

	db_clientdesc->DBPacket(HEADER_GD_GUILD_CHANGE_MEMBER_DATA, 0, &gd_guild, sizeof(gd_guild));

	TPacketGCGuild pack;
	TGuildMemberPacketData mbData;
	pack.header = HEADER_GC_GUILD;
	pack.subheader = GUILD_SUBHEADER_GC_LIST;
	pack.size = sizeof(TPacketGCGuild);
	pack.size += sizeof(TGuildMemberPacketData);
	cit->second._dummy = 0;

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPDESC d = (*it)->GetDesc();

		if (d)
		{
			TEMP_BUFFER buf;

			buf.write(&pack, sizeof(pack));

			mbData.byNameFlag = 0;
			mbData.byGrade = cit->second.grade;
			mbData.byIsGeneral = cit->second.is_general;
			mbData.byJob = cit->second.job;
			mbData.byLevel = cit->second.level;
			mbData.dwOffer = cit->second.offer_exp;
			mbData.pid = cit->second.pid;
			buf.write(&mbData, sizeof(TGuildMemberPacketData));

			d->Packet(buf.read_peek(), buf.size());
		}
	}
}

        #######################################################################
        
Remplacer la fonction :

bool CGuild::OfferExp(LPCHARACTER ch, int amount)

Par ceci :

bool CGuild::OfferExp(LPCHARACTER ch, int amount)
{
	TGuildMemberContainer::iterator cit = m_member.find(ch->GetPlayerID());

	if (cit == m_member.end())
		return false;

	if (m_data.exp+amount < m_data.exp)
		return false;

	if (amount < 0)
		return false;

	if (ch->GetExp() < (DWORD) amount)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<±ćµĺ> Á¦°řÇĎ°íŔÚ ÇĎ´Â °ćÇčÄˇ°ˇ ł˛Ŕş °ćÇčÄˇş¸´Ů ¸ą˝Ŕ´Ď´Ů."));
		return false;
	}

	if (ch->GetExp() - (DWORD) amount > ch->GetExp())
	{
		sys_err("Wrong guild offer amount %d by %s[%u]", amount, ch->GetName(), ch->GetPlayerID());
		return false;
	}

	ch->PointChange(POINT_EXP, -amount);

	TPacketGuildExpUpdate guild_exp;
	guild_exp.guild_id = GetID();
	guild_exp.amount = amount / 100;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_EXP_UPDATE, 0, &guild_exp, sizeof(guild_exp));
	GuildPointChange(POINT_EXP, amount / 100, true);

	cit->second.offer_exp += amount / 100;
	cit->second._dummy = 0;

	TPacketGCGuild pack;
	TGuildMemberPacketData mbData;
	pack.header = HEADER_GC_GUILD;
	pack.subheader = GUILD_SUBHEADER_GC_LIST;
	pack.size = sizeof(TPacketGCGuild);
	pack.size += sizeof(TGuildMemberPacketData);

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		LPDESC d = (*it)->GetDesc();
		if (d)
		{

			TEMP_BUFFER buf;

			buf.write(&pack, sizeof(pack));

			mbData.byNameFlag = 0;
			mbData.byGrade = cit->second.grade;
			mbData.byIsGeneral = cit->second.is_general;
			mbData.byJob = cit->second.job;
			mbData.byLevel = cit->second.level;
			mbData.dwOffer = cit->second.offer_exp;
			mbData.pid = cit->second.pid;
			buf.write(&mbData, sizeof(TGuildMemberPacketData));

			d->Packet(buf.read_peek(), buf.size());
		}
	}

	SaveMember(ch->GetPlayerID());

	TPacketGuildChangeMemberData gd_guild;

	gd_guild.guild_id = GetID();
	gd_guild.pid = ch->GetPlayerID();
	gd_guild.offer = cit->second.offer_exp;
	gd_guild.level = ch->GetLevel();
	gd_guild.grade = cit->second.grade;

	db_clientdesc->DBPacket(HEADER_GD_GUILD_CHANGE_MEMBER_DATA, 0, &gd_guild, sizeof(gd_guild));
	return true;
}

        #######################################################################
        
Trouver :

void CGuild::SendListPacket(LPCHARACTER ch)

Remplacer :

void CGuild::SendListPacket(LPCHARACTER ch)
{
	/*
	   List Packet

	   Header
	   Count (byte)
	   [
	   ...
	   name_flag 1 - ŔĚ¸§Ŕ» ş¸ł»´ŔłÄ ľČş¸ł»´ŔłÄ
	   name CHARACTER_NAME_MAX_LEN+1
	   ] * Count

	 */
	LPDESC d;
	if (!(d=ch->GetDesc()))
		return;

	TPacketGCGuild pack;
	pack.header = HEADER_GC_GUILD;
	pack.size = sizeof(TPacketGCGuild);
	pack.subheader = GUILD_SUBHEADER_GC_LIST;

	pack.size += sizeof(TGuildMemberPacketData) * m_member.size();
    pack.size += (CHARACTER_NAME_MAX_LEN + 1) * m_member.size();

	TEMP_BUFFER buf;

	TGuildMemberPacketData mbData;

	buf.write(&pack,sizeof(pack));

	char c[CHARACTER_NAME_MAX_LEN+1];

	for (TGuildMemberContainer::iterator it = m_member.begin(); it != m_member.end(); ++it)
	{
		it->second._dummy = 1;

		mbData.byNameFlag = 1;
		mbData.byGrade = it->second.grade;
		mbData.byIsGeneral = it->second.is_general;
		mbData.byJob = it->second.job;
		mbData.byLevel = it->second.level;
		mbData.dwOffer = it->second.offer_exp;
		mbData.pid = it->second.pid;

		buf.write(&mbData, sizeof(TGuildMemberPacketData));

		strlcpy(c, it->second.name.c_str(), MIN(sizeof(c), it->second.name.length() + 1));

		buf.write(c, CHARACTER_NAME_MAX_LEN+1 );

		if ( test_server )
			sys_log(0 ,"name %s job %d  ", it->second.name.c_str(), it->second.job );
	}

	d->Packet(buf.read_peek(), buf.size());

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it != m_memberOnline.end(); ++it)
	{
		SendLoginPacket(ch, *it);
	}

	for (TGuildMemberP2POnlineContainer::iterator it = m_memberP2POnline.begin(); it != m_memberP2POnline.end(); ++it)
	{
		SendLoginPacket(ch, *it);
	}

}

        #######################################################################
        
Rechercher :

void CGuild::SendListOneToAll(DWORD pid)

Remplacer par :

void CGuild::SendListOneToAll(DWORD pid)
{

	TPacketGCGuild pack;
	pack.header = HEADER_GC_GUILD;
	pack.size = sizeof(TPacketGCGuild);
	pack.subheader = GUILD_SUBHEADER_GC_LIST;

	pack.size += sizeof(TGuildMemberPacketData);

	TGuildMemberPacketData mbData;

	char c[CHARACTER_NAME_MAX_LEN+1];
	memset(c, 0, sizeof(c));

	TGuildMemberContainer::iterator cit = m_member.find(pid);
	if (cit == m_member.end())
		return;

	for (TGuildMemberOnlineContainer::iterator it = m_memberOnline.begin(); it!= m_memberOnline.end(); ++it)
	{
		LPDESC d = (*it)->GetDesc();
		if (!d) 
			continue;

		TEMP_BUFFER buf;

		buf.write(&pack, sizeof(pack));

		cit->second._dummy = 1;

		mbData.byNameFlag = 1;
		mbData.byGrade = cit->second.grade;
		mbData.byIsGeneral = cit->second.is_general;
		mbData.byJob = cit->second.job;
		mbData.byLevel = cit->second.level;
		mbData.dwOffer = cit->second.offer_exp;
		mbData.pid = cit->second.pid;
		//buf.write(&(cit->second), sizeof(DWORD) * 3 +1);
		buf.write(&mbData, sizeof(TGuildMemberPacketData));
		buf.write(cit->second.name.c_str(), cit->second.name.length());
		buf.write(c, CHARACTER_NAME_MAX_LEN + 1 - cit->second.name.length());
		d->Packet(buf.read_peek(), buf.size());
	}
}

        #######################################################################
        
Chercher :

SGuildMember::SGuildMember(DWORD pid, BYTE grade, BYTE is_general, BYTE job, BYTE level, DWORD offer_exp, char* name)

Remplacer :

SGuildMember::SGuildMember(DWORD pid, BYTE grade, BYTE is_general, BYTE job, int level, DWORD offer_exp, char* name)
