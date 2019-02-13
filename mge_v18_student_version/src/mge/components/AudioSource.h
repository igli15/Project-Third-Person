//
// Created by Igli milaqi on 22/10/2018.
//

#ifndef SMFLPROJECT_AUDIOSOURCE_H
#define SMFLPROJECT_AUDIOSOURCE_H

#include "mge/core/Component.h"
#include <SFML/Audio.hpp>
#include <map>

    class AudioSource : public Component {

    private:
        sf::Music *m_music;
        float m_volume = 100;                           //default full volume

    public:
        AudioSource();
        ~AudioSource() override;
        void PlayOneShotSound(const std::string& soundTag);

        void SetVolume(const float& volume);

        void PlayMusic();

        void PauseMusic();

        void StopMusic();

		void SetMusic(sf::Music* music);
    };


#endif //SMFLPROJECT_AUDIOSOURCE_H
