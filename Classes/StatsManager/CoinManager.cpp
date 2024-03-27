#include "StatsManager.h"
#include "AudioEngine.h"
#include "../Character/Player.h"

StatsManager* StatsManager::_instance;

StatsManager* StatsManager::getInstance(Player* _plr)
{
    if (_instance == nullptr)
    {
        _instance = new StatsManager();
    }
    _instance->_player = _plr;
    _instance->dbManager = SQLiteManager::getInstance();
    return _instance;
}

void StatsManager::active(std::string tyleStat)
{
    if (_player->getMoney() >= 10) {
        _player->decreaseMoney(10);
        if (tyleStat == "skull speed") {
            _player->setMovementLevel(1);
        }
        else if (tyleStat == "block speed") {
            _player->setMovementLevel(1);
        }
        else if (tyleStat == "skill duration") {
            _player->setMovementLevel(1);
        }
        else if (tyleStat == "life spawn") {
            _player->setMovementLevel(1);
        }
    }
    SQLiteManager::PlayerInfo playerI4 = dbManager->getPlayerById(1);
    dbManager->setPlayerInfo(1, playerI4.movement_speed, playerI4.life_spawn, playerI4.block_speed, playerI4.skill_duration);
}

void StatsManager::upgrade(std::string tyleStat)
{
    if (_player->getMoney() >= 5) {
        _player->decreaseMoney(5);
        if (tyleStat == "skull speed") {
            _player->setMovementLevel(_player->getMovementLevel() + 1);
        }
        else if (tyleStat == "block speed") {
            _player->setBlockSpeedLevel(_player->getBlockSpeedLevel() + 1);
        }
        else if (tyleStat == "skill duration") {
            _player->setSkillDurationLevel(_player->getSkillDurationLevel() + 1);
        }
        else if (tyleStat == "life spawn") {
            _player->setLifeSpawnLevel(_player->getLifeSpawnLevel() + 1);
        }
        SQLiteManager::PlayerInfo playerI4= dbManager->getPlayerById(1);
        dbManager->setPlayerInfo(1, playerI4.movement_speed, playerI4.life_spawn, playerI4.block_speed, playerI4.skill_duration);
    }
}

