#pragma once

#ifndef SCREENDEFINES
#define SCREENDEFINES

#define APPTITLE "Math Demonstration"
#define SCREENWIDTH 1080
#define SCREENHEIGHT 720
#define FULLSCREEN false
#endif

#pragma region Tank
#define TANK_MOVESPEED 115.f
#define TANK_TURNSPEED 2.5f
#pragma endregion

#pragma region UTILS
template <typename Base, typename T>
inline bool instanceof(const T*) {
	return std::is_base_of<Base, T>::value;
}
#pragma endregion