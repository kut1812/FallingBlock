#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "cocos2d.h"

USING_NS_CC;

class Utilities
{
public:
	static Utilities* getInstance();
	int generateNumber(int min, int max);
	void initRandomSeed();
	void playMusic(std::string fileName);
	void playSFX(std::string fileName);
	void setMusicVolume(float newVolume);
	void setSFXVolume(float newVolume);
	float getMusicVolume() { return _musicVolume; }
	float getSFXVolume() { return _sfxVolume; }
	static Animation* createAnimationPng(std::string name, int numFrame, float duration);
	static Animation* createAnimation(std::string name, int numFrame, float duration);
	static std::pair<Animation*, int> createAnimation(std::string name, float duration);
	static bool loadSpriteFrameCache(std::string path, std::string fileName);
private:
	static Utilities* _instance;

	float _musicVolume = 0.5f, _sfxVolume = 0.5f;

	int _bgmID;
};

#endif // !__UTILITIES_H__