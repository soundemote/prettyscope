#include "app/standalone_controls.hpp"
#include "app/preset_store.hpp"
#include "platform/win32_gl_window.hpp"
#include "visual/scope_renderer.hpp"
#include "visual/signal_buffer.hpp"
#include "visual/signal_source.hpp"
#include "visual/test_signal.hpp"
#include "visual/visual_params.hpp"

#include <chrono>
#include <exception>
#include <iostream>
#include <thread>

int main()
{
    try
    {
        prettyscope::Win32GlWindow window("Prettyscope - OpenGL Trace", 1280, 720);
        prettyscope::ScopeRenderer renderer;
        prettyscope::SignalBuffer signal(1024);
        prettyscope::TestSignalGenerator generator;
        prettyscope::SignalSource& signalSource = generator;
        prettyscope::StandaloneControls controls;

        prettyscope::VisualParams params;
        prettyscope::PresetStore::loadDefault(params, generator);

        renderer.initialize();

        auto previous = std::chrono::steady_clock::now();
        float smoothedFps = 60.0f;
        while (window.processMessages())
        {
            const auto now = std::chrono::steady_clock::now();
            const float dt = std::chrono::duration<float>(now - previous).count();
            previous = now;

            if (dt > 0.0f)
            {
                const float instantFps = 1.0f / dt;
                smoothedFps = smoothedFps * 0.92f + instantFps * 0.08f;
                params.fps = smoothedFps;
            }

            controls.update(window, params, generator);
            window.setTitle(controls.titleText(params, generator));

            signalSource.advance(signal, dt);

            const auto size = window.framebufferSize();
            renderer.render(signal, params, size.width, size.height);
            window.swapBuffers();

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Prettyscope failed: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
