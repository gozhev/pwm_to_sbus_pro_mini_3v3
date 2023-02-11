#pragma once

#include <stdint.h>

constexpr uint16_t SBUS_VALUE_CENTER {1000};
constexpr uint16_t SBUS_VALUE_RADIUS {640};
constexpr uint16_t SBUS_VALUE_MIN {0};
constexpr uint16_t SBUS_VALUE_MAX {2047};

void SbusInit();
void SbusWrite();
void SbusBuildPacket();

inline void SbusInit()
{
}

inline uint16_t SbusFromPwm(uint16_t pulse_width_us) {
	int32_t value =
		(static_cast<int32_t>(pulse_width_us)
			- static_cast<int32_t>(PWM_PULSE_WIDTH_CENTER_US))
		* static_cast<int32_t>(SBUS_VALUE_RADIUS)
		/ static_cast<int32_t>(PWM_PULSE_WIDTH_RADIUS_US)
		+ static_cast<int32_t>(SBUS_VALUE_CENTER);
	if (value < SBUS_VALUE_MIN) {
		value = SBUS_VALUE_MIN;
	} else if (value > SBUS_VALUE_MAX) {
		value = SBUS_VALUE_MAX;
	}
	return static_cast<uint16_t>(value);
}
