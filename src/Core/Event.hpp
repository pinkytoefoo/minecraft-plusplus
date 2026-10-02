#pragma once

#include <cstdint>
#include <variant>

template<typename... Ts> struct Overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

enum class EventType : uint8_t
{
    Key,
    MouseMove,
    MouseClick,
    WindowResize
};

struct KeyEvent
{
    int key;
    int scancode;
    int action;
    int mods;
};


struct MouseMoveEvent
{
    double xpos;
    double ypos;
};

struct MouseClickEvent
{
    // implement
};

struct WindowResizeEvent
{
    int width;
    int height;
};


struct Event
{
    std::variant<
        KeyEvent,
        MouseMoveEvent, MouseClickEvent,
        WindowResizeEvent
    > Data;
};

