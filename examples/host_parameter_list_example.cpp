#include "prettyscope.hpp"

#include <cstddef>
#include <iostream>

namespace
{
void printHeader(const char* kind)
{
    std::cout << kind << '\n';
}

void printParameterPrefix(const char* stableId, prettyscope::VisualParameterStableId numericId)
{
    std::cout << "  " << stableId << " #" << numericId.value;
}

int countAutomatableFloatParameters()
{
    size_t count = 0;
    const prettyscope::VisualFloatParameter* parameters = prettyscope::visualFloatParameters(count);

    int automatable = 0;
    printHeader("float");
    for (size_t i = 0; i < count; ++i)
    {
        const prettyscope::VisualFloatParameter& parameter = parameters[i];
        if (!parameter.automatable)
        {
            continue;
        }

        ++automatable;
        printParameterPrefix(parameter.stableId, parameter.numericId);
        std::cout << " [" << parameter.minimum << ", " << parameter.maximum << "]"
                  << " default " << parameter.defaultValue
                  << " midpoint " << parameter.midpoint
                  << " name \"" << parameter.displayName << "\"\n";
    }

    return automatable;
}

int countAutomatableBoolParameters()
{
    size_t count = 0;
    const prettyscope::VisualBoolParameter* parameters = prettyscope::visualBoolParameters(count);

    int automatable = 0;
    printHeader("bool");
    for (size_t i = 0; i < count; ++i)
    {
        const prettyscope::VisualBoolParameter& parameter = parameters[i];
        if (!parameter.automatable)
        {
            continue;
        }

        ++automatable;
        printParameterPrefix(parameter.stableId, parameter.numericId);
        std::cout << " default " << (parameter.defaultValue ? "true" : "false")
                  << " name \"" << parameter.displayName << "\"\n";
    }

    return automatable;
}

int countAutomatableChoiceParameters()
{
    size_t count = 0;
    const prettyscope::VisualChoiceParameter* parameters = prettyscope::visualChoiceParameters(count);

    int automatable = 0;
    printHeader("choice");
    for (size_t i = 0; i < count; ++i)
    {
        const prettyscope::VisualChoiceParameter& parameter = parameters[i];
        if (!parameter.automatable)
        {
            continue;
        }

        ++automatable;
        printParameterPrefix(parameter.stableId, parameter.numericId);
        std::cout << " options " << parameter.optionCount
                  << " default " << parameter.defaultValue
                  << " name \"" << parameter.displayName << "\"\n";
    }

    return automatable;
}
}

int main()
{
    int automatable = 0;
    automatable += countAutomatableFloatParameters();
    automatable += countAutomatableBoolParameters();
    automatable += countAutomatableChoiceParameters();

    std::cout << "automatable total " << automatable << '\n';
    return automatable > 0 ? 0 : 1;
}
