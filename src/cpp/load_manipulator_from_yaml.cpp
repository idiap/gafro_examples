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
#include <gafro_robot_descriptions/serialization/FilePath.hpp>
#include <gafro_robot_descriptions/serialization/SystemSerialization.hpp>

using namespace gafro;

int main(int /*argc*/, char ** /*argv*/) {
  // This example creates a manipulator with four links and three joints.

  Manipulator<double, 7> manipulator(
      std::move(
          SystemSerialization(FilePath("robots/panda/panda.yaml")).load()),
      "panda_endeffector_joint");

  auto position = manipulator.getRandomConfiguration();

  Motor<double> motor = manipulator.getEEMotor(position);

  MultivectorMatrix<double, Motor, 1, 7> analytic_jacobian =
      manipulator.getEEAnalyticJacobian(position);
  MultivectorMatrix<double, MotorGenerator, 1, 7> geometric_jacobian =
      manipulator.getEEGeometricJacobian(position);
  MultivectorMatrix<double, MotorGenerator, 1, 7> frame_jacobian =
      manipulator.getEEFrameJacobian(position);

  return 0;
}