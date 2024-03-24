#ifndef __JSON_MANAGER_H__
#define __JSON_MANAGER_H__

#include "cocos2d.h"
#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"


USING_NS_CC;

class JSONManager {
public:
    struct PlayerData {
        
    };
    struct BlockData {

    };
    struct X2CoinSkillData {

    };
    struct X2JumpSkillData {

    };
    struct ShieldSkillData {

    };

    static JSONManager* getInstance();
    //PlayerData loadJSONData(const std::string& filename);

private:
    static JSONManager* instance;

    JSONManager();
    ~JSONManager();
};

#endif // __JSON_MANAGER_H__
