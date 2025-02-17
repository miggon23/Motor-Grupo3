#include "AudioFactory.h"
#include "ECS/Manager.h"
#include <iostream>

namespace Flamingo
{
    AudioFactory::AudioFactory()
    {
    }

    Flamingo::Component* AudioFactory::createComponent(Flamingo::GameObject* gO, const std::unordered_map<std::string, std::string>& args)
    {
        try
        {
            std::string route = (args.at("t_routeSong"));
            std::string name = (args.at("t_songName"));
            std::string musicS = (args.at("t_music"));

            bool music;

            if (musicS == "true")
                music = true;
            else if (musicS == "false")
                music = false;
            else
                throw new std::exception("Invalids or incompletes params");

            AudioSource* c = Manager::instance()->addComponent<AudioSource>(gO);
            c->initValues(route.c_str(), name, music);
           
            Flamingo::Manager::instance()->addGameObjectToGroups(gO, {Flamingo::GROUP_AUDIO});
            return c;
        }
        catch (...)
        {
            throw std::exception("[ERROR Audio Factory]: Key broken or not found");
        }
    }
} // namespace Flamingo