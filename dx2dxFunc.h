#pragma once
#include "dx2dxStruct.h"

int RandomInt(int min, int max);
float RandomFloat(float min, float max);

bool KEY_DOWN_ONCE(int vKey, bool *keyState);
bool KEY_UP_ONCE(int vKey, bool *keyState);

dx2dx::Point GET_MOUSE_POS();

bool LBUTTON_DOWN_ONCE();
bool LBUTTON_UP_ONCE();

// * WM_CLOSE �޽����� �߻����Ѽ� �����Ų��.
void GAME_SHUTDOWN();