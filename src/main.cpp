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

                    // TODO: idk how to load the fish.webp directly from resources lmao
                    // something with the webp format i think, can anyone help pls :sob:
                    // yes ill add imageplus for it
                    // if (Mod::get()->getSettingValue<bool>("fishSpinner"))
                    // {
                    //     spinner->setVisible(false);
                    //     auto fishSpinner = CCSprite::create("fish.webp"_spr);
                    //     fishSpinner->setPosition({0, 0});
                    //     spinner->addChild(fishSpinner);
                    // }
                    break;
                }
            }
        }

        return layer;
    }
};
