#include "EntityCache.h"

void C_EntityCache::UpdateFriends()
{
	static size_t nCurrentSize, nOldSide;
	const auto& Players = Groups[GroupType_t::PLAYERS_ALL];
	nCurrentSize = Players.size();

	if (nCurrentSize != nOldSide)
	{
		for (const auto& Player : Players)
		{
			m_bFriends[Player->entindex()] = Player->IsSteamFriend();
		}
	}
}

void C_EntityCache::Fill()
{
	C_BaseEntity *_pLocal = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (_pLocal && _pLocal->IsInValidTeam())
	{
		pLocal = _pLocal;
		pLocalWeapon = pLocal->GetActiveWeapon();

		for (int n = 1; n < I::EntityList->GetHighestEntityIndex(); n++)
		{
			C_BaseEntity *pEntity = I::EntityList->GetClientEntity(n);

			if (!pEntity || pEntity->IsDormant())
				continue;

			switch (pEntity->GetClassId())
			{
				case CTFPlayer:
				{
					Groups[GroupType_t::PLAYERS_ALL].push_back(pEntity);
					Groups[pEntity->m_iTeamNum() != pLocal->m_iTeamNum() ? GroupType_t::PLAYERS_ENEMIES : GroupType_t::PLAYERS_TEAMMATES].push_back(pEntity);
					break;
				}
				
				default: break;
			}
		}
	}

	UpdateFriends();
}

void C_EntityCache::Clear()
{
	pLocal = nullptr;
	pLocalWeapon = nullptr;

	for (auto &group : Groups)
		group.second.clear();
}

const std::vector<C_BaseEntity *> &C_EntityCache::GetGroup(const GroupType_t &group)
{
	return Groups[group];
}

