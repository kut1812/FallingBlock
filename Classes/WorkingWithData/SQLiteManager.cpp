#include "SQLiteManager.h"

USING_NS_CC;

SQLiteManager* SQLiteManager::s_instance = nullptr;

SQLiteManager* SQLiteManager::getInstance() {
    if (!s_instance) {
        s_instance = new SQLiteManager();
        s_instance->init();
    }
    return s_instance;
}

void SQLiteManager::destroyInstance() {
    CC_SAFE_DELETE(s_instance);
}

bool SQLiteManager::init() {
    bool ret = false;
    do {
        // Open database
        std::string dbPath = FileUtils::getInstance()->getWritablePath() + "falling-block.db";
        int result = sqlite3_open(dbPath.c_str(), &_database);
        if (result != SQLITE_OK) {
            CCLOG("Failed to open database: %s", sqlite3_errmsg(_database));
            break;
        }
        CCLOG("Database opened successfully");

        const char* createTableQuery = "CREATE TABLE IF NOT EXISTS player (id INTEGER PRIMARY KEY AUTOINCREMENT, money INTEGER, movement_speed REAL, life_spawn INTEGER, block_speed REAL, skill_duration REAL)";
        executeQuery(createTableQuery);
        const char* createTable2Query = "CREATE TABLE IF NOT EXISTS topscores  (id INTEGER PRIMARY KEY AUTOINCREMENT, playerid INTEGER, score INTEGER)";
        executeQuery(createTable2Query);
        ret = true;
    } while (0);
    std::string dbPath = FileUtils::getInstance()->getWritablePath() + "falling-block.db";
    CCLOG("Database path: %s", dbPath.c_str());

    return ret;
}

void SQLiteManager::closeDatabase() {
    if (_database) {
        sqlite3_close(_database);
        _database = nullptr;
    }
}

void SQLiteManager::executeQuery(const std::string& query) {
    char* errorMessage;
    int result = sqlite3_exec(_database, query.c_str(), nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        CCLOG("Failed to execute query: %s", errorMessage);
        sqlite3_free(errorMessage);
    }
    else {
        CCLOG("Query executed successfully");
    }
}

void SQLiteManager::setPlayerInfo(const int playerId, float movement_speed, int life_spawn, float block_speed, float skill_duration) {
    std::string checkQuery = "SELECT * FROM player WHERE id = " + std::to_string(playerId);
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(_database, checkQuery.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        CCLOG("Failed to execute query: %s", sqlite3_errmsg(_database));
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string updateQuery = "UPDATE player SET movement_speed = " + std::to_string(movement_speed) + ", "
            "life_spawn = " + std::to_string(life_spawn) + ", "
            "block_speed = " + std::to_string(block_speed) + ", "
            "skill_duration = " + std::to_string(skill_duration) +
            " WHERE id = " + std::to_string(playerId);
        executeQuery(updateQuery);
    }
    else {
        std::string insertQuery = "INSERT INTO player (id, movement_speed, life_spawn, block_speed, skill_duration) "
            "VALUES (" + std::to_string(playerId) + ", " + std::to_string(movement_speed) + ", " +
            std::to_string(life_spawn) + ", " + std::to_string(block_speed) + ", " +
            std::to_string(skill_duration) + ")";
        executeQuery(insertQuery);
    }

    sqlite3_finalize(stmt);
}

void SQLiteManager::addScore(int playerId, int score) {
    std::string insertQuery = "INSERT INTO topscores (playerid, score) VALUES (" + std::to_string(playerId) + ", " + std::to_string(score) + ")";
    executeQuery(insertQuery);
}

std::vector<SQLiteManager::ScoreInfo> SQLiteManager::getTop10Highscore() {
    std::vector<ScoreInfo> topScores;

    std::string query = "SELECT id, playerid, score FROM topscores ORDER BY score DESC LIMIT 10";
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        CCLOG("Failed to execute query: %s", sqlite3_errmsg(_database));
        return topScores;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        ScoreInfo topScore;
        topScore.id = sqlite3_column_int(stmt, 0);
        topScore.playerId = sqlite3_column_int(stmt, 1);
        topScore.score = sqlite3_column_int(stmt, 2);
        topScores.push_back(topScore);
    }

    sqlite3_finalize(stmt);
    return topScores;

}

SQLiteManager::PlayerInfo SQLiteManager::getPlayerById(int playerId) {
    PlayerInfo player;
    player.id = -1; 
    player.money = 0; 
    player.movement_speed = 0.0f; 
    player.life_spawn = 0; 
    player.block_speed = 0.0f; 
    player.skill_duration = 0.0f; 

    std::string query = "SELECT money, movement_speed, life_spawn, block_speed, skill_duration "
        "FROM player WHERE id = " + std::to_string(playerId);
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        CCLOG("Failed to execute query: %s", sqlite3_errmsg(_database));
        return player; 
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        player.id = playerId;
        player.money = sqlite3_column_int(stmt, 0);
        player.movement_speed = sqlite3_column_double(stmt, 1);
        player.life_spawn = sqlite3_column_int(stmt, 2);
        player.block_speed = sqlite3_column_double(stmt, 3);
        player.skill_duration = sqlite3_column_double(stmt, 4);
    }

    sqlite3_finalize(stmt);
    return player;
}
