#include <random>
#include <iostream>

#include "matplotlibcpp.hpp"

int main()
{
    using matplotlibcpp::plt;

    {
        std::vector<double> x, y;
        for (double e = -3; e < 3; e += 0.1) {
            x.push_back(e);
            y.push_back(std::sin(e));
        }
        plt.plot(x, y);
        plt.show();
    }

    {
        std::vector<double> x, y;
        srand(0);
        for (double e = -3; e < 3; e += 0.1) {
            double e2 = e + 30 * (double)rand() / RAND_MAX;
            x.push_back(e2);
            y.push_back(std::sin(e2));
        }
        plt.plot(x, y, "ro");
        plt.show();
    }

    {
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
        std::normal_distribution<> dist(0, 1);
        std::vector<double> x;
        for (int i = 0; i < 1000; ++i) {
            x.push_back(dist(engine));
        }
        plt.hist(x);
        plt.show();
    }

    {
        std::vector<double> x, y;
        for (double e = 0; e < 10; e += 0.1) {
            x.push_back(e);
            y.push_back(std::exp(e));
        }
        plt.plot(x, y);
        plt.title("exponential function: $ y = e^x $");
        plt.ylim(0, 5000);
        plt.show();
    }

    {
        double xmin = -3.14159265;
        double xmax = 3.14159265;
        std::vector<double> x, y_sin, y_cos;
        for (double e = xmin; e < xmax; e += 0.1) {
            x.push_back(e);
            y_sin.push_back(std::sin(e));
            y_cos.push_back(std::cos(e));
        }
        plt.plot(x, y_sin);
        plt.plot(x, y_cos);
        plt.hlines(-1, xmin, xmax, std::make_pair("linestyles", "dashed"));
        plt.hlines(1, xmin, xmax, std::make_pair("linestyles", "dashed"));
        plt.title("$\\sin(x)$ and $\\cos(x)$");
        plt.xlim(xmin, xmax);
        plt.ylim(-1.3, 1.3);

        plt.show();
    }

    {
        double xmin = -3.14159265;
        double xmax = 3.14159265;
        std::vector<double> x, y_sin, y_cos;
        for (double e = xmin; e < xmax; e += 0.1) {
            x.push_back(e);
            y_sin.push_back(std::sin(e));
            y_cos.push_back(std::cos(e));
        }

        plt.subplot(2, 1, 1);
        plt.plot(x, y_sin);
        plt.title("$\\sin(x)$");
        plt.xlim(xmin, xmax);
        plt.ylim(-1.3, 1.3);

        plt.subplot(2, 1, 2);
        plt.plot(x, y_cos);
        plt.title("$\\cos(x)$");
        plt.xlim(xmin, xmax);
        plt.ylim(-1.3, 1.3);
        plt.tight_layout();

        plt.show();
    }

    {
        double xmin = -3.14159265;
        double xmax = 3.14159265;
        std::vector<double> x, y_sin, y_cos;
        for (double e = xmin; e < xmax; e += 0.1) {
            x.push_back(e);
            y_sin.push_back(std::sin(e));
            y_cos.push_back(std::cos(e));
        }
        plt.plot(x, y_sin, std::make_pair("label", "sin"));
        plt.plot(x, y_cos, std::make_pair("label", "cos"));
        plt.legend();

        plt.show();
    }

    {
        plt.arrow(0, 0, 0.5, 0.5);
        plt.show();
    }

    {
        namespace py = boost::python;
        auto fig = plt.figure();

        auto ax = fig.add_subplot(2, 1, 1);
        double xmin = -3.14159265;
        double xmax = 3.14159265;
        std::vector<double> x, y_sin, y_cos;
        for (double e = xmin; e < xmax; e += 0.1) {
            x.push_back(e);
            y_sin.push_back(std::sin(e));
            y_cos.push_back(std::cos(e));
        }
        ax.plot(x, y_sin, std::make_pair("label", "sin"));
        fig.legend();
        plt.show();
    }

    {
        auto fig = plt.figure();

        auto plot = [](auto) {
            plt.cla();

            double xmin = -3.14159265;
            double xmax = 3.14159265;
            static double th0 = 0;
            std::vector<double> x, y_sin;
            for (double e = xmin; e < xmax; e += 0.1) {
                x.push_back(e);
                y_sin.push_back(std::sin(e + th0));
            }

            plt.plot(x, y_sin);
            th0 += 0.1;
        };

        namespace py = boost::python;
        auto ani = matplotlibcpp::animation::FuncAnimation(fig, plot);
        plt.show();
    }
}
