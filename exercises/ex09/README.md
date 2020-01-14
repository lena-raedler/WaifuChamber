# Exercise Sheet 8 — Outlook Ⅱ

*due on 21 January 2020*

## Task 1 (4 Points)

Implement a simple calculator using either [imgui], [Qt Widgets], or [Qt Quick].

[imgui]: https://github.com/ocornut/imgui
[Qt Widgets]: https://doc.qt.io/qt-5/qtwidgets-index.html
[Qt Quick]: https://doc.qt.io/qt-5/qtquick-index.html

For Qt Quick, the actual calculation needs to be implemented in C++ as we want to investigate the interaction between the GUI framework and the C++ programming language.

## Task 2 (4 Points)

Your are given the following definition of a struct (+ used enum):

```cpp
enum class Fullscreen { Fullscreen, Borderless, Window };

struct Config {
    int width = 1920;
    int height = 1080;
    double effectVolume = 1.0;
    double musicVolume = 0.3;
    bool headless = false;
    Fullscreen fullscreen = Fullscreen::Window;
};
```

Find a way to **easily** serialise and de-serialise instances of this struct so it can be easily stored and loaded to/from disk.
The serialisation and de-serialisation logic should be derived from the struct definition.
If I change the definition, I should not have to update the corresponding logic manually.

I presented a way of using [X Macros](https://en.wikipedia.org/wiki/X_Macro) for this in the recap slides.
But there are also libraries and frameworks available for C++ that can be used instead.

If your solution requires files to be generated at build time, provide a CMake snippet illustrating how this can be implemented.

## Shameless Plug

[Raygun] is a simplistic game engine built around [NVIDIA Vulkan Ray Tracing], implemented in C++.

The first official version has been released and is available under the [MIT license].
At this moment, Windows is the only supported platform, but Linux support is on the way.

[Raygun]: https://github.com/W4RH4WK/Raygun
[NVIDIA Vulkan Ray Tracing]: https://devblogs.nvidia.com/vulkan-raytracing/
[MIT license]: https://opensource.org/licenses/MIT
