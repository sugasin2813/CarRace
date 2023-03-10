#pragma once
class BaseScene{
public:
	BaseScene();
	virtual void initialize() = 0;
	virtual void finalize() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};