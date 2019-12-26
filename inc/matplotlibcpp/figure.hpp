#pragma once

#include "util.hpp"
#include "axes.hpp"

namespace matplotlibcpp
{

struct Figure
{
    using object = boost::python::object;

    explicit Figure(const py::object& self)
        : self{self},
          add_axes_{self.attr("add_axes")},
          add_subplot_{self.attr("add_subplot")},
          legend{self.attr("legend")},
          tight_layout{self.attr("tight_layout")},
          clf{self.attr("clf")}
    {
    }

    Axes add_axes(double l, double b, double w, double h)
    {
        auto axes = add_axes_(*py::make_tuple(l, b, w, h));
        return Axes{axes};
    }

    Axes add_subplot(int nrows, int ncols, int index)
    {
        auto axes = add_subplot_(*py::make_tuple(nrows, ncols, index));
        return Axes{axes};
    }

    object self;

    // callable
    object legend;
    object tight_layout;
    object clf;

private:
    object add_axes_, add_subplot_;
};
}  // namespace matplotlibcpp
