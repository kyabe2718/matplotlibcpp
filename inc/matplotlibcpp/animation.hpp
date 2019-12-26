#pragma once

#include "util.hpp"

namespace matplotlibcpp::animation
{

struct FuncAnimation
{
    template <class... TKWArgs>
    FuncAnimation(const Figure& fig, void (*plotter)(py::object), const std::pair<const char*, TKWArgs>&... kwargs)
        : self{
            py::import("matplotlib.animation")
                .attr("FuncAnimation")(
                    *py::make_tuple(fig.self, py::make_function(static_cast<void (*)(py::object)>(plotter))), **to_dict(kwargs...))}
    {
    }

    py::object self;
};

}  // namespace matplotlibcpp::animation