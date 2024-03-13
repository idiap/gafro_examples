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

from pygafro import Motor
from pygafro import Point
from pygafro import Line
from pygafro import Plane


# create a random motor to transform the geometric primitives
motor = Motor.Random()

point = Point.Random()
line = Line.Random()
plane = Plane.Random()

# transform the geometric primitives
point_transformed = motor.apply(point)
line_transformed = motor.apply(line)
plane_transformed = motor.apply(plane)

# explicit use of the geometric product to transform primitives using a motor
point_transformed_alternative = motor * point * motor.reverse()
line_transformed_alternative = motor * line * motor.reverse()
plane_transformed_alternative = motor * plane * motor.reverse()

print("Point")
print(point)
print(point_transformed)
print(point_transformed_alternative)
print("---")
print("Line")
print(line)
print(line_transformed)
print(line_transformed_alternative)
print("---")
print("Plane")
print(plane)
print(plane_transformed)
print(plane_transformed_alternative)
