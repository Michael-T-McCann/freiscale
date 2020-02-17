#include "Composition.hpp"

#include "otfft/otfft.h"

#include <cassert>
#include <iostream>

void Sound::compute_spectrums() {

	uint32_t spectrum_count = (this->size() + SpectrumStep-1) / SpectrumStep;
	spectrums.resize(SpectrumSize * spectrum_count);

	//Based on example in OTFFT docs!

	//processing buffers:
	OTFFT::simd_array< double > x(SpectrumSize);
	OTFFT::simd_array< OTFFT::complex_t > y(SpectrumSize);

	//FFT processor:
	OTFFT::RFFT rfft(SpectrumSize);

	//window:
	std::vector< float > window;

	//...rectangular window:
	//  wikipedia says a lot about this topic :-/
	window.assign(SpectrumSize, 1.0f);

	for (uint32_t offset = 0; offset < this->size(); offset += SpectrumStep) {
		//copy to input buffer:
		uint32_t len = std::min< uint32_t >(this->size() - offset, SpectrumSize);
		for (uint32_t s = 0; s < len; ++s) {
			x[s] = window[s] * (*this)[offset+s];
		}
		for (uint32_t s = len; s < SpectrumSize; ++s) {
			x[s] = 0.0;
		}

		//transform:
		rfft.fwd(x.p, y.p);

		//compute power:
		float *spectrum = &(spectrums[(offset / SpectrumStep) * SpectrumSize]);
		for (uint32_t s = 0; s < SpectrumSize; ++s) {
			//assert( (offset / SpectrumStep) * SpectrumSize + s < spectrums.size() );
			spectrum[s] = y[s].Re * y[s].Re + y[s].Im * y[s].Im;
		}
	}
}
