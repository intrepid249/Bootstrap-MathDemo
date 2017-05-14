#pragma once

#ifndef SCREENDEFINES
#define SCREENDEFINES

#ifdef _DEBUG
#define APPTITLE "Math Demonstration - (DEBUG)"
#else
#define APPTITLE "Math Demonstration"
#endif
#define SCREENWIDTH 1640
#define SCREENHEIGHT 960
#define FULLSCREEN false
#endif

#pragma region Vehicles
enum eControlID { FORWARD, BACKWARD, LEFT, RIGHT, SHOOT, SECONDARYFIRE };

	#pragma region Tank
	#define TANK_MOVESPEED 115.f
	#define TANK_TURNSPEED 2.5f
	#define TANK_CANNON_SHOTDELAY 1.3f
	#define TANK_MACHINEGUN_SHOTDELAY 0.3f
	#pragma endregion
#pragma endregion

#pragma region Weapons
	#define TANKSHELL_SPEED 300.f
	#define TANKSHELL_LIFETIME 5
	#define TANKBULLET_SPEED 400.f
	#define TANKBULLET_LIFETIME 5
#pragma endregion

#pragma region UTILS
template <typename Base, typename T>
inline bool instanceof(const T*) {
	return std::is_base_of<Base, T>::value;
}
#pragma endregion