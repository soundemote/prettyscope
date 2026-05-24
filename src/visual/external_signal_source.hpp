#pragma once

#include "visual/signal_source.hpp"

#include <vector>

namespace prettyscope
{
class ExternalSignalSource : public SignalSource
{
public:
    void setMonoInput(const float* samples, int sampleCount);
    void setStereoInput(const float* left, const float* right, int sampleCount);

    SignalSourceInfo info() const override;
    void advance(SignalBuffer& signal, float dt) override;

private:
    std::vector<float> left_;
    std::vector<float> right_;
    SignalLayout layout_ = SignalLayout::Stereo;
};
}
