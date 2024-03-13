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

    gafro::Line<double> line(gafro::Point<double>(), gafro::Point<double>(0.0, 1.0, 0.0));
    gafro::Point<double> ee_target_point = panda.getEEMotor(panda.getRandomConfiguration()).apply(gafro::Point<double>());

    gafro::SingleManipulatorTarget<double, 7, gafro::Line, gafro::Point> cost_function(&panda, line, ee_target_point);

    Eigen::Vector<double, 7> x = panda.getRandomConfiguration();

    double cost = cost_function.getError(x).squaredNorm();

    // Gauss-Newton algorithm to find the inverse kinematics
    int i = 0;
    for (; i < 100; ++i)
    {
        Eigen::Vector<double, 7> gradient;
        Eigen::Matrix<double, 7, 7> hessian;

        cost_function.getGradientAndHessian(x, gradient, hessian);

        Eigen::Vector<double, 7> update = -((hessian + 1e-5 * Eigen::Matrix<double, 7, 7>::Identity()).inverse() * gradient);

        // line search
        {
            int iter = 0;

            double c = cost;

            double alpha = 2.0;

            while (c >= cost && ++iter < 20)
            {
                alpha *= 0.5;
                Eigen::Matrix<double, 7, 1> xk = x + alpha * update;

                c = cost_function.getError(xk).squaredNorm();
            }

            update = alpha * update;
        }

        if (update.squaredNorm() < 1e-10 || update.hasNaN())
        {
            break;
        }

        x = x + update;

        if (x.hasNaN())
        {
            break;
        }

        cost = cost_function.getError(x).squaredNorm();

        std::cout << "iteration: " << i << " -> "             //
                  << "cost: " << cost << ", "                 //
                  << "update norm: " << update.squaredNorm()  //
                  << std::endl;

        if (cost < 1e-10)
        {
            break;
        }
    }

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Target Point: " << ee_target_point << std::endl;
    std::cout << "Solution Line: " << panda.getEEMotor(x).apply(line) << std::endl;
}