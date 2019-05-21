#pragma once

#include "SeetyDog/Layer.h"

#include "Game.h"
#include "ResourceManager.h"

class BreakoutLayer : public SeetyDog::Layer {
public://Constructors/Destructors
	BreakoutLayer();
	~BreakoutLayer();

public://Methods
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(SeetyDog::Event& event) override;

private:
	const unsigned int m_Width = 1200, m_Height = 800;
	float m_DeltaTime, m_LastFrame;
	Game breakout;
};