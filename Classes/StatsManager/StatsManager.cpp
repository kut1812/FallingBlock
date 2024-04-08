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

bool StatsManager::upgrade(std::string tyleStat)
{
    if (tyleStat == "skull speed" && _player->getMovementLevel() < 300 && _player->getMoney() >= _player->getMovementLevel() * 5) {
        _player->decreaseMoney(_player->getMovementLevel() * 5);
        _player->movementLevel += 1;
        dbManager->setPlayerInfo(1, _player->movementLevel, _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), 1, _player->getX2Jump() ? 1 : 0, _player->getShield() ? 1 : 0);
        return true;
    }
    else if (tyleStat == "block speed" && _player->getBlockSpeedLevel() < 300 && _player->getMoney() >= _player->getBlockSpeedLevel() * 5) {
        _player->decreaseMoney(_player->getBlockSpeedLevel() * 5);
        _player->setBlockSpeedLevel(_player->getBlockSpeedLevel() + 1);
        dbManager->setPlayerInfo(1, _player->movementLevel, _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), 1, _player->getX2Jump() ? 1 : 0, _player->getShield() ? 1 : 0);
        return true;
    }
    else if (tyleStat == "skill duration" && _player->getSkillDurationLevel() < 300 && _player->getMoney() >= _player->getSkillDurationLevel() * 5) {
        _player->decreaseMoney(_player->getSkillDurationLevel() * 5);
        _player->setSkillDurationLevel(_player->getSkillDurationLevel() + 1);
        dbManager->setPlayerInfo(1, _player->movementLevel, _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), 1, _player->getX2Jump() ? 1 : 0, _player->getShield() ? 1 : 0);
        return true;
    }
    else if (tyleStat == "life spawn" && _player->getLifeSpawnLevel() < 300 && _player->getMoney() >= _player->getLifeSpawnLevel() * 5) {
        _player->decreaseMoney(_player->getLifeSpawnLevel() * 5);
        _player->setLifeSpawnLevel(_player->getLifeSpawnLevel() + 1);
        dbManager->setPlayerInfo(1, _player->movementLevel, _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), 1, _player->getX2Jump() ? 1 : 0, _player->getShield() ? 1 : 0);
        return true;
    }
    //SQLiteManager::PlayerInfo playerI4= dbManager->getPlayerById(1);
    return false;
}

