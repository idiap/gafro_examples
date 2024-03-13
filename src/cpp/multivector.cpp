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

using namespace gafro;

int main(int /*argc*/, char ** /*argv*/)
{
    Twist<double> twist = Twist<double>::Random();

    std::cout << twist << std::endl;
    std::cout << (twist | (E0123i<double>(1.0) * E0<double>(1.0))) << std::endl;
    std::cout << E0123i<double>(1.0) * E0<double>(1.0) << std::endl;

    // create a multivector that corresponds to the scalar part of the algebra
    Multivector<double, blades::scalar> scalar(2.0);

    // create a multivector corresponds to a Euclidean vector
    Multivector<double, blades::e1, blades::e2, blades::e3> vector({ 1.0, 2.0, 3.0 });

    // creates an expressions that are not evaluated yet
    auto expresion_geometric_product = scalar * vector;
    auto expression_sum = scalar + vector;

    // different ways to evalute the same expression
    Multivector<double, blades::e1, blades::e2, blades::e3> result_1 = scalar * vector;
    Multivector<double, blades::e1, blades::e2, blades::e3> result_2 = expresion_geometric_product;
    Multivector<double, blades::e1, blades::e2, blades::e3> result_3 = expresion_geometric_product.evaluate();
    // an expression will create a multivector with the necessary blades
    Multivector<double, blades::scalar, blades::e1, blades::e2, blades::e3> result_4 = expression_sum;
    Multivector<double, blades::scalar, blades::e1, blades::e2, blades::e3> result_5 = scalar * result_4;

    std::cout << result_1 << std::endl;
    std::cout << result_2 << std::endl;
    std::cout << result_3 << std::endl;
    std::cout << result_4 << std::endl;
    std::cout << result_5 << std::endl;

    return 0;
}