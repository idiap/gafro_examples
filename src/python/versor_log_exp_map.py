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
from pygafro import Rotor
from pygafro import RotorGenerator
from pygafro import Translator
from pygafro import TranslatorGenerator


motor_1 = Motor.Random()

# this is an expression for the motor logarithm
motor_log = motor_1.log()

# it will evaluate to a motor generator
motor_gen = motor_log.evaluate()

# the generator can be used to obtain a motor via the exponential
motor_2 = Motor.exp(motor_gen).evaluate()

# the different parts of a motor generator correspond to translation and rotation
rotor_gen = RotorGenerator(motor_gen.vector()[:3])
translator_gen = TranslatorGenerator(motor_gen.vector()[3:])

rotor = Rotor.exp(rotor_gen)
translator = Translator.exp(translator_gen)

motor_3 = Motor(translator * rotor)
motor_4 = Motor(translator, rotor)

print(motor_1)
print(motor_2)
print(motor_3)
print(motor_4)
