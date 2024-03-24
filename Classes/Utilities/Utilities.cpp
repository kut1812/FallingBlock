#include "Utilities.h"
#include <cstdlib>
#include <ctime>  
#include "AudioEngine.h"


Utilities* Utilities::_instance;

void Utilities::initRandomSeed() {
    srand(time(NULL));
}

Utilities* Utilities::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Utilities();
    }
    return _instance;
}

int Utilities::generateNumber(int min, int max) {
    int randomNumber = rand() % (max - min + 1) + min;
    return randomNumber;
}

void Utilities::playMusic(std::string fileName)
{
    AudioEngine::stop(_bgmID);
    _bgmID = AudioEngine::play2d("Audio/Music/" + fileName, true, _musicVolume);
}

void Utilities::playSFX(std::string fileName)
{
    AudioEngine::play2d("Audio/SFX/" + fileName, false, _sfxVolume);
}

void Utilities::setMusicVolume(float newVolume)
{
    _musicVolume = newVolume;

    AudioEngine::setVolume(_bgmID, _musicVolume);
}

void Utilities::setSFXVolume(float newVolume)
{
    _sfxVolume = newVolume;
}


Animation* Utilities::createAnimation(std::string name, int numFrame, float duration)
{
    Vector<SpriteFrame*> frames;
    for (int i = 0; i <= numFrame; i++)
    {
        char buffer[100];
        sprintf(buffer, "%s (%d)", name.c_str(), i + 1);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
        if (frame == nullptr)
        {
            break;
        }
        frames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, duration);
    AnimationCache::getInstance()->addAnimation(animation, name);
    return animation;
}
Animation* Utilities::createAnimationPng(std::string name, int numFrame, float duration)
{
    Vector<SpriteFrame*> frames;
    for (int i = 0; i <= numFrame; i++)
    {
        char buffer[100];
        sprintf(buffer, "%s (%d).png", name.c_str(), i + 1);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
        if (frame == nullptr)
        {
            break;
        }
        frames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, duration);
    AnimationCache::getInstance()->addAnimation(animation, name);
    return animation;
}
//
std::pair<Animation*, int> Utilities::createAnimation(std::string name, float duration)
{
    Vector<SpriteFrame*> frames;

    int numFrame = 0;
    while (true)
    {
        char buffer[100];
        sprintf(buffer, "%s (%d)", name.c_str(), numFrame + 1);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
        if (frame == nullptr)
        {
            break;
        }
        frames.pushBack(frame);
        ++numFrame;
    }

    Animation* animation = Animation::createWithSpriteFrames(frames, duration / (float)numFrame);
    AnimationCache::getInstance()->addAnimation(animation, name);
    return std::pair<Animation*, int>(animation, numFrame);
}

bool Utilities::loadSpriteFrameCache(std::string path, std::string fileName)
{
    if (!FileUtils::getInstance()->isFileExist(path + fileName + ".plist") ||
        !FileUtils::getInstance()->isFileExist(path + fileName + ".png"))
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path + fileName + ".plist", path + fileName + ".png");
    return true;
}