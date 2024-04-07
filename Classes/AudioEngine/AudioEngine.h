#ifndef __AUDIO__
#define __AUDIO__

#include "cocos2d.h"
#include "audio/include/AudioEngine.h" 

USING_NS_CC;

class Audio {
public:
    static Audio* getInstance();
    int play2d(const std::string& filePath, bool loop = false, float volume = 0.01f, const AudioProfile* profile = nullptr);
    void setVolume(int audioId, float volume);
    void pause(int audioId);
    void resume(int audioId);
    void stop(int audioId);
    int getBackgroundMusicId() const { return backgroundMusicId; };
    void setPressJoystickSoundId(int newId) { pressJoystickSoundId = newId; };
    int getPressJoystickSoundId() const { return pressJoystickSoundId; };
    void setJumpSoundId(int newId) { jumpSoundId = newId; };
    int getJumpSoundId() const { return jumpSoundId; };
    void setCollectCoinSoundId(int newId) { collectCoinSoundId = newId; };
    int getCollectCoinSoundId() const { return collectCoinSoundId; };
    void setBlockFlopSoundId(int newId) { blockFlopSoundId = newId; };
    int getBlockFlopSoundId() const { return blockFlopSoundId; };
private:
    static Audio* instance;
    int backgroundMusicId = 0;
    int pressJoystickSoundId = 0;
    int jumpSoundId = 0;
    int collectCoinSoundId = 0;
    int blockFlopSoundId = -1;
    Audio();
    ~Audio();
};

#endif // __AUDIO__
