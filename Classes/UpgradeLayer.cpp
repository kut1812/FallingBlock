#include "UpgradeLayer.h"
#include "LayerManager.h"
#include "AudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"
#include "StatsManager/StatsManager.h"
#include "WorkingWithData/SQLiteManager.h"

USING_NS_CC;

UpgradeLayer* UpgradeLayer::create(Player* _plr)
{
    UpgradeLayer* layer = new (std::nothrow) UpgradeLayer();
    if (layer && layer->init(_plr)) {
        layer->autorelease();
        return layer;
    }
    layer->_player = _plr;
    return nullptr;
}

bool UpgradeLayer::init(Player* _plr) {
    if (!Layer::init()) {
        return false;
    }

    SQLiteManager* dbManager = SQLiteManager::getInstance();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Node* upgradeLayer = CSLoader::getInstance()->createNode("csb/Upgrade.csb");
    Director::getInstance()->pause();
    auto sceneGame = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
    if (sceneGame!=nullptr)
    {
        //sceneGame->setDynamicAllBlock(200);
    }
    auto cancel = upgradeLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Button::TouchEventType::BEGAN:
            // Khi nút được nhấn, phóng to nút lên
            cancel->setScale(0.55f);
            break;
        case ui::Button::TouchEventType::ENDED: {
            auto sceneGame1 = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
            if (sceneGame1 != nullptr) {
                sceneGame1->setDynamicAllBlock(true);
            }
            Director::getInstance()->resume();
            upgradeLayer->removeFromParentAndCleanup(true);
            cancel->setScale(0.5);
            break;
        }
        default:
            break;
        }
        });

    SQLiteManager::PlayerInfo playerInfo = dbManager->getPlayerById(1);
    auto textLevelSkullSpeed = Label::createWithTTF("   " + std::to_string(_plr->getMovementLevel()) + " / 300", "font/Baloo2/Baloo2-Bold.ttf", 18);
    textLevelSkullSpeed->setPosition(Vec2(visibleSize.width * 0.31, visibleSize.height * 0.56));
    textLevelSkullSpeed->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(textLevelSkullSpeed);
    auto textLifeSpawn = Label::createWithTTF("    " + std::to_string(_plr->getLifeSpawnLevel()) + " / 300", "font/Baloo2/Baloo2-Bold.ttf", 18);
    textLifeSpawn->setPosition(Vec2(visibleSize.width * 0.53, visibleSize.height * 0.56));
    textLifeSpawn->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(textLifeSpawn);
    auto textBlockSpeed = Label::createWithTTF("   " + std::to_string(_plr->getBlockSpeedLevel()) + " / 300", "font/Baloo2/Baloo2-Bold.ttf", 18);
    textBlockSpeed->setPosition(Vec2(visibleSize.width * 0.31, visibleSize.height * 0.345));
    textBlockSpeed->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(textBlockSpeed);
    auto textSkillDuration = Label::createWithTTF("    " + std::to_string(_plr->getSkillDurationLevel()) + " / 300", "font/Baloo2/Baloo2-Bold.ttf", 18);
    textSkillDuration->setPosition(Vec2(visibleSize.width * 0.53, visibleSize.height * 0.345));
    textSkillDuration->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(textSkillDuration);
    auto textCoin = Label::createWithTTF(std::to_string(_plr->getMoney()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    textCoin->setPosition(Vec2(visibleSize.width * 0.51, visibleSize.height * 0.20));
    upgradeLayer->addChild(textCoin);

    //%
    // 
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << ((std::round(static_cast<float>(_plr->getMovementLevel() + 1) / 3 * 10.0) / 10.0));
    std::string formattedString = ss.str();
    auto statSkullSpeed = Label::createWithTTF("" + formattedString + "%", "font/Baloo2/Baloo2-Bold.ttf", 20);
    statSkullSpeed->setPosition(Vec2(visibleSize.width * 0.36, visibleSize.height * 0.515));
    statSkullSpeed->setColor(Color3B::GREEN);
    statSkullSpeed->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(statSkullSpeed);


    std::stringstream ss2;
    ss2 << std::fixed << std::setprecision(2) << (static_cast<float>((_plr->getBlockSpeedLevel())) / 6);
    std::string formattedString2 = ss2.str();
    auto statBlockSpeed = Label::createWithTTF("-" + formattedString2 + "%", "font/Baloo2/Baloo2-Bold.ttf", 20);
    statBlockSpeed->setPosition(Vec2(visibleSize.width * 0.36, visibleSize.height * 0.305));
    statBlockSpeed->setAnchorPoint(Vec2(0, 0.5));
    statBlockSpeed->setColor(Color3B::GREEN);
    upgradeLayer->addChild(statBlockSpeed);
    std::stringstream ss3;
    ss3 << std::fixed << std::setprecision(2) << (static_cast<float>((_plr->getSkillDurationLevel())) / 40);
    std::string formattedString3 = ss3.str();
    auto statSkillDuration = Label::createWithTTF("   -" + formattedString3 + "s", "font/Baloo2/Baloo2-Bold.ttf", 20);
    statSkillDuration->setPosition(Vec2(visibleSize.width * 0.57, visibleSize.height * 0.305));
    statSkillDuration->setColor(Color3B::GREEN);
    statSkillDuration->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(statSkillDuration);
    float level = static_cast<float>(_plr->getLifeSpawnLevel()) / 15;
    std::ostringstream ss4;
    float result = 30.0f - level;
    ss4 << std::fixed << std::setprecision(2) << result;
    std::string formattedString4 = ss4.str();
    auto statLifeSpawn = Label::createWithTTF("   " + formattedString4 + "s", "font/Baloo2/Baloo2-Bold.ttf", 20);
    statLifeSpawn->setPosition(Vec2(visibleSize.width * 0.57, visibleSize.height * 0.515));
    statLifeSpawn->setColor(Color3B::GREEN);
    statLifeSpawn->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(statLifeSpawn);

    auto a = _plr->getMovementLevel();
    auto b = "MAX";
    std::string price;
    if (a==300)
    {
        price = b;
    }
    else {
        price = std::to_string(_plr->getMovementLevel() * 5)+ "$";
    }
    auto statSkullPrice = Label::createWithTTF("  " + price , "font/Baloo2/Baloo2-Bold.ttf", 18);
    statSkullPrice->setPosition(Vec2(visibleSize.width * 0.485, visibleSize.height * 0.515));
    statSkullPrice->setColor(Color3B::ORANGE);
    statSkullPrice->setAnchorPoint(Vec2(1, 0.5));
    upgradeLayer->addChild(statSkullPrice);

    a = _plr->getBlockSpeedLevel();
    if (a==300)
    {
        price = b;
    }
    else {
        price = std::to_string(_plr->getBlockSpeedLevel() * 5)+ "$";
    }
    auto statBlockPrice = Label::createWithTTF("  " + price , "font/Baloo2/Baloo2-Bold.ttf", 18);
    statBlockPrice->setPosition(Vec2(visibleSize.width * 0.485, visibleSize.height * 0.305));
    statBlockPrice->setAnchorPoint(Vec2(1, 0.5));
    statBlockPrice->setColor(Color3B::ORANGE);
    upgradeLayer->addChild(statBlockPrice);
    a = _plr->getSkillDurationLevel();
    if (a==300)
    {
        price = b;
    }
    else {
        price = std::to_string(_plr->getSkillDurationLevel() * 5)+ "$";
    }
    auto statSkillPrice = Label::createWithTTF("  " +price , "font/Baloo2/Baloo2-Bold.ttf", 18);
    statSkillPrice->setPosition(Vec2(visibleSize.width * 0.71, visibleSize.height * 0.305));
    statSkillPrice->setColor(Color3B::ORANGE);
    statSkillPrice->setAnchorPoint(Vec2(1, 0.5));
    upgradeLayer->addChild(statSkillPrice);
    a = _plr->getLifeSpawnLevel();
    if (a==300)
    {
        price = b;
    }
    else {
        price = std::to_string(_plr->getLifeSpawnLevel() * 5)+ "$";
    }
    auto statLifePrice = Label::createWithTTF("  " +price , "font/Baloo2/Baloo2-Bold.ttf", 18);
    statLifePrice->setPosition(Vec2(visibleSize.width * 0.71, visibleSize.height * 0.515));
    statLifePrice->setColor(Color3B::ORANGE);
    statLifePrice->setAnchorPoint(Vec2(1, 0.5));
    upgradeLayer->addChild(statLifePrice);
    //SkullSpeed
    int levelSkullSpeed = _plr->movementLevel; 

    Vector<Sprite*> loadingSkullSpeed;
    for (int i = 0; i < 10; ++i) {
        auto section = Sprite::create("popup/fb_popup_upgrade_cell_b.png"); // Hình ảnh mặc định là màu đen
        section->setPosition(Vec2(visibleSize.width * 0.33 + (i * visibleSize.width * 0.013), visibleSize.height * 0.62)); // Đặt vị trí cho từng khúc
        section->setScale(0.5);
        upgradeLayer->addChild(section);
        loadingSkullSpeed.pushBack(section);
    }
    if (levelSkullSpeed % 10 !=0)
    {
        levelSkullSpeed = levelSkullSpeed % 10;
    }
    else
    {
        if (levelSkullSpeed>0)
        {
            levelSkullSpeed = 10;
        }
        else
        {
            levelSkullSpeed = 0;
        }
    }
    for (int i = 0; i < levelSkullSpeed ; ++i) {
        loadingSkullSpeed.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
    }

    //LifeSpawn
    int levelLifeSpawn = _plr->getLifeSpawnLevel();

    Vector<Sprite*> loadingLifeSpawn;
    for (int i = 0; i < 10; ++i) {
        auto section = Sprite::create("popup/fb_popup_upgrade_cell_b.png"); // Hình ảnh mặc định là màu đen
        section->setPosition(Vec2(visibleSize.width * 0.55 + (i * visibleSize.width * 0.013), visibleSize.height * 0.62)); // Đặt vị trí cho từng khúc
        section->setScale(0.5);
        upgradeLayer->addChild(section);
        loadingLifeSpawn.pushBack(section);
    }
    if (levelLifeSpawn % 10 != 0)
    {
        levelLifeSpawn = levelLifeSpawn % 10;
    }
    else
    {
        if (levelLifeSpawn > 0)
        {
            levelLifeSpawn = 10;
        }
        else
        {
            levelLifeSpawn = 0;
        }
    }
    for (int i = 0; i < levelLifeSpawn; ++i) {
        loadingLifeSpawn.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
    }


    //BlockSpeed
    int levelBlockSpeed = _plr->getBlockSpeedLevel();

    Vector<Sprite*> loadingBlockSpeed;
    for (int i = 0; i < 10; ++i) {
        auto section = Sprite::create("popup/fb_popup_upgrade_cell_b.png"); // Hình ảnh mặc định là màu đen
        section->setPosition(Vec2(visibleSize.width * 0.33 + (i * visibleSize.width * 0.013), visibleSize.height * 0.40)); // Đặt vị trí cho từng khúc
        section->setScale(0.5);
        upgradeLayer->addChild(section);
        loadingBlockSpeed.pushBack(section);
    }
    if (levelBlockSpeed % 10 != 0)
    {
        levelBlockSpeed = levelBlockSpeed % 10;
    }
    else
    {
        if (levelBlockSpeed > 0)
        {
            levelBlockSpeed = 10;
        }
        else
        {
            levelBlockSpeed = 0;
        }
    }
    for (int i = 0; i < levelBlockSpeed; ++i) {
        loadingBlockSpeed.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
    }


    //SkillDuration
    int levelSkillDuration = _plr->getSkillDurationLevel();

    Vector<Sprite*> loadingSkillDuration;
    for (int i = 0; i < 10; ++i) {
        auto section = Sprite::create("popup/fb_popup_upgrade_cell_b.png"); // Hình ảnh mặc định là màu đen
        section->setPosition(Vec2(visibleSize.width * 0.55 + (i * visibleSize.width * 0.013), visibleSize.height * 0.40)); // Đặt vị trí cho từng khúc
        section->setScale(0.5);
        upgradeLayer->addChild(section);
        loadingSkillDuration.pushBack(section);
    }
    if (levelSkillDuration % 10 != 0)
    {
        levelSkillDuration = levelSkillDuration % 10;
    }
    else
    {
        if (levelSkillDuration > 0)
        {
            levelSkillDuration = 10;
        }
        else
        {
            levelSkillDuration = 0;
        }
    }
    for (int i = 0; i < levelSkillDuration; ++i) {
        loadingSkillDuration.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
    }
    this->addChild(upgradeLayer);


    //button + skull speed
    auto buttonAddSS = upgradeLayer->getChildByName<ui::Button*>("Button_3_0");
    buttonAddSS->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (StatsManager::getInstance(_plr)->upgrade("skull speed")) {
                CCLOG("Successfully!");
                int levelSkullSpeed = _plr->getMovementLevel();
                for (int i = 0; i < 10; ++i) {
                    loadingSkullSpeed.at(i)->setTexture("popup/fb_popup_upgrade_cell_b.png");
                }
                if (levelSkullSpeed % 10 != 0)
                {
                    levelSkullSpeed = levelSkullSpeed % 10;
                }
                else
                {
                    if (levelSkullSpeed > 0)
                    {
                        levelSkullSpeed = 10;
                    }
                    else
                    {
                        levelSkullSpeed = 0;
                    }
                }
                for (int i = 0; i < levelSkullSpeed; ++i) {
                    loadingSkullSpeed.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
                }
                textLevelSkullSpeed->setString("   " + std::to_string(_plr->getMovementLevel()) + " / 300");
                textCoin->setString(std::to_string(_plr->getMoney()));
                std::stringstream ss;
                ss << std::fixed << std::setprecision(2) << ((std::round(static_cast<float>(_plr->getMovementLevel() + 1) / 3 * 10.0) / 10.0));
                std::string formattedString = ss.str();
                statSkullSpeed->setString("" + formattedString + "%");
                auto a = _plr->getMovementLevel();
                std::string b = "MAX";
                std::string price;
                if (a == 300)
                {
                    price = b ;
                }
                else {
                    price = std::to_string(_plr->getMovementLevel() * 5)+"$";
                }
                statSkullPrice->setString("  " + price );
                if (_plr->getMoney() < _plr->getMovementLevel() * 5 || _plr->getMovementLevel() == 300)
                {
                    buttonAddSS->setEnabled(false);
                }
            }
            else {
                CCLOG("Not enough money!");
            }
        }
        });
        if (_plr->getMoney()< _plr->getMovementLevel() * 5 || _plr->getMovementLevel()==300)
        {
            buttonAddSS->setEnabled(false);
        } 

    //button + life spawn

    auto buttonAddLS = upgradeLayer->getChildByName<ui::Button*>("Button_3_0_0");
    buttonAddLS->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (StatsManager::getInstance(_plr)->upgrade("life spawn")) {

                CCLOG("Successfully!");
                int levelLifeSpawn = _plr->getLifeSpawnLevel();
                for (int i = 0; i < 10; ++i) {
                    loadingLifeSpawn.at(i)->setTexture("popup/fb_popup_upgrade_cell_b.png");
                }
                if (levelLifeSpawn % 10 != 0)
                {
                    levelLifeSpawn = levelLifeSpawn % 10;
                }
                else
                {
                    if (levelLifeSpawn > 0)
                    {
                        levelLifeSpawn = 10;
                    }
                    else
                    {
                        levelLifeSpawn = 0;
                    }
                }
                for (int i = 0; i < levelLifeSpawn; ++i) {
                    loadingLifeSpawn.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
                }
                textLifeSpawn->setString("    " + std::to_string(_plr->getLifeSpawnLevel()) + " / 300");
                textCoin->setString(std::to_string(_plr->getMoney()));
                float level = static_cast<float>(_plr->getLifeSpawnLevel()) / 3;
                float result = 330.0f - level;
                std::ostringstream ss4;
                ss4 << std::fixed << std::setprecision(2) << result;
                std::string formattedString4 = ss4.str();
                statLifeSpawn->setString("   " + formattedString4 + "s");
                auto a = _plr->getLifeSpawnLevel();
                std::string b = "MAX";
                std::string price;
                if (a == 300)
                {
                    price = b;
                }
                else {
                    price = std::to_string(_plr->getLifeSpawnLevel() * 5) + "$";
                }
                statLifePrice->setString("  " +price);
                if (_plr->getMoney() < _plr->getLifeSpawnLevel() * 5 || _plr->getLifeSpawnLevel() == 300)
                {
                    buttonAddLS->setEnabled(false);
                }
            }
            else {
                CCLOG("Not enough money!");
            }
        }
        });
    if (_plr->getMoney() < _plr->getLifeSpawnLevel() * 5 || _plr->getLifeSpawnLevel() == 300)
    {
        buttonAddLS->setEnabled(false);
    }
    //button + block speed

    auto buttonAddBS = upgradeLayer->getChildByName<ui::Button*>("Button_3_0_0_0");
    buttonAddBS->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (StatsManager::getInstance(_plr)->upgrade("block speed")) {

                CCLOG("Successfully!");
                int levelBlockSpeed = _plr->getBlockSpeedLevel();
                for (int i = 0; i < 10; ++i) {
                    loadingBlockSpeed.at(i)->setTexture("popup/fb_popup_upgrade_cell_b.png");
                }
                if (levelBlockSpeed % 10 != 0)
                {
                    levelBlockSpeed = levelBlockSpeed % 10;
                }
                else
                {
                    if (levelBlockSpeed > 0)
                    {
                        levelBlockSpeed = 10;
                    }
                    else
                    {
                        levelBlockSpeed = 0;
                    }
                }
                for (int i = 0; i < levelBlockSpeed; ++i) {
                    loadingBlockSpeed.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
                }
                textBlockSpeed->setString("   " + std::to_string(_plr->getBlockSpeedLevel()) + " / 300");
                textCoin->setString(std::to_string(_plr->getMoney()));
                std::stringstream ss2;
                ss2 << std::fixed << std::setprecision(2) << (static_cast<float>((_plr->getBlockSpeedLevel())) / 6);
                std::string formattedString2 = ss2.str();
                statBlockSpeed->setString("-" + formattedString2 + "%");
                auto a = _plr->getBlockSpeedLevel();
                std::string b = "MAX";
                std::string price;
                if (a == 300)
                {
                    price = b;
                }
                else {
                    price = std::to_string(_plr->getBlockSpeedLevel() * 5) + "$";
                }
                statBlockPrice->setString("  " + price);
                if (_plr->getMoney() < _plr->getBlockSpeedLevel() * 5 || _plr->getBlockSpeedLevel() == 300)
                {
                    buttonAddBS->setEnabled(false);
                }
            }
            else {
                CCLOG("Not enough money!");
            }
        }
        });
    if (_plr->getMoney() < _plr->getBlockSpeedLevel() * 5 || _plr->getBlockSpeedLevel() == 300)
    {
        buttonAddBS->setEnabled(false);
    }
    //button + skill duration

    auto buttonAddSD = upgradeLayer->getChildByName<ui::Button*>("Button_3_0_0_0_0");
    buttonAddSD->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (StatsManager::getInstance(_plr)->upgrade("skill duration")) {

                CCLOG("Successfully!");
                int levelSkillDuration = _plr->getSkillDurationLevel();
                for (int i = 0; i < 10; ++i) {
                    loadingSkillDuration.at(i)->setTexture("popup/fb_popup_upgrade_cell_b.png");
                }
                if (levelSkillDuration % 10 != 0)
                {
                    levelSkillDuration = levelSkillDuration % 10;
                }
                else
                {
                    if (levelSkillDuration > 0)
                    {
                        levelSkillDuration = 10;
                    }
                    else
                    {
                        levelSkillDuration = 0;
                    }
                }
                for (int i = 0; i < levelSkillDuration; ++i) {
                    loadingSkillDuration.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
                }
                textSkillDuration->setString("    " + std::to_string(_plr->getSkillDurationLevel()) + " / 300");
                textCoin->setString(std::to_string(_plr->getMoney()));
                std::stringstream ss3;
                ss3 << std::fixed << std::setprecision(2) << (static_cast<float>((_plr->getSkillDurationLevel())) / 40);
                std::string formattedString3 = ss3.str();
                statSkillDuration->setString("   -" + formattedString3 + "s");
                auto a = _plr->getSkillDurationLevel();
                std::string b = "MAX";
                std::string price;
                if (a == 300)
                {
                    price = b;
                }
                else {
                    price = std::to_string(_plr->getSkillDurationLevel() * 5) + "$";
                }
                statSkillPrice->setString("  " +price);
                if (_plr->getMoney() < _plr->getSkillDurationLevel() * 5 || _plr->getSkillDurationLevel() == 300)
                {
                    buttonAddSD->setEnabled(false);
                }
            }
            else {
                CCLOG("Not enough money!");
            }
        }
        });
    if (_plr->getMoney() < _plr->getSkillDurationLevel() * 5 || _plr->getSkillDurationLevel() == 300)
    {
        buttonAddSD->setEnabled(false);
    }
    return true;
}
