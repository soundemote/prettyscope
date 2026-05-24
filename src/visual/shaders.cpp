#include "visual/shaders.hpp"

namespace prettyscope::shaders
{
const char* kBeamVertex = R"GLSL(
#version 150

in vec2 segmentStart;
in vec2 segmentEnd;
in float cornerIndex;

uniform vec2 viewportSize;
uniform float beamSize;

out vec3 beamFrame;

void main()
{
    vec2 startPx = (segmentStart * 0.5 + 0.5) * viewportSize;
    vec2 endPx = (segmentEnd * 0.5 + 0.5) * viewportSize;
    vec2 dir = endPx - startPx;
    float len = length(dir);

    if (len > 0.0001) {
        dir /= len;
    } else {
        dir = vec2(1.0, 0.0);
    }

    vec2 norm = vec2(-dir.y, dir.x);
    float idx = mod(cornerIndex, 4.0);
    float side = (mod(idx, 2.0) - 0.5) * 2.0;
    float tang;
    vec2 current;

    if (idx >= 2.0) {
        current = endPx;
        tang = 1.0;
        beamFrame.x = -beamSize;
    } else {
        current = startPx;
        tang = -1.0;
        beamFrame.x = len + beamSize;
    }

    beamFrame.y = side * beamSize;
    beamFrame.z = len;

    vec2 positionPx = current + (tang * dir + side * norm) * beamSize;
    vec2 clip = positionPx / viewportSize * 2.0 - 1.0;
    gl_Position = vec4(clip, 0.0, 1.0);
}
)GLSL";

const char* kBeamFragment = R"GLSL(
#version 150

#define EPS 1e-6
#define SQRT2 1.4142135623730951

uniform vec3 beamColor;
uniform float beamSize;
uniform float beamIntensity;

in vec3 beamFrame;

out vec4 fragColor;

float erfApprox(float x)
{
    float s = sign(x);
    float a = abs(x);
    float b = 1.0 + (0.278393 + (0.230389 + 0.078108 * a * a) * a) * a;
    b *= b;
    return s - s / (b * b);
}

void main()
{
    float len = beamFrame.z;
    float sigma = max(beamSize * 0.25, 0.001);
    float alpha;

    if (len < EPS) {
        alpha = exp(-dot(beamFrame.xy, beamFrame.xy) / (2.0 * sigma * sigma)) / max(2.0 * sqrt(beamSize), 1.0);
    } else {
        alpha = erfApprox(beamFrame.x / (SQRT2 * sigma)) - erfApprox((beamFrame.x - len) / (SQRT2 * sigma));
        alpha *= exp(-beamFrame.y * beamFrame.y / (2.0 * sigma * sigma)) * beamSize / (2.0 * len);
    }

    alpha = clamp(alpha * beamIntensity, 0.0, 1.0);
    fragColor = vec4(beamColor, alpha);
}
)GLSL";

const char* kScreenVertex = R"GLSL(
#version 150

in vec2 position;
in vec2 texcoord;

out vec2 uv;

void main()
{
    uv = texcoord;
    gl_Position = vec4(position, 0.0, 1.0);
}
)GLSL";

const char* kTextureFragment = R"GLSL(
#version 150

uniform sampler2D image;

in vec2 uv;

out vec4 fragColor;

void main()
{
    fragColor = texture(image, uv);
}
)GLSL";

const char* kDecayFragment = R"GLSL(
#version 150

uniform sampler2D image;
uniform vec3 backgroundColor;
uniform float persistence;
uniform float fastDecay;
uniform float afterglow;
uniform int decayStyle;

in vec2 uv;

out vec4 fragColor;

void main()
{
    vec3 src = texture(image, uv).rgb;
    vec3 signal = max(src - backgroundColor, vec3(0.0));

    if (decayStyle == 1) {
        float brightness = max(max(signal.r, signal.g), signal.b);
        float dimTail = 1.0 - smoothstep(0.015, 0.34, brightness);
        float softTail = 1.0 - smoothstep(0.18, 0.82, brightness);
        float brightDrain = brightness * mix(0.035, 0.24, fastDecay);
        float tailBoost = dimTail * mix(0.0, 0.055, afterglow) + softTail * afterglow * 0.012;
        float keep = clamp(persistence + tailBoost - brightDrain, 0.0, mix(0.982, 0.9975, afterglow));
        signal *= keep;
        signal = max(signal - vec3(mix(0.0009, 0.00018, afterglow)), vec3(0.0));
        signal = pow(signal, vec3(mix(1.035, 1.012, afterglow)));
    } else {
        signal *= persistence;
    }

    fragColor = vec4(backgroundColor + signal, 1.0);
}
)GLSL";

const char* kSolidVertex = R"GLSL(
#version 150

in vec2 position;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
}
)GLSL";

const char* kSolidFragment = R"GLSL(
#version 150

uniform vec4 fillColor;

out vec4 fragColor;

void main()
{
    fragColor = fillColor;
}
)GLSL";
}
