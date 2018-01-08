#include "Sound.h"


Sound::Sound()
{
	// opens sound card and returns if it hasn't
	alDevice = alcOpenDevice(NULL);
	if (alDevice == NULL)
	{
		std::cout << "cannot open sound card" << std::endl;
	}
	// creates context and verifies and then set to current context
	alContext = alcCreateContext(alDevice, NULL);
	if (alContext == NULL)
	{
		std::cout << "cannot open context" << std::endl;
	}
	alcMakeContextCurrent(alContext);
}

// closes openAL
Sound::~Sound()
{
	for (unsigned int i = 0; i < dataList.size(); i++)
	{
		alDeleteSources(1, (unsigned int*)&dataList[i].sID);
		if (dataList[i].bID != -1)
		{
			alDeleteBuffers(1, (unsigned int*)&dataList[i].bID);
			delete[] dataList[i].b;
		}
	}
	alcDestroyContext(alContext);
	alcCloseDevice(alDevice);
}

// checks if system stores most significant value first in byte sequence
bool Sound::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

// makes char arrays into ints for WAV files
int Sound::convertToInt(char* buffer, int length)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < length; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < length; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

// loads wav file
char* Sound::LoadWAVfile(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4); 
	in.read(buffer, 4);
	in.read(buffer, 4); 
	in.read(buffer, 2); 
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);

	char* soundData = new char[size];
	in.read(soundData, size);
	return soundData;
}

// gets audio file in location
unsigned int Sound::AudioFileLoad(const char* filename)
{
	bool found = false;
	unsigned int sID, bID;
	char* Data = NULL;
	for (unsigned int i = 0; i < dataList.size(); i++)
	{
		if (dataList[i].n == filename && dataList[i].bID != -1)
		{
			bID = dataList[i].bID;
			found = true;
			break;
		}
	}
	if (!found)
	{
		int channel, sampleRate, bps, size;
		Data = LoadWAVfile(filename, channel, sampleRate, bps, size);
		unsigned int format;
		alGenBuffers(1, &bID);

		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}

		}

		alBufferData(bID, format, Data, size, sampleRate);
	}
	alGenSources(1, &sID);
	alSourcei(sID, AL_BUFFER, bID);
	alSourcef(sID, AL_REFERENCE_DISTANCE, 1.0f);
	dataList.push_back(data(sID, (!found ? bID : -1), Data, filename));
	return sID;
}

// plays audio specicgied as id at location passed in 
void Sound::Play(unsigned int id, glm::vec3& pos)
{
	alSource3f(id, AL_POSITION, pos.x, pos.y, pos.z);
	alSourcePlay(id);
}

// stops specified audio
void Sound::Stop(unsigned int id)
{
	alSourceStop(id);
}