#pragma once

#include <algorithm>
#include <vector>

namespace prettyscope
{
class SignalBuffer
{
public:
    explicit SignalBuffer(int sampleCount)
        : left_(static_cast<size_t>(std::max(2, sampleCount)), 0.0f),
          right_(left_.size(), 0.0f)
    {
    }

    int size() const
    {
        return static_cast<int>(left_.size());
    }

    void resize(int sampleCount)
    {
        const size_t count = static_cast<size_t>(std::max(2, sampleCount));
        left_.assign(count, 0.0f);
        right_.assign(count, 0.0f);
    }

    float* data()
    {
        return left_.data();
    }

    const float* data() const
    {
        return left_.data();
    }

    float* rightData()
    {
        return right_.data();
    }

    const float* rightData() const
    {
        return right_.data();
    }

    float& operator[](int index)
    {
        return left_[static_cast<size_t>(index)];
    }

    float operator[](int index) const
    {
        return left_[static_cast<size_t>(index)];
    }

    float& right(int index)
    {
        return right_[static_cast<size_t>(index)];
    }

    float right(int index) const
    {
        return right_[static_cast<size_t>(index)];
    }

private:
    std::vector<float> left_;
    std::vector<float> right_;
};
}
