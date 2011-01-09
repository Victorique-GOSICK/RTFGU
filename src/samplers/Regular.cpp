// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Regular.h"

#include <cassert>
#include <cmath>


namespace {

    const int DEFAULT_BUNDLE_SIZE = 4;

}


Regular2D::Regular2D() : bundleSize_(DEFAULT_BUNDLE_SIZE) {}
Regular2D::Regular2D(int bundleSize) : bundleSize_(bundleSize) {}
Regular2D::~Regular2D() {}


const SampleGenerator2D::SampleBundle& Regular2D::get_next() {
    // Lazily create samples.
    if (samples_.empty())
        generate_samples();

    return samples_;
}


void Regular2D::set_bundle_size(size_t numSamples) {
    double intPart = 0.0;
    double fracPart = modf((double)numSamples, &intPart);
    assert( 0.0 == fracPart && "The number of samples in a bundle must be a square." );
    bundleSize_ = numSamples;
    samples_.clear(); // force a new generation next time get_next is called.
}


int Regular2D::get_bundle_size() const {
    return bundleSize_;
}


/*
    0  0.5  1
    ________
    | . | . |
    |---+---|
    | . | . |
    ---------
    ____________
    | . | . | . |
    | . | . | . |
    | . | . | . |
    -------------
*/
void Regular2D::generate_samples() {
    float n = sqrt((float)bundleSize_);
    float inv_n = 1 / n;
    float start = inv_n / 2.0f;
    int in = (int) n;

    for (int p = 0; p < in; p++) {
        for (int q = 0; q < in; q++) {
            samples_.push_back(Point2D(start + q*inv_n, start + p*inv_n));
        }
    }
}
