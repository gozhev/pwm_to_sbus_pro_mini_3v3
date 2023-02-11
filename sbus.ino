#include "sbus.h"
#include "pwm.h"

#include <string.h>

constexpr uint8_t SBUS_PACKET_SIZE {25};
constexpr uint8_t SBUS_DATA_BITS_PER_FRAME {8};
constexpr uint8_t SBUS_BITS_PER_FRAME {12};
constexpr uint8_t SBUS_BITS_PER_CHANNEL {11};
constexpr uint8_t SBUS_CHANNELS_PER_PACKET {16};

uint16_t sbus_frames[SBUS_PACKET_SIZE] {};

uint16_t SbusBuildFrame(uint8_t value)
{
	uint8_t parity {};
	for (uint8_t x = value; x; x >>= 1) {
		parity ^= (x & 0x1);
	}
	uint16_t result {};
	result |= 0b11;
	result <<= 1;
	result |= parity;
	result <<= SBUS_DATA_BITS_PER_FRAME;
	result |= value & ~((~0U) << SBUS_DATA_BITS_PER_FRAME);
	result <<= 1;
	return result;
}

void SbusBuildPacket()
{
	sbus_frames[0] = SbusBuildFrame(0x0F);
	sbus_frames[23] = SbusBuildFrame(0x00);
	sbus_frames[24] = SbusBuildFrame(0x00);
	uint8_t channel {};
	uint8_t buffer_size {};
	uint32_t buffer {};
	constexpr auto DATA_FRAMES_PER_PACKET = SBUS_CHANNELS_PER_PACKET
			* SBUS_BITS_PER_CHANNEL / SBUS_DATA_BITS_PER_FRAME;
	for (uint8_t frame = 1U; frame < 1U + DATA_FRAMES_PER_PACKET; ++frame) {
		if (buffer_size < SBUS_DATA_BITS_PER_FRAME) {
			auto pwm_value = PwmGetChannelValue(channel);
			auto sbus_value = SbusFromPwm(pwm_value);
			buffer |= (static_cast<uint32_t>(sbus_value) << buffer_size);
			buffer_size += SBUS_BITS_PER_CHANNEL;
			channel++;
		}
		sbus_frames[frame] = SbusBuildFrame(static_cast<uint8_t>(buffer));
		buffer >>= SBUS_DATA_BITS_PER_FRAME;
		buffer_size -= SBUS_DATA_BITS_PER_FRAME;
	}
}

void SbusWrite()
{
	auto sbus_data = sbus_frames;
	auto sbus_data_end = sbus_frames + SBUS_PACKET_SIZE;
	uint16_t frame_bits = 0x0;
	uint8_t logic_level = 0U;

	uint8_t pins_saved = 0x0;
	uint8_t pins = 0x0;
	uint16_t ticks = 0x0;

	pins = GpioGetPinsState();
	cli();
	TIFR2 |= _BV(OCF2A);
	for (; sbus_data != sbus_data_end; ++sbus_data) {
		frame_bits = *sbus_data;
		for (uint8_t bit_n = SBUS_BITS_PER_FRAME; bit_n; --bit_n) {
			logic_level = (frame_bits & 0x1);
			while (!(TIFR2 & _BV(OCF2A)));
			if (logic_level) {
				PORTD &= ~_BV(1);
			} else {
				PORTD |= _BV(1);
			}
			TIFR2 |= _BV(OCF2A);
			frame_bits >>= 1;

			ticks = PwmGetTicks();
			pins = GpioGetPinsState();
			if (pins != pins_saved) {
				pins_saved = pins;
				pwm_buffer_write->ticks = ticks;
				pwm_buffer_write->pins = pins;
				pwm_buffer_write = PwmBufferFrameNext(pwm_buffer_write);
			}
		}
	}
	sei();
}
