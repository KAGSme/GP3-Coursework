#pragma once

#include "cTransform.h"
#include "cShader.h"

class cActor
{
public:
	cActor();
	~cActor();

	virtual void begin() {}
	virtual void update(float elapsedTime) {}
	virtual void render() {}

	cShader* getShader() { return m_shader; };
	cTransform* getTransform() { return m_transform; };
	void setShader(cShader* newShader) { m_shader = newShader; };
	void setTransform(cTransform* newTransform) { m_transform = newTransform; };

private:
	cTransform* m_transform;
	cShader* m_shader;
};

