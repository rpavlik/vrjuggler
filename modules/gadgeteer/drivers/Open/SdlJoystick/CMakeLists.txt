include_directories(${SDL_INCLUDE_DIR})
gadgeteer_add_driver(SdlJoystick
	SdlJoystick.cpp
	SdlJoystick.h
	SdlRumbleEffect.cpp
	SdlRumbleEffect.h
	SdlRumbleEffectConstant.cpp
	SdlRumbleEffectConstant.h
	SdlRumbleEffectPeriodic.cpp
	SdlRumbleEffectPeriodic.h
	SdlRumbleEffectRamp.cpp
	SdlRumbleEffectRamp.h)
target_link_libraries(SdlJoystick_drv ${SDL_LIBRARY})