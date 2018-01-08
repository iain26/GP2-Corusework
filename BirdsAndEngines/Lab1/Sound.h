#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Sound
{
	struct data {
		int sID, bID;
		char* b;
		std::string n;
		data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sID = sI;
			this->bID = bI;
			this->b = b;
			this->n = n;
		}

	};
	 
	struct Vector3
	{
		float x, y, z;
	};
	std::vector<data> dataList;
	ALCcontext* alContext;
	ALCdevice *alDevice;
	bool isBigEndian();
	int convertToInt(char* buffer, int length);
	char* LoadWAVfile(const char* fn, int& channel, int& sr, int& bps, int& size);

public:
	Sound();
	~Sound();
	unsigned int AudioFileLoad(const char* filename);
	void Play(unsigned int id, glm::vec3& pos);
	void Stop(unsigned int id);
	void SetAudioListener(glm::vec3& pos, glm::vec3& camLookAt);

private:

};

