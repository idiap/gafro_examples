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
from pygafro import SingleManipulatorMotorCost
import numpy as np

# Create the robot
panda = FrankaEmikaRobot()

# Create the cost function
ee_target_motor = panda.getEEMotor(panda.getRandomConfiguration())

cost_function = SingleManipulatorMotorCost(panda, ee_target_motor)

# Gauss-Newton algorithm to find the inverse kinematics
x = panda.getRandomConfiguration()
cost = np.linalg.norm(cost_function.getError(x))

for i in range(100):
    gradient, hessian = cost_function.getGradientAndHessian(x)

    update = -(np.linalg.inv(hessian) @ gradient)

    # line search
    iter = 1
    c = cost
    alpha = 2.0

    while (c >= cost) and (iter < 20):
        alpha *= 0.5
        xk = x + alpha * update
        c = np.linalg.norm(cost_function.getError(xk))
        iter += 1

    update = alpha * update


    if (np.linalg.norm(update) < 1e-10) or np.isnan(update).any():
        break

    x = x + update

    if np.isnan(x).any():
        break

    cost = np.linalg.norm(cost_function.getError(x))

    print(f"iteration: {i} -> cost: {cost}, update norm: {np.linalg.norm(update)}")

    if cost < 1e-10:
        break


print("------------------------------------------------------")
print(f"Target Motor:   {ee_target_motor}")
print(f"Solution Motor: {panda.getEEMotor(x)}")
