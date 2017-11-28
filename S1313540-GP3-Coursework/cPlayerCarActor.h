#pragma once
#include "cActor.h"
#include "cModel.h"
class cPlayerCarActor :
	public cActor
{
public:
	cPlayerCarActor();
	~cPlayerCarActor();

	virtual void begin() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;
private:
	cModel* m_model;
};

