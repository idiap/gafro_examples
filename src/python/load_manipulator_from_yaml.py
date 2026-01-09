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

from pygafro import createManipulator
from pygafro import __path__ as pygafro_path
import os


# Only necessary to retrieve YAML files supplied with pygafro, otherwise
# just use the path to the file directly
filename = os.path.join(pygafro_path[0], "assets/robots/panda/panda.yaml")

# Create a manipulator from a YAML file
manipulator = createManipulator(filename, 7, "panda_endeffector_joint")

# Use it
position = manipulator.getRandomConfiguration()

ee_motor = manipulator.getEEMotor(position)
ee_analytic_jacobian = manipulator.getEEAnalyticJacobian(position)
ee_geometric_jacobian = manipulator.getEEGeometricJacobian(position)
ee_frame_jacobian = manipulator.getEEFrameJacobian(position)
