#include "pwm.h"

const uint8_t PWM_CHANNEL_TO_INPUT[PWM_CHANNELS] = {
	1, 0, 7, 6, 5, 4, 3, 2
};

volatile uint8_t pwm_pins_state_saved = 0x0;
volatile uint16_t pwm_rising_edge_ticks[PWM_CHANNELS] = {0};
volatile uint16_t pwm_pulse_width_us[PWM_CHANNELS] = {0};

PwmFrame volatile pwm_buffer[PWM_BUFFER_SIZE] {};
PwmFrame volatile *volatile pwm_buffer_write = pwm_buffer;
PwmFrame volatile *volatile pwm_buffer_read = pwm_buffer;

void PwmInit()
{
	for (uint8_t i = 0; i < PWM_CHANNELS; ++i) {
		pwm_pulse_width_us[i] = PWM_PULSE_WIDTH_CENTER_US;
	}
}

void PwmProcessBuffer()
{
	while (true) {
		auto volatile read_next = PwmBufferFrameNext(pwm_buffer_read);
		if (read_next == pwm_buffer_write) {
			break;
		}
		auto frame_prev = pwm_buffer_read;
		auto frame = read_next;
		auto pins_diff = (frame->pins ^ frame_prev->pins);
		uint8_t pin_mask = 0x1;
		for (uint8_t input_n = 0; input_n < PWM_CHANNELS; ++input_n) {
			if (pins_diff & pin_mask) {
				if (frame->pins & pin_mask) {
					pwm_rising_edge_ticks[input_n] = frame->ticks;
				} else {
					auto pulse_width_us = (frame->ticks - pwm_rising_edge_ticks[input_n])
						/ PWM_TICKS_PER_US;
					//if (PwmCheckPulseWidth(pulse_width_us)) {
						pwm_pulse_width_us[input_n] = pulse_width_us;
					//}
				}
			}
			pin_mask <<= 1;
		}
		pwm_buffer_read = read_next;
	}
}
