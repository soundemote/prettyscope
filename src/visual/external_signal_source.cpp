#include "visual/external_signal_source.hpp"

#include <algorithm>

namespace prettyscope
{
void ExternalSignalSource::setMonoInput(const float* samples, int sampleCount)
{
    const int count = std::max(0, sampleCount);
    left_.assign(samples, samples + count);
    right_.assign(left_.begin(), left_.end());
    layout_ = SignalLayout::Mono;
}

void ExternalSignalSource::setStereoInput(const float* left, const float* right, int sampleCount)
{
    const int count = std::max(0, sampleCount);
    left_.assign(left, left + count);
    right_.assign(right, right + count);
    layout_ = SignalLayout::Stereo;
}

SignalSourceInfo ExternalSignalSource::info() const
{
    return {"external", layout_, layout_ == SignalLayout::Stereo ? TraceMode::Xy : TraceMode::Time};
}

void ExternalSignalSource::advance(SignalBuffer& signal, float)
{
    if (left_.empty())
    {
        for (int i = 0; i < signal.size(); ++i)
        {
            signal[i] = 0.0f;
            signal.right(i) = 0.0f;
        }
        return;
    }

    for (int i = 0; i < signal.size(); ++i)
    {
        const int sourceIndex = i * static_cast<int>(left_.size()) / signal.size();
        signal[i] = left_[static_cast<size_t>(sourceIndex)];
        signal.right(i) = right_[static_cast<size_t>(sourceIndex)];
    }
}
}
