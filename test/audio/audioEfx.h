#pragma once

namespace audioEfx {
	namespace {
		int _gate_counter = 0;
	} // anonymous namespace

	int clamp(int input);
	int gate(int input, int threshold, int release, float ratio);
	int boost(int input, float gain, int value = 0);
} // namespace audioEfx