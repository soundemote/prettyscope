#include "app/preset_store.hpp"

#include "visual/visual_param_limits.hpp"

#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

namespace prettyscope
{
namespace
{
std::filesystem::path presetPath()
{
    return std::filesystem::current_path() / "presets" / "default.prettyscope.json";
}

const char* traceModeName(TraceMode mode)
{
    return mode == TraceMode::Xy ? "xy" : "time";
}

const char* decayStyleName(DecayStyle style)
{
    return style == DecayStyle::Phosphor ? "phosphor" : "classic";
}

const char* signalModeName(TestSignalGenerator::Mode mode)
{
    switch (mode)
    {
    case TestSignalGenerator::Mode::Lissajousish:
        return "fold";
    case TestSignalGenerator::Mode::BassPulse:
        return "bass";
    case TestSignalGenerator::Mode::Musical:
    default:
        return "musical";
    }
}

bool readFile(std::string& out)
{
    std::ifstream file(presetPath());
    if (!file)
    {
        return false;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    out = buffer.str();
    return true;
}

bool findString(const std::string& text, const char* key, std::string& value)
{
    const std::regex pattern(std::string("\"") + key + "\"\\s*:\\s*\"([^\"]*)\"");
    std::smatch match;
    if (!std::regex_search(text, match, pattern))
    {
        return false;
    }

    value = match[1].str();
    return true;
}

bool findFloat(const std::string& text, const char* key, float& value)
{
    const std::regex pattern(std::string("\"") + key + "\"\\s*:\\s*(-?[0-9]+(?:\\.[0-9]+)?)");
    std::smatch match;
    if (!std::regex_search(text, match, pattern))
    {
        return false;
    }

    value = std::stof(match[1].str());
    return true;
}

bool findBool(const std::string& text, const char* key, bool& value)
{
    const std::regex pattern(std::string("\"") + key + "\"\\s*:\\s*(true|false)");
    std::smatch match;
    if (!std::regex_search(text, match, pattern))
    {
        return false;
    }

    value = match[1].str() == "true";
    return true;
}

bool findColor(const std::string& text, const char* key, RgbColor& color)
{
    const std::regex pattern(std::string("\"") + key + "\"\\s*:\\s*\\[\\s*(-?[0-9]+(?:\\.[0-9]+)?)\\s*,\\s*(-?[0-9]+(?:\\.[0-9]+)?)\\s*,\\s*(-?[0-9]+(?:\\.[0-9]+)?)\\s*\\]");
    std::smatch match;
    if (!std::regex_search(text, match, pattern))
    {
        return false;
    }

    color = {std::stof(match[1].str()), std::stof(match[2].str()), std::stof(match[3].str())};
    return true;
}
}

bool PresetStore::saveDefault(const VisualParams& params, const TestSignalGenerator& generator)
{
    std::filesystem::create_directories(presetPath().parent_path());

    std::ofstream file(presetPath());
    if (!file)
    {
        return false;
    }

    file << "{\n";
    file << "  \"traceMode\": \"" << traceModeName(params.traceMode) << "\",\n";
    file << "  \"signalMode\": \"" << signalModeName(generator.mode()) << "\",\n";
    file << "  \"decayStyle\": \"" << decayStyleName(params.decayStyle) << "\",\n";
    file << "  \"traceGain\": " << params.traceGain << ",\n";
    file << "  \"glowStrength\": " << params.glowStrength << ",\n";
    file << "  \"traceWidth\": " << params.traceWidth << ",\n";
    file << "  \"glowWidth\": " << params.glowWidth << ",\n";
    file << "  \"persistence\": " << params.persistence << ",\n";
    file << "  \"fastDecay\": " << params.fastDecay << ",\n";
    file << "  \"afterglow\": " << params.afterglow << ",\n";
    file << "  \"persistenceEnabled\": " << (params.persistenceEnabled ? "true" : "false") << ",\n";
    file << "  \"showGrid\": " << (params.showGrid ? "true" : "false") << ",\n";
    file << "  \"traceColor\": [" << params.traceColor.r << ", " << params.traceColor.g << ", " << params.traceColor.b << "],\n";
    file << "  \"glowColor\": [" << params.glowColor.r << ", " << params.glowColor.g << ", " << params.glowColor.b << "],\n";
    file << "  \"backgroundColor\": [" << params.backgroundColor.r << ", " << params.backgroundColor.g << ", " << params.backgroundColor.b << "]\n";
    file << "}\n";
    return true;
}

bool PresetStore::loadDefault(VisualParams& params, TestSignalGenerator& generator)
{
    std::string text;
    if (!readFile(text))
    {
        return false;
    }

    std::string value;
    if (findString(text, "traceMode", value))
    {
        params.traceMode = value == "xy" ? TraceMode::Xy : TraceMode::Time;
    }
    if (findString(text, "signalMode", value))
    {
        if (value == "fold")
        {
            generator.setMode(TestSignalGenerator::Mode::Lissajousish);
        }
        else if (value == "bass")
        {
            generator.setMode(TestSignalGenerator::Mode::BassPulse);
        }
        else
        {
            generator.setMode(TestSignalGenerator::Mode::Musical);
        }
    }
    if (findString(text, "decayStyle", value))
    {
        params.decayStyle = value == "phosphor" ? DecayStyle::Phosphor : DecayStyle::Classic;
    }

    findFloat(text, "traceGain", params.traceGain);
    findFloat(text, "glowStrength", params.glowStrength);
    findFloat(text, "traceWidth", params.traceWidth);
    findFloat(text, "glowWidth", params.glowWidth);
    findFloat(text, "persistence", params.persistence);
    findFloat(text, "fastDecay", params.fastDecay);
    findFloat(text, "afterglow", params.afterglow);
    findBool(text, "persistenceEnabled", params.persistenceEnabled);
    findBool(text, "showGrid", params.showGrid);
    findColor(text, "traceColor", params.traceColor);
    findColor(text, "glowColor", params.glowColor);
    findColor(text, "backgroundColor", params.backgroundColor);

    clampVisualParams(params);
    ++params.clearRevision;
    return true;
}
}
