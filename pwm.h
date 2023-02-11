#pragma once

#define PWM_CHANNELS 8U

// f / prescaler / 10^-6 sec
#define PWM_TICKS_PER_US (F_CPU / 8U / 1000U / 1000U)

constexpr uint16_t PWM_PULSE_WIDTH_CENTER_US {1500U};
constexpr uint16_t PWM_PULSE_WIDTH_RADIUS_US {400U};
constexpr uint16_t PWM_PULSE_WIDTH_MIN_US {900U};
constexpr uint16_t PWM_PULSE_WIDTH_MAX_US {2100U};

extern const uint8_t PWM_CHANNEL_TO_INPUT[PWM_CHANNELS];
extern volatile uint8_t pwm_pins_state_saved;
extern volatile uint16_t pwm_rising_edge_ticks[PWM_CHANNELS];
extern volatile uint16_t pwm_pulse_width_us[PWM_CHANNELS];

struct PwmFrame {
	uint8_t pins;
	uint16_t ticks;
};

constexpr uint8_t PWM_BUFFER_SIZE {64U};
extern PwmFrame volatile pwm_buffer[PWM_BUFFER_SIZE];
constexpr PwmFrame volatile* pwm_buffer_end = pwm_buffer + PWM_BUFFER_SIZE;
extern PwmFrame volatile *volatile pwm_buffer_write;
extern PwmFrame volatile *volatile pwm_buffer_read;

void PwmInit();
inline uint8_t PwmChannelToInput(uint8_t channel);
inline uint16_t PwmGetChannelValue(uint8_t channel);
inline uint16_t PwmGetTicks();
inline bool PwmCheckPulseWidth(uint16_t pulse_width_us);
inline void PwmResetChannels();

inline PwmFrame volatile* PwmBufferFrameNext(PwmFrame volatile* frame)
{
	if ((++frame) == pwm_buffer_end) {
		return pwm_buffer;
	}
	return frame;
}

inline uint16_t PwmGetChannelValue(uint8_t channel)
{
	if (channel < PWM_CHANNELS) {
		return pwm_pulse_width_us[PwmChannelToInput(channel)];
	} else {
		return PWM_PULSE_WIDTH_CENTER_US;
	}
}

inline uint8_t PwmChannelToInput(uint8_t channel)
{
	return PWM_CHANNEL_TO_INPUT[channel];
}

inline uint16_t PwmGetTicks()
{
	return TCNT1;
}

inline bool PwmCheckPulseWidth(uint16_t pulse_width_us)
{
	return PWM_PULSE_WIDTH_MIN_US <= pulse_width_us &&
			pulse_width_us <= PWM_PULSE_WIDTH_MAX_US;
}

inline void PwmResetChannels()
{
	GpioInterruptsClear();
	pwm_pins_state_saved = 0x0;
}
