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
from pygafro import blades
from pygafro import Twist
from pygafro import E0123i, E0


# create a multivector that corresponds to the scalar part of the algebra
scalar = Multivector.create(['scalar'], 2.0)

# create a multivector that corresponds to a Euclidean vector
vector = Multivector.create(['e1', 'e2', 'e3'], [1.0, 2.0, 3.0])

# note: this is equivalent to:
#vector = Multivector.create([blades.e1, blades.e2, blades.e3], [1.0, 2.0, 3.0])

# expressions are immediately evaluated in Python (not the case in C++)
geometric_product = scalar * vector
sum = scalar + vector

print(geometric_product)
print(sum)

# Access individual blade values
e1 = vector['e1']   # equivalent to vector[blades.e1]
vector['e1'] = 4.0

print(vector)

# Other examples
twist = Twist.Random()

print(twist)
print(twist | (E0123i(1.0) * E0(1.0)))
print(E0123i(1.0) * E0(1.0))
