#include "visual/shaders.hpp"

#include <cstring>
#include <iostream>

namespace
{
bool contains(const char* name, const char* source, const char* needle)
{
    if (source != nullptr && std::strstr(source, needle) != nullptr)
    {
        return true;
    }

    std::cerr << name << " does not contain " << needle << '\n';
    return false;
}
}

int main()
{
    bool passed = true;
    passed = contains("beam fragment", prettyscope::shaders::kBeamFragment, "erfApprox") && passed;
    passed = contains("beam fragment", prettyscope::shaders::kBeamFragment, "beamIntensity") && passed;
    passed = contains("decay fragment", prettyscope::shaders::kDecayFragment, "afterglow") && passed;
    passed = contains("decay fragment", prettyscope::shaders::kDecayFragment, "brightDrain") && passed;
    passed = contains("decay fragment", prettyscope::shaders::kDecayFragment, "tailBoost") && passed;
    return passed ? 0 : 1;
}
