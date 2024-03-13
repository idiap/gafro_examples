/*
    Copyright (c) Idiap Research Institute, http://www.idiap.ch/
    Written by Tobias Löw <https://tobiloew.ch>

    This file is part of gafro_examples.

    gafro is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as
    published by the Free Software Foundation.

    gafro is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with gafro. If not, see <http://www.gnu.org/licenses/>.
*/

#include <gafro/gafro.hpp>

int main(int /*argc*/, char ** /*argv*/)
{
    // create different geometric primitives
    gafro::Point<double> p0;
    gafro::Point<double> p1(1.0, 0.0, 0.0);
    gafro::Point<double> p2(0.0, 1.0, 0.0);
    gafro::Point<double> p3(0.0, 0.0, 1.0);
    gafro::Point<double> p4(1.0, 1.0, 1.0);

    gafro::Line<double> line(p0, p1);
    gafro::Line<double> line_alternative = p0 ^ p1 ^ gafro::Ei<double>(1.0);  // equivalent to line, but explicitly using the outer product (^)

    gafro::Plane<double> plane(p1, p2, p3);
    gafro::Plane<double> plane_alternative = p1 ^ p2 ^ p3 ^ gafro::Ei<double>(1.0);  // equivalent to plane

    gafro::Sphere<double> sphere(p1, p2, p3, p4);
    gafro::Sphere<double> sphere_alternative = p1 ^ p2 ^ p3 ^ p4;  // equivalent to plane

    // print the values
    std::cout << "p0 " << p0 << std::endl;
    std::cout << "p1 " << p1 << std::endl;
    std::cout << "p2 " << p2 << std::endl;
    std::cout << "p3 " << p3 << std::endl;

    std::cout << "---" << std::endl;
    std::cout << "line " << line << std::endl;
    std::cout << "line_alternative " << line_alternative << std::endl;

    std::cout << "---" << std::endl;
    std::cout << "plane " << plane << std::endl;
    std::cout << "plane_alternative " << plane_alternative << std::endl;

    std::cout << "---" << std::endl;
    std::cout << "sphere " << sphere << std::endl;
    std::cout << "sphere_alternative " << sphere_alternative << std::endl;

    return 0;
}