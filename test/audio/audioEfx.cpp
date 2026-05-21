#include "audioEfx.h"
//#include "stdafx.h"

// TODO: if the compilation is too slow, I might switch back to pre-compiled headers -> stdafx.h and change use precompiled headers to yes in project settings.

namespace audioEfx {
	int clamp(int input){ return input&(~0xFF)?0xFF:input; }

	int boost(int input, float gain, int value){ return clamp(input*(int)gain+value); }

	int gate(int input, int threshold, int release, float ratio){
		if(input < threshold){
			_gate_counter = _gate_counter>0?--_gate_counter:0;
			input *= (ratio + ((1.f-ratio) * _gate_counter/release));
		} else { _gate_counter = release; input = boost(input, 1.2); }

		return clamp(input);
	}

	int compressor(int input, int threshold, int release, float ratio){
		if(input < threshold){
			_gate_counter = _gate_counter>0?--_gate_counter:0;
			input *= (ratio + ((1.f-ratio) * _gate_counter/release));
		} else { 
			_gate_counter = release;

			input = ratio * (input - threshold); 
		}

		return clamp(input);
	}
}