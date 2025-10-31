#include <Geode/Geode.hpp>
#include <Geode/modify/GJGameLoadingLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;

class $modify(GJGameLoadingLayer)
{
    static GJGameLoadingLayer *transitionToLoadingLayer(GJGameLevel *level, bool editor)
    {
        auto layer = GJGameLoadingLayer::transitionToLoadingLayer(level, editor);
        auto loadingString = Mod::get()->getSettingValue<std::string>("loadingString");

        if (layer)
        {
            log::debug("editor: {}", editor);
            for (int i = 0; i < layer->getChildrenCount(); i++)
            {
                // i mean i could just getChildByID(0) and do it that way but im smorty
                if (auto label = static_cast<CCLabelBMFont *>(layer->getChildren()->objectAtIndex(i)))
                {
                    auto winSize = CCDirector::sharedDirector()->getWinSize();
                    label->setPosition(label->getPositionX() - 40, label->getPositionY());
                    label->setString(loadingString.c_str());
                    auto spinner = LoadingSpinner::create(30.f);
                    spinner->setPosition(winSize.width - 30, 30);
                    layer->addChild(spinner);

                    if (Mod::get()->getSettingValue<bool>("fishSpinner"))
                    {
                        spinner->setVisible(false);
                        auto fishSpinner = CCSprite::create("fish.webp"_spr);
                        fishSpinner->setScale(1.2f);
                        fishSpinner->setPosition({winSize.width - 30, 30});
                        layer->addChild(fishSpinner, 100);
                    }
                    break;
                }
            }
        }

        return layer;
    }
};
