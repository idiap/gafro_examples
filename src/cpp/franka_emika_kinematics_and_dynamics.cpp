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
#include <gafro_robot_descriptions/FrankaEmikaRobot.hpp>

int main(int /*argc*/, char ** /*argv*/)
{
    gafro::FrankaEmikaRobot<double> panda;

    Eigen::Matrix<double, 7, 1> position = panda.getRandomConfiguration();
    Eigen::Matrix<double, 7, 1> velocity = Eigen::Matrix<double, 7, 1>::Random();
    Eigen::Matrix<double, 7, 1> acceleration = Eigen::Matrix<double, 7, 1>::Random();
    Eigen::Matrix<double, 7, 1> torque = Eigen::Matrix<double, 7, 1>::Random();

    // forward kinematics: compute the motor at the end-effector
    gafro::Motor<double> ee_motor = panda.getEEMotor(position);

    std::cout << ee_motor << std::endl;

    // compute jacobians
    auto ee_analytic_jacobian = panda.getEEAnalyticJacobian(position);
    auto ee_geometric_jacobian = panda.getEEGeometricJacobian(position);

    std::cout << ee_analytic_jacobian << std::endl;
    std::cout << ee_geometric_jacobian << std::endl;

    // compute dynamics
    Eigen::Matrix<double, 7, 1> acceleration_computed = panda.getJointAccelerations(position, velocity, torque);

    Eigen::Matrix<double, 7, 1> torque_computed = panda.getJointTorques(position, velocity, acceleration);

    std::cout << acceleration_computed.transpose() << std::endl;

    std::cout << torque_computed.transpose() << std::endl;

    return 0;
}
