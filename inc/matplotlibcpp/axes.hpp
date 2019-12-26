#pragma once

#include "util.hpp"

namespace matplotlibcpp
{

struct Axes
{
    explicit Axes(const py::object& self)
        : self{self},
          plot_{self.attr("plot")}, scatter_{self.attr("scatter")}, hist_{self.attr("hist")},
          hlines_{self.attr("hlines")}, vlines_{self.attr("vlines")}, annotate_{self.attr("annotate")},
          set_title_{self.attr("set_title")}, set_xlabel_{self.attr("set_xlabel")}, set_ylabel_{self.attr("set_ylabel")}
    {
    }

    template <class T, class... TKWArgs>
    void plot(const std::vector<T>& x, const std::vector<T>& y, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        plot_(*py::make_tuple(to_ndarray(x), to_ndarray(y)), **to_dict(kwargs...));
    }

    template <class T, class... TKWArgs>
    void plot(const std::vector<T>& x, const std::vector<T>& y, const char* fmt, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        plot_(*py::make_tuple(to_ndarray(x), to_ndarray(y), fmt), **to_dict(kwargs...));
    }

    template <class T, class... TKWArgs>
    void scatter(const std::vector<T>& x, const std::vector<T>& y, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        scatter_(*py::make_tuple(to_ndarray(x), to_ndarray(y)), **to_dict(kwargs...));
    }

    template <class T, class... TKWArgs>
    void hist(const std::vector<T>& x, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        hist_(to_ndarray(x), **to_dict(kwargs...));
    }

    template <class... TKWArgs>
    void hlines(double y, double xmin, double xmax, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        hlines_(*py::make_tuple(y, xmin, xmax), **to_dict(kwargs...));
    }

    template <class... TKWArgs>
    void vlines(double x, double ymin, double ymax, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        vlines_(*py::make_tuple(self, x, ymin, ymax), **to_dict(kwargs...));
    }

    template <class... TKWArgs>
    void arrow(double x0, double y0, double x1, double y1, const std::pair<const char*, TKWArgs>&... arrowprops)
    {
        annotate_(py::object(""),
            **to_dict(std::make_pair("xy", py::make_tuple(x1, y1)), std::make_pair("xytext", py::make_tuple(x0, y0)),
                std::make_pair("arrowprops", to_dict(arrowprops...))));
    }

    void arrow(double x0, double y0, double x1, double y1, const char* arrowstyle = "->")
    {
        annotate_(py::object(""),
            **to_dict(std::make_pair("xy", py::make_tuple(x1, y1)), std::make_pair("xytext", py::make_tuple(x0, y0)),
                std::make_pair("arrowprops",
                    to_dict(std::make_pair("arrowstyle", arrowstyle)))));
    }

    template <class... TKWArgs>
    void set_title(const std::string& title, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        set_title_(title.c_str(), **to_dict(kwargs...));
    }

    void set_xlabel(const std::string& label)
    {
        set_xlabel_(label.c_str());
    }

    void set_ylabel(const std::string& label)
    {
        set_ylabel_(label.c_str());
    }

private:
    using object = boost::python::object;
    object self;
    object plot_, scatter_, hist_, hlines_, vlines_, annotate_, set_title_, set_xlabel_, set_ylabel_;
};

}  // namespace matplotlibcpp