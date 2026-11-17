#include "app/app.h"
#include "core/input.h"

namespace obi {
void DevPad(int port, input::Pad& p);  // devinput.cpp
}

// what the runtime asks of the game; strings must be set, hooks may stay null
const app::GameInfo app::kGame = {
    .title = L"Star Wars Obi-Wan",               // window and splash
    .short_title = L"Obi-Wan",               // message boxes
    .name = L"ObiWan",                      // window classes, crash dumps, handover event
    .log = "obiwan",                        // log file prefix
    .settings = "settings.toml",          // settings file beside the exe
    .splash = L"splash",                  // optional splash.png or splash.bmp beside the exe
    .missing = L"Put the game in the assets folder: its disc image (.iso), or default.xbe with its folders beside it.",
    .images = {{"default.xbe", "ObiWan"}},  // each recompiled xbe and its exe, for title launches
    .options = {},                        // game settings kept in the settings file
    .load = nullptr,                      // reads more from the settings file's toml::table
    .save = nullptr,                      // writes more into it
    .init = nullptr,                      // after the settings load, before the window and boot
    .loaded = nullptr,                    // image in memory, before its entry point runs
    .window = nullptr,                    // the game window is up
    .message = nullptr,                   // window messages first; true takes one
    .ui = nullptr,                        // ImGui drawing each frame
    .pad = obi::DevPad,                   // changes a polled pad (local test input)
    .rumble = nullptr,                    // changes a rumble before it is set
    // mouse and keyboard, rebound in the settings menu: the saber on the mouse buttons and wheel; the controller
    // layout is the game's configuration 1
    .keys = {{"up", "Move forward", "W"},
             {"down", "Move back", "S"},
             {"left", "Move left", "A"},
             {"right", "Move right", "D"},
             {"a", "Jump / Force jump", "Space, Enter"},
             {"b", "Use / Force push", "Q, Backspace"},
             {"x", "Crouch / Force pull", "C, Left Ctrl"},
             {"y", "Acrobatics / Force throw", "E"},
             {"lt", "Force (hold)", "Left Shift"},
             {"rt", "Lock-on", "Tab"},
             {"rs", "Lightsaber throw", "Middle Mouse"},
             {"rs_up", "Saber swipe up", "Scroll Up, I"},
             {"rs_down", "Saber block (swipe down)", "Scroll Down, K"},
             {"rs_left", "Saber swipe left", "Left Mouse, J"},
             {"rs_right", "Saber swipe right", "Right Mouse, L"},
             {"white", "Free look / Force view", "F"},
             {"black", "180 quick-turn", "R"},
             {"dpad_up", "Inventory up", "Up"},
             {"dpad_down", "Inventory down", "Down"},
             {"dpad_left", "Inventory left", "Left"},
             {"dpad_right", "Inventory right", "Right"},
             {"start", "Pause", "Esc"}},
    .version = "0.1.1",                   // the options menu header
    .tier = "alpha",                      // alpha, beta or complete
    .widescreen = false,                  // made for 4:3: widescreen through the toolkit's hack
};
