#include "app/standalone_app.hpp"

#include "app/preset_store.hpp"
#include "app/standalone_controls.hpp"
#include "platform/win32_gl_window.hpp"
#include "visual/frame_stats.hpp"
#include "visual/scope_engine.hpp"
#include "visual/signal_source.hpp"
#include "visual/test_signal.hpp"

#include <chrono>
#include <thread>

namespace prettyscope
{
int StandaloneApp::run()
{
    Win32GlWindow window("Prettyscope - OpenGL Trace", 1280, 720);
    ScopeEngine scope(1024);
    TestSignalGenerator generator;
    SignalSource& signalSource = generator;
    StandaloneControls controls;

    VisualParams& params = scope.params();
    PresetStore::loadDefault(params, generator);

    scope.initialize();

    auto previous = std::chrono::steady_clock::now();
    FrameStats frameStats;
    while (window.processMessages())
    {
        const auto now = std::chrono::steady_clock::now();
        const float dt = std::chrono::duration<float>(now - previous).count();
        previous = now;

        frameStats.advance(dt);
        params.fps = frameStats.fps();

        controls.update(window, params, generator);
        window.setTitle(controls.titleText(params, generator));

        const auto size = window.framebufferSize();
        scope.render(signalSource, dt, size.width, size.height);
        window.swapBuffers();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    scope.shutdown();
    return 0;
}
}
