#ifndef __MILEAGE_COUNTER__
#define __MILEAGE_COUNTER__

#include "cocos2d.h"

USING_NS_CC;

class MileageCounter : public Label {
public:
    static MileageCounter* create(const std::string& fontFile, const std::string& text, float fontSize, const Color4B& color = Color4B::WHITE, TextHAlignment alignment = TextHAlignment::LEFT, TextVAlignment vertAlignment = TextVAlignment::TOP) {
        MileageCounter* label = new (std::nothrow) MileageCounter();
        if (label && label->initWithTTF(text, fontFile, fontSize, Size::ZERO, alignment, vertAlignment)) {
            label->setTextColor(color);
            label->autorelease();
            return label;
        }
        CC_SAFE_DELETE(label);
        return nullptr;
    }

    void setMileage(int mileage) {
        this->setString(StringUtils::format("%d", mileage));
    }

    int getMileage() const {
        return atoi(getString().c_str());
    }

protected:
    MileageCounter() {}
    virtual ~MileageCounter() {}
};


#endif // !__MILEAGE_COUNTER__