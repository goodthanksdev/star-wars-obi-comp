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
    .version = "0.1.0",                   // the options menu header
    .tier = "alpha",                      // alpha, beta or complete
};
