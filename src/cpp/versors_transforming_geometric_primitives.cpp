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

#include <gafro/algebra.hpp>

using namespace gafro;

int main(int /*argc*/, char ** /*argv*/)
{
    // create a random motor to transform the geometric primitives
    Motor<double> motor = Motor<double>::Random();

    Point<double> point = Point<double>::Random();
    Line<double> line = Line<double>::Random();
    Plane<double> plane = Plane<double>::Random();

    // transform the geometric primitives
    Point<double> point_transformed = motor.apply(point);
    Line<double> line_transformed = motor.apply(line);
    Plane<double> plane_transformed = motor.apply(plane);

    // explicit use of the geometric product to transform a point using a motor
    Point<double> point_transformed_alternative = motor * point * motor.reverse();
    Line<double> line_transformed_alternative = motor * line * motor.reverse();
    Plane<double> plane_transformed_alternative = motor * plane * motor.reverse();

    std::cout << "Point" << std::endl;
    std::cout << point << std::endl;
    std::cout << point_transformed << std::endl;
    std::cout << point_transformed_alternative << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "Line" << std::endl;
    std::cout << line << std::endl;
    std::cout << line_transformed << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "Plane" << std::endl;
    std::cout << plane << std::endl;
    std::cout << plane_transformed << std::endl;

    return 0;
}