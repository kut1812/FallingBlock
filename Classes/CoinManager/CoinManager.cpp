#include "CoinManager.h"
#include "AudioEngine.h"

CoinManager* CoinManager::_instance;

CoinManager* CoinManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new CoinManager();
    }
    return _instance;
}
