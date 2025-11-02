#include <Geode/Geode.hpp>
#include <Geode/modify/GJGameLoadingLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;

// to the index staff: finally you decided to review this tiny mod that you could approve in like 10 seconds like what ages, jeez
class $modify(GJGameLoadingLayer)
{
    static GJGameLoadingLayer *transitionToLoadingLayer(GJGameLevel *level, bool editor)
    {
        auto layer = GJGameLoadingLayer::transitionToLoadingLayer(level, editor);
        auto loadingString = Mod::get()->getSettingValue<std::string>("loadingString");

        if (layer)
        {
            log::debug("loading editor: {}", editor);
            float textScale = Mod::get()->getSettingValue<float>("loadingScale");
            // i mean i could just getChildByID(0) and do it that way but im smorty
            if (auto label = layer->getChildByType<CCLabelBMFont>(0))
            {
                auto winSize = CCDirector::sharedDirector()->getWinSize();
                label->setPosition(label->getPositionX() - 40, label->getPositionY());
                label->setString(loadingString.c_str());
                label->setScale(textScale);
                auto spinner = LoadingSpinner::create(30.f);
                spinner->setPosition(winSize.width - 30, 30);
                layer->addChild(spinner);

                if (Mod::get()->getSettingValue<bool>("fishSpinner"))
                {
                    spinner->setVisible(false);
                    auto fishSpinner = CCSprite::create("fish.webp"_spr);
                    fishSpinner->setScale(1.4f);
                    fishSpinner->setPosition({winSize.width - 30, 30});
                    layer->addChild(fishSpinner, 100);
                }

                // time to do the options thingy
                if (Mod::get()->getSettingValue<bool>("customEditorLoading"))
                {
                    if (editor)
                    {
                        auto enterString = Mod::get()->getSettingValue<std::string>("enterEditorString");
                        label->setString(enterString.c_str());
                    }
                    else if (!editor)
                    {
                        auto exitingString = Mod::get()->getSettingValue<std::string>("exitingEditorString");
                        label->setString(exitingString.c_str());
                    }
                }
            }
        }

        return layer;
    }
};
