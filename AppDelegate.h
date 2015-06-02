#pragma once
#include "Application.h"


class AppDelegate final
	//: public dx2dx::Application
{
	friend class dx2dx::Game;
private:
	DISALLOW_COPY_AND_ASSIGN(AppDelegate);

protected:
	AppDelegate();
	~AppDelegate();

private:
	void AppLaunching();

};

