
#include "../../hdr/global.h"
#include <chrono>

typedef struct s_SoundQ
{
	Mix_Chunk *sound;
	int volume;
	int loops;
}				t_SoundQ;

typedef struct s_Channel
{
	double time;	//ms
	bool occupied;
}				t_Channel;

typedef struct s_Volume
{
	int index;
	int volume;
}				t_Volume;

auto startTime = std::chrono::high_resolution_clock::now();
std::vector<t_SoundQ> soundQ = {};
std::vector<t_Channel> channel = {};
std::vector<t_Volume> volumes = {};

void AudioCreateChannels(int amount)
{
	Mix_AllocateChannels(amount);
	for (int i = 0; i < amount; i++)
		channel.push_back({0, false});
}

void AudioCreateVolume(int Chan, int volume)
{
	volumes.push_back({Chan, volume});
}

void AudioSetSound(Mix_Chunk *sound, int channel, int loops)
{
	int volume = 50;
	for (int i = 0; i < volumes.size(); i++)
	{
		if (volumes[i].index == channel)
		{
			volume = volumes[i].volume;
			break ;
		}
	}
	soundQ.push_back({sound, volume, loops});
}

static double DeltaTime()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> deltaTime = currentTime - startTime;
	startTime = currentTime;
	return (deltaTime.count());
}

static double GetDuration(Mix_Chunk *sound)
{
	Uint32 totalSamples = sound->alen / (2 * 2);
	double duration = (double)totalSamples / 44100.0;
	return (duration + 0.25);
}

static int FindChannel()
{
	for (int i = 0; i < channel.size(); i++)
	{
		if (channel[i].occupied == false)
			return (i);
	}
	return (-1);
}

static void PollAudio()
{
	for (int i = 0; i < soundQ.size(); i++)
	{
		Mix_Chunk *sound = soundQ[i].sound;
		int volume = soundQ[i].volume;
		int loops = soundQ[i].loops;
		int usedC = FindChannel();
		if (usedC == (-1))
			return ;
		Mix_Volume(usedC, volume);
		Mix_PlayChannel(usedC, sound, loops);
		channel[usedC].occupied = true;
		channel[usedC].time = GetDuration(sound);
		soundQ.erase(soundQ.begin() + i);
		i -= 1;
	}
}

static void UpdateChannels()
{
	double deltaTime = DeltaTime();
	for (int i = 0; i < channel.size(); i++)
	{
		if (channel[i].occupied)
		{
			channel[i].time -= deltaTime;
			if (channel[i].time <= 0.0)
				channel[i].occupied = false;
		}
	}
}

void AudioUpdate()
{
	UpdateChannels();
	PollAudio();
}

void AudioClear()
{
	soundQ.clear();
	for (int i = 0; i < channel.size(); i++)
	{
		channel[i].occupied = false;
		Mix_HaltChannel(i);
	}
}
