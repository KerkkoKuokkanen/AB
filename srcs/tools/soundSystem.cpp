
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

void CreateVolumeChannels()
{
	AudioCreateVolume(Channels::VOLUME_1, 1);
	AudioCreateVolume(Channels::VOLUME_2, 2);
	AudioCreateVolume(Channels::VOLUME_3, 3);
	AudioCreateVolume(Channels::VOLUME_4, 4);
	AudioCreateVolume(Channels::VOLUME_5, 5);
	AudioCreateVolume(Channels::VOLUME_6, 6);
	AudioCreateVolume(Channels::VOLUME_7, 7);
	AudioCreateVolume(Channels::VOLUME_8, 8);
	AudioCreateVolume(Channels::VOLUME_9, 9);
	AudioCreateVolume(Channels::VOLUME_10, 10);
	AudioCreateVolume(Channels::VOLUME_11, 11);
	AudioCreateVolume(Channels::VOLUME_12, 12);
	AudioCreateVolume(Channels::VOLUME_13, 13);
	AudioCreateVolume(Channels::VOLUME_14, 14);
	AudioCreateVolume(Channels::VOLUME_15, 15);
	AudioCreateVolume(Channels::VOLUME_16, 16);
	AudioCreateVolume(Channels::VOLUME_17, 17);
	AudioCreateVolume(Channels::VOLUME_18, 18);
	AudioCreateVolume(Channels::VOLUME_19, 19);
	AudioCreateVolume(Channels::VOLUME_20, 20);
	AudioCreateVolume(Channels::VOLUME_21, 21);
	AudioCreateVolume(Channels::VOLUME_22, 22);
	AudioCreateVolume(Channels::VOLUME_23, 23);
	AudioCreateVolume(Channels::VOLUME_24, 24);
	AudioCreateVolume(Channels::VOLUME_25, 25);
	AudioCreateVolume(Channels::VOLUME_26, 26);
	AudioCreateVolume(Channels::VOLUME_27, 27);
	AudioCreateVolume(Channels::VOLUME_28, 28);
	AudioCreateVolume(Channels::VOLUME_29, 29);
	AudioCreateVolume(Channels::VOLUME_30, 30);
	AudioCreateVolume(Channels::VOLUME_31, 31);
	AudioCreateVolume(Channels::VOLUME_32, 32);
	AudioCreateVolume(Channels::VOLUME_33, 33);
	AudioCreateVolume(Channels::VOLUME_34, 34);
	AudioCreateVolume(Channels::VOLUME_35, 35);
	AudioCreateVolume(Channels::VOLUME_36, 36);
	AudioCreateVolume(Channels::VOLUME_37, 37);
	AudioCreateVolume(Channels::VOLUME_38, 38);
	AudioCreateVolume(Channels::VOLUME_39, 39);
	AudioCreateVolume(Channels::VOLUME_40, 40);
	AudioCreateVolume(Channels::VOLUME_41, 41);
	AudioCreateVolume(Channels::VOLUME_42, 42);
	AudioCreateVolume(Channels::VOLUME_43, 43);
	AudioCreateVolume(Channels::VOLUME_44, 44);
	AudioCreateVolume(Channels::VOLUME_45, 45);
	AudioCreateVolume(Channels::VOLUME_46, 46);
	AudioCreateVolume(Channels::VOLUME_47, 47);
	AudioCreateVolume(Channels::VOLUME_48, 48);
	AudioCreateVolume(Channels::VOLUME_49, 49);
	AudioCreateVolume(Channels::VOLUME_50, 50);
	AudioCreateVolume(Channels::VOLUME_51, 51);
	AudioCreateVolume(Channels::VOLUME_52, 52);
	AudioCreateVolume(Channels::VOLUME_53, 53);
	AudioCreateVolume(Channels::VOLUME_54, 54);
	AudioCreateVolume(Channels::VOLUME_55, 55);
	AudioCreateVolume(Channels::VOLUME_56, 56);
	AudioCreateVolume(Channels::VOLUME_57, 57);
	AudioCreateVolume(Channels::VOLUME_58, 58);
	AudioCreateVolume(Channels::VOLUME_59, 59);
	AudioCreateVolume(Channels::VOLUME_60, 60);
	AudioCreateVolume(Channels::VOLUME_61, 61);
	AudioCreateVolume(Channels::VOLUME_62, 62);
	AudioCreateVolume(Channels::VOLUME_63, 63);
	AudioCreateVolume(Channels::VOLUME_64, 64);
	AudioCreateVolume(Channels::VOLUME_65, 65);
	AudioCreateVolume(Channels::VOLUME_66, 66);
	AudioCreateVolume(Channels::VOLUME_67, 67);
	AudioCreateVolume(Channels::VOLUME_68, 68);
	AudioCreateVolume(Channels::VOLUME_69, 69);
	AudioCreateVolume(Channels::VOLUME_70, 70);
	AudioCreateVolume(Channels::VOLUME_71, 71);
	AudioCreateVolume(Channels::VOLUME_72, 72);
	AudioCreateVolume(Channels::VOLUME_73, 73);
	AudioCreateVolume(Channels::VOLUME_74, 74);
	AudioCreateVolume(Channels::VOLUME_75, 75);
	AudioCreateVolume(Channels::VOLUME_76, 76);
	AudioCreateVolume(Channels::VOLUME_77, 77);
	AudioCreateVolume(Channels::VOLUME_78, 78);
	AudioCreateVolume(Channels::VOLUME_79, 79);
	AudioCreateVolume(Channels::VOLUME_80, 80);
	AudioCreateVolume(Channels::VOLUME_81, 81);
	AudioCreateVolume(Channels::VOLUME_82, 82);
	AudioCreateVolume(Channels::VOLUME_83, 83);
	AudioCreateVolume(Channels::VOLUME_84, 84);
	AudioCreateVolume(Channels::VOLUME_85, 85);
	AudioCreateVolume(Channels::VOLUME_86, 86);
	AudioCreateVolume(Channels::VOLUME_87, 87);
	AudioCreateVolume(Channels::VOLUME_88, 88);
	AudioCreateVolume(Channels::VOLUME_89, 89);
	AudioCreateVolume(Channels::VOLUME_90, 90);
	AudioCreateVolume(Channels::VOLUME_91, 91);
	AudioCreateVolume(Channels::VOLUME_92, 92);
	AudioCreateVolume(Channels::VOLUME_93, 93);
	AudioCreateVolume(Channels::VOLUME_94, 94);
	AudioCreateVolume(Channels::VOLUME_95, 95);
	AudioCreateVolume(Channels::VOLUME_96, 96);
	AudioCreateVolume(Channels::VOLUME_97, 97);
	AudioCreateVolume(Channels::VOLUME_98, 98);
	AudioCreateVolume(Channels::VOLUME_99, 99);
	AudioCreateVolume(Channels::VOLUME_100, 100);
	AudioCreateVolume(Channels::VOLUME_101, 101);
	AudioCreateVolume(Channels::VOLUME_102, 102);
	AudioCreateVolume(Channels::VOLUME_103, 103);
	AudioCreateVolume(Channels::VOLUME_104, 104);
	AudioCreateVolume(Channels::VOLUME_105, 105);
	AudioCreateVolume(Channels::VOLUME_106, 106);
	AudioCreateVolume(Channels::VOLUME_107, 107);
	AudioCreateVolume(Channels::VOLUME_108, 108);
	AudioCreateVolume(Channels::VOLUME_109, 109);
	AudioCreateVolume(Channels::VOLUME_110, 110);
	AudioCreateVolume(Channels::VOLUME_111, 111);
	AudioCreateVolume(Channels::VOLUME_112, 112);
	AudioCreateVolume(Channels::VOLUME_113, 113);
	AudioCreateVolume(Channels::VOLUME_114, 114);
	AudioCreateVolume(Channels::VOLUME_115, 115);
	AudioCreateVolume(Channels::VOLUME_116, 116);
	AudioCreateVolume(Channels::VOLUME_117, 117);
	AudioCreateVolume(Channels::VOLUME_118, 118);
	AudioCreateVolume(Channels::VOLUME_119, 119);
	AudioCreateVolume(Channels::VOLUME_120, 120);
	AudioCreateVolume(Channels::VOLUME_121, 121);
	AudioCreateVolume(Channels::VOLUME_122, 122);
	AudioCreateVolume(Channels::VOLUME_123, 123);
	AudioCreateVolume(Channels::VOLUME_124, 124);
	AudioCreateVolume(Channels::VOLUME_125, 125);
	AudioCreateVolume(Channels::VOLUME_126, 126);
	AudioCreateVolume(Channels::VOLUME_127, 127);
	AudioCreateVolume(Channels::VOLUME_128, 128);
}

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
