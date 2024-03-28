#ifndef __STATS_MANAGER_H__
#define __STATS_MANAGER_H__

#include "cocos2d.h"
#include "../WorkingWithData/SQLiteManager.h"

USING_NS_CC;
class Player;
class StatsManager
{
public:
	static StatsManager* getInstance(Player* _plr);

	bool upgrade(std::string tyleStat);
private:
	SQLiteManager* dbManager;
	static StatsManager* _instance;
	Player* _player;
	int _amount;
};

#endif // !__STATS_MANAGER_H__