// JSONManager.cpp
#include "JSONManager.h"

USING_NS_CC;

JSONManager* JSONManager::instance = nullptr;

JSONManager* JSONManager::getInstance()
{
    if (!instance)
    {
        instance = new JSONManager();
    }
    return instance;
}

JSONManager::JSONManager()
{
    // Constructor
}

JSONManager::~JSONManager()
{
    // Destructor
}

JSONManager::PlayerData JSONManager::loadJSONData(const std::string& filename)
{
    FILE* file = fopen(filename.c_str(), "rb");
    if (!file)
    {
        CCLOG("Kh�ng th? m? t?p JSON.");
    }

    //char buffer[65536];
    //FileReadStream fileStream(file, buffer, sizeof(buffer));
    //Document document;
    //document.ParseStream(fileStream);

    //fclose(file);

    //// Ki?m tra xem t?p JSON c� h?p l? kh�ng
    //if (document.HasParseError())
    //{
    //    CCLOG("L?i khi ph�n t�ch t?p JSON.");
    //}
    //PlayerData playerData;

    //if (document.HasMember("player") && document["player"].IsObject())
    //{
    //    // Truy xu?t v� c?p nh?t thu?c t�nh c?a ??i t??ng UserData d?a tr�n d? li?u JSON
    //    if (document["player"].HasMember("health") && document["player"]["health"].IsInt())
    //    {
    //        playerData.health = document["player"]["health"].GetInt();
    //    }

    //    if (document["player"].HasMember("movementSpeed") && document["player"]["movementSpeed"].IsFloat())
    //    {
    //        playerData.movementSpeed = document["player"]["movementSpeed"].GetFloat();
    //    }

    //    if (document["player"].HasMember("attackSpeed") && document["player"]["attackSpeed"].IsFloat())
    //    {
    //        playerData.attackSpeed = document["player"]["attackSpeed"].GetFloat();
    //    }

    //    if (document["player"].HasMember("energy") && document["player"]["energy"].IsInt())
    //    {
    //        playerData.energy = document["player"]["energy"].GetInt();
    //    }

    //    if (document["player"].HasMember("maxHealth") && document["player"]["maxHealth"].IsInt())
    //    {
    //        playerData.maxHealth = document["player"]["maxHealth"].GetInt();
    //    }

    //    if (document["player"].HasMember("specialSkill") && document["player"]["specialSkill"].IsString())
    //    {
    //        playerData.specialSkill = document["player"]["specialSkill"].GetString();
    //    }

    //    if (document["player"].HasMember("weapon") && document["player"]["weapon"].IsString())
    //    {
    //        playerData.weapon = document["player"]["weapon"].GetString();
    //    }

    //    // C�c thu?c t�nh kh�c c� th? ???c c?p nh?t t??ng t?

    //    CCLOG("JSON data loaded successfully!");
    //}
    //else
    //{
    //    CCLOG("Failed to parse JSON data!");
    //}

    //// Tr? v? ??i t??ng playerData ?� ???c c?p nh?t
    return playerData;
}