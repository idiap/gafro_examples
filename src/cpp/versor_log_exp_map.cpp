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

#include <gafro/algebra.hpp>

using namespace gafro;

int main(int /*argc*/, char ** /*argv*/)
{
    Motor<double> motor_1 = Motor<double>::Random();

    // this is an expression for the motor logarithm
    Motor<double>::Logarithm motor_log = motor_1.log();
    // it will evaluate to a motor generator
    Motor<double>::Generator motor_gen = motor_log;

    // both can be used to obtain a motor via the exponential
    Motor<double> motor_2 = Motor<double>::exp(motor_log);
    Motor<double> motor_3 = Motor<double>::exp(motor_gen);

    // the parts of different parts of a motor generator correspond to translation and rotation
    Rotor<double>::Generator rotor_gen(motor_gen.vector().topRows(3));
    Translator<double>::Generator translator_gen(motor_gen.vector().bottomRows(3));

    Rotor<double> rotor = Rotor<double>::exp(rotor_gen);
    Translator<double> translator = Translator<double>::exp(translator_gen);

    Motor<double> motor_4 = translator * rotor;

    std::cout << motor_1 << std::endl;
    std::cout << motor_2 << std::endl;
    std::cout << motor_3 << std::endl;
    std::cout << motor_4 << std::endl;

    return 0;
}