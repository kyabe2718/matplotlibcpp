#pragma once

#include "util.hpp"

namespace matplotlibcpp
{

struct pyplot
{
    using object = boost::python::object;

    template <class T = double, class... TKWArgs>
    static void plot(const std::vector<T>& x, const std::vector<T>& y, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        plot_(*py::make_tuple(to_ndarray(x), to_ndarray(y)), **to_dict(kwargs...));
    }

    template <class T = double, class... TKWArgs>
    static void plot(const std::vector<T>& x, const std::vector<T>& y, const char* fmt, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        plot_(*py::make_tuple(to_ndarray(x), to_ndarray(y), fmt), **to_dict(kwargs...));
    }

    template <class... TKWArgs>
    static void arrow(double x0, double y0, double x1, double y1, const std::pair<const char*, TKWArgs>&... arrowprops)
    {
        annotate_(*py::make_tuple(py::object("")),
            **to_dict(std::make_pair("xy", py::make_tuple(x1, y1)),
                std::make_pair("xytext", py::make_tuple(x0, y0)),
                std::make_pair("arrowprops", to_dict(arrowprops...))));
    }

    static void arrow(double x0, double y0, double x1, double y1, const char* arrowstyle = "->")
    {
        annotate_(*py::make_tuple(py::object("")),
            **to_dict(std::make_pair("xy", py::make_tuple(x1, y1)),
                std::make_pair("xytext", py::make_tuple(x0, y0)),
                std::make_pair("arrowprops",
                    to_dict(std::make_pair("arrowstyle", arrowstyle)))));
    }

    template <class T, class... TKWArgs>
    static void scatter(const std::vector<T>& x, const std::vector<T>& y, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        scatter_(*py::make_tuple(to_ndarray(x), to_ndarray(y)), **to_dict(kwargs...));
    }

    template <class T, class... TKWArgs>
    static void hist(const std::vector<T>& x, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        hist_(*py::make_tuple(to_ndarray(x)), **to_dict(kwargs...));
    }

    template <class... TKWArgs>
    static void title(const std::string& title, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        title_(*py::make_tuple(title.c_str()), **to_dict(kwargs...));
    }

    static void xlim(double left, double right)
    {
        xlim_(left, right);
    }

    static void ylim(double bottom, double top)
    {
        ylim_(bottom, top);
    }

    static void xlabel(const std::string& label)
    {
        xlabel_(label.c_str());
    }

    static void ylabel(const std::string& label)
    {
        ylabel_(label.c_str());
    }

    template <class... TKWArgs>
    static void hlines(double y, double xmin, double xmax, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        hlines_(*py::make_tuple(y, xmin, xmax), **to_dict(kwargs...));
    }

    template <class... TKWArgs>
    static void vlines(double x, double ymin, double ymax, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        vlines_(*py::make_tuple(x, ymin, ymax), **to_dict(kwargs...));
    }

    template <class... TKWArgs>
    static void subplot(int nrows, int ncols, int index, const std::pair<const char*, TKWArgs>&... kwargs)
    {
        subplot_(*py::make_tuple(nrows, ncols, index), **to_dict(kwargs...));
    }

    static void show() { show_(); }
    static void legend() { legend_(); }
    static void tight_layout() { tight_layout_(); }
    static void savefig(const char* path) { savefig_(path); }
    static void cla() { cla_(); }

    static Figure figure()
    {
        return Figure{figure_()};
    }

private:
    inline static object plot_, scatter_, hist_, annotate_, title_;
    inline static object xlim_, ylim_, xlabel_, ylabel_;
    inline static object hlines_, vlines_;
    inline static object subplot_, show_, legend_, tight_layout_;
    inline static object figure_, savefig_, cla_;

public:
    pyplot()
    {
        if (!Py_IsInitialized()) {
            Py_Initialize();
            np::initialize();
        }
        auto dict = py::dict{py::import("matplotlib.pyplot").attr("__dict__")};
        plot_ = dict["plot"];
        scatter_ = dict["scatter"];
        hist_ = dict["hist"];
        annotate_ = dict["annotate"];
        title_ = dict["title"];
        xlim_ = dict["xlim"];
        ylim_ = dict["ylim"];
        xlabel_ = dict["xlabel"];
        ylabel_ = dict["ylabel"];
        hlines_ = dict["hlines"];
        vlines_ = dict["vlines"];
        subplot_ = dict["subplot"];
        show_ = dict["show"];
        legend_ = dict["legend"];
        tight_layout_ = dict["tight_layout"];
        figure_ = dict["figure"];
        savefig_ = dict["savefig"];
        cla_ = dict["cla"];
    }
};


inline auto plt = matplotlibcpp::pyplot{};
}  // namespace matplotlibcpp
