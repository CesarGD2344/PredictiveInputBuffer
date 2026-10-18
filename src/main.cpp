
#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

namespace {
    struct Stage {
        int allTicks;
        int waveTicks;
        bool enabled;
    };

    constexpr Stage stages[] = {
        {2, 2, true},
        {4, 4, true},
        {8, 8, true},
        {16, 8, true},
        {0, 0, false}
    };

    int currentStage = 0;

    void logStage() {
        auto const& stage = stages[currentStage];

        if (!stage.enabled) {
            log::info("[InputBuffer] Stage 5: OFF (100% Raw Input)");
            return;
        }

        log::info(
            "[InputBuffer] Stage {}: {} Ticks All | {} Ticks Wave",
            currentStage + 1,
            stage.allTicks,
            stage.waveTicks
        );
    }

    void nextStage() {
        currentStage = (currentStage + 1) % 5;
        logStage();
    }
}

class $modify(PredictiveInputBufferKeyboard, CCKeyboardDispatcher) {
    void dispatchKeyboardMSG(
        enumKeyCodes key,
        bool isKeyDown,
        bool isKeyRepeat,
        double timestamp
    ) {
        if (key == enumKeyCodes::KEY_F6 && isKeyDown && !isKeyRepeat) {
            nextStage();
        }

        CCKeyboardDispatcher::dispatchKeyboardMSG(
            key, isKeyDown, isKeyRepeat, timestamp
        );
    }
};

$on_mod(Loaded) {
    log::info("[InputBuffer] Prototype loaded. Press F6 to cycle stages.");
    logStage();
}
