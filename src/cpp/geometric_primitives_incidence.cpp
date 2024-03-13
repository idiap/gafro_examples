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
    // create several random geometric primitives
    gafro::Sphere<double> sphere1 = gafro::Sphere<double>::Random();
    gafro::Sphere<double> sphere2 = gafro::Sphere<double>::Random();

    gafro::Plane<double> plane1 = gafro::Plane<double>::Random();
    gafro::Plane<double> plane2 = gafro::Plane<double>::Random();

    gafro::Line<double> line1 = gafro::Line<double>::Random();
    gafro::Line<double> line2 = gafro::Line<double>::Random();

    // compute the meet operator between geometric primitives
    auto sphere_sphere_meet = (sphere1.dual() ^ sphere2.dual()).evaluate().dual().evaluate();
    auto line_sphere_meet = (sphere1.dual() ^ line1.dual()).evaluate().dual().evaluate();
    auto line_plane_meet = (line1.dual() ^ plane1.dual()).evaluate().dual().evaluate();

    //
    std::cout << sphere_sphere_meet << std::endl;
    std::cout << line_sphere_meet << std::endl;
    std::cout << line_plane_meet << std::endl;

    return 0;
}