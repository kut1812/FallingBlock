//#include "Character/Player.h"
//
//Player* Player::createPlayer() {
//    Player* player = new (std::nothrow) Player();
//    if (player && player->init()) {
//        player->autorelease();
//        return player;
//    }
//    else {
//        delete player;
//        player = nullptr;
//        return nullptr;
//    }
//}