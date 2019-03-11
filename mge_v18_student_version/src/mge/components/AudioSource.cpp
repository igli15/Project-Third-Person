//
// Created by Igli milaqi on 22/10/2018.
//

#include "AudioSource.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"

void AudioSource::PlayOneShotSound(const std::string& soundTag)
{
    AbstractGame::Instance()->GetResourceManager()->GetSound(soundTag)->setVolume(m_volume);
	AbstractGame::Instance()->GetResourceManager()->GetSound(soundTag)->play();
}

void AudioSource::PlayMusic()
{
    m_music->setVolume(m_volume);
    m_music->play();
}

void AudioSource::PauseMusic()
{
    m_music->pause();
}

void AudioSource::StopMusic()
{
    m_music->stop();
}

void AudioSource::SetMusic(sf::Music * music)
{
	m_music = music;
}


AudioSource::AudioSource()
{
    m_music = new sf::Music();
}

AudioSource::~AudioSource()
{
    m_music = nullptr;
}

void AudioSource::SetVolume(const float &volume)
{
	if(m_music != nullptr) m_music->setVolume(volume);
    m_volume = volume;
}

void AudioSource::SetMusicPitch(sf::Music * music, float pPitch)
{
	if (m_music != nullptr) m_music->setPitch(pPitch);
}

