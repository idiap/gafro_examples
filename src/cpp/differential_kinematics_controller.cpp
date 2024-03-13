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
    // create robot
    gafro::FrankaEmikaRobot<double> panda;

    gafro::Line<double> reference_line = gafro::Line<double>::Z();
    gafro::Line<double> target_line = panda.getEEMotor(panda.getRandomConfiguration()).apply(gafro::Line<double>::Z());

    Eigen::Vector<double, 7> q = panda.getRandomConfiguration();

    for (int i = 0; i < 5000; ++i)
    {
        Eigen::Matrix<double, 6, 7> jacobian = panda.getEEFrameJacobian(q).embed();
        Eigen::Matrix<double, 7, 6> inverse_jacobian =
          (jacobian.transpose() * jacobian + 1e-5 * Eigen::Matrix<double, 7, 7>::Identity()).inverse() * jacobian.transpose();

        gafro::Motor<double> ee_motor = panda.getEEMotor(q).reverse();

        gafro::Line<double> transformed_target_line = ee_motor.apply(target_line);

        gafro::Twist<double> twist = transformed_target_line.getMotor(reference_line).log();

        Eigen::Vector<double, 7> qdot = -inverse_jacobian * twist.vector();

        qdot = qdot.array().min(0.1).max(-0.1);

        q += 0.01 * qdot;

        std::cout << "----" << std::endl;
        std::cout << q.transpose() << std::endl;
        std::cout << twist << std::endl;
    }
}