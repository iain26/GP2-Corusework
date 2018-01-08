#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Cam
{
public:
	Cam()
	{
	}

	//Sets information for perspective camera 
	void InitialiseCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->proj = glm::perspective(fov, aspect, nearClip, farClip);
	}

	//the viewable space on screen i.e. whats camera pointing at
	inline glm::mat4 GetViewProjection() const
	{
		return proj * glm::lookAt(pos, pos + forward, up);
	}
	
	void SetPos(glm::vec3 pos) {
		this->pos = pos;
	}

	glm::vec3 GetPos() {
		return this->pos;
	}

protected:
private:
	glm::mat4 proj;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};


