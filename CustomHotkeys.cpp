#include "CustomHotkeys.h"

static std::vector<CustomHotkey> customHotkeys =
{
    {"console", SDLKey::SDLK_l, 1, -1},
    {"speed", SDLKey::SDLK_BACKQUOTE, 1, -1},
    {"info", SDLKey::SDLK_LALT, 1, -1},
    {"temporal", SDLKey::SDLK_LALT, 3, 0},
    {"un_temporal", SDLKey::SDLK_LALT, 3, 9},
    {"temporal_speed", SDLKey::SDLK_LALT, 1, -1},
    {"temporal_slow", SDLKey::SDLK_LALT, 1, -1},
};

HOOK_METHOD(ControlsScreen, OnInit, () -> void)
{
    super();

    for (int i = 0; i < 4; i++)
    {
        auto vec = this->buttons[i];
        vec[0].rect.x = 0;

        printf("%08X %08X %08X\n", &(vec[0]), vec[0].rect.x, this);
    }
}


HOOK_STATIC(Settings, ResetHotkeys, () -> void)
{
    super();

    SettingValues* settings = G_->GetSettings();

    int c = 0;

    for (auto i : settings->hotkeys[1])
    {
        printf("%d %s\n", c, i.name.c_str());
        c++;
    }

    for (auto i : customHotkeys)
    {
        HotkeyDesc hk = HotkeyDesc();
        hk.name = i.hotkeyName;
        hk.key = i.defaultValue;

        if (i.index == -1)
        {
            settings->hotkeys[i.page].push_back(hk);
        }
        else
        {
            settings->hotkeys[i.page].insert(settings->hotkeys[i.page].begin() + i.index, hk);
        }
    }
}
