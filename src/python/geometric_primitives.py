#! /usr/bin/env python3

# Copyright (c) Idiap Research Institute, http://www.idiap.ch/
# Written by Philip Abbet <philip.abbet@idiap.ch>
# Based on the C++ version by Tobias Löw <https://tobiloew.ch>
#
# This file is part of gafro_examples.
#
# gafro is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# gafro is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with gafro. If not, see <http://www.gnu.org/licenses/>.

from pygafro import Multivector
from pygafro import Point
from pygafro import Line
from pygafro import Plane


# create different geometric primitives
p0 = Point()
p1 = Point(1.0, 0.0, 0.0)
p2 = Point(0.0, 1.0, 0.0)
p3 = Point(0.0, 0.0, 1.0)

ei = Multivector.create(['ei'], 1.0)

line = Line(p0, p1)
line_alternative = p0 ^ p1 ^ ei  # equivalent to line, but explicitly using the outer product (^)

plane = Plane(p1, p2, p3)
plane_alternative = p1 ^ p2 ^ p3 ^ ei # equivalent to plane

# print the values
print("p0", p0)
print("p1", p1)
print("p2", p2)
print("p3", p3)

print("---")
print("line            ", line)
print("line_alternative", line_alternative)

print("---")
print("plane            ", plane)
print("plane_alternative", plane_alternative)
