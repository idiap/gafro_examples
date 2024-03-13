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

from pygafro import FrankaEmikaRobot
import numpy as np


panda = FrankaEmikaRobot()

position = panda.getRandomConfiguration()
velocity = np.random.random((7,))
acceleration = np.random.random((7,))
torque = np.random.random((7,))

# forward kinematics: compute the motor at the end-effector
ee_motor = panda.getEEMotor(position)

print(ee_motor)
print()

# compute jacobians
ee_analytic_jacobian = panda.getEEAnalyticJacobian(position)
ee_geometric_jacobian = panda.getEEGeometricJacobian(position)

for i, v in enumerate(ee_analytic_jacobian):
    print(i, ':  ', v)
print()

for i, v in enumerate(ee_geometric_jacobian):
    print(i, ':  ',  v)
print()

# compute dynamics
acceleration_computed = panda.getJointAccelerations(position, velocity, torque)

torque_computed = panda.getJointTorques(position, velocity, acceleration)

print(acceleration_computed.transpose())
print(torque_computed.transpose())
