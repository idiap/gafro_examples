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
    // This example creates a manipulator with four links and three joints.

    Translator<double> com(Translator<double>::Generator({ 0.0, 0.0, 0.0 }));

    std::unique_ptr<Link<double>> link1 = std::make_unique<Link<double>>();
    link1->setName("link1");
    link1->setMass(0.1);
    link1->setCenterOfMass(com);
    link1->setInertia(Inertia<double>(0.1, Eigen::Matrix<double, 3, 3>::Identity()));
    link1->setAxis(Motor<double>::Generator({ 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 }));

    std::unique_ptr<Link<double>> link2 = std::make_unique<Link<double>>();
    link2->setName("link2");
    link2->setMass(0.1);
    link2->setCenterOfMass(com);
    link2->setInertia(Inertia<double>(0.1, Eigen::Matrix<double, 3, 3>::Identity()));
    link2->setAxis(Motor<double>::Generator({ 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 }));

    std::unique_ptr<Link<double>> link3 = std::make_unique<Link<double>>();
    link3->setName("link3");
    link3->setMass(0.1);
    link3->setCenterOfMass(com);
    link3->setInertia(Inertia<double>(0.1, Eigen::Matrix<double, 3, 3>::Identity()));
    link3->setAxis(Motor<double>::Generator({ 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 }));

    std::unique_ptr<Link<double>> link4 = std::make_unique<Link<double>>();
    link4->setName("link4");
    link4->setMass(0.1);
    link4->setCenterOfMass(com);
    link4->setInertia(Inertia<double>(0.1, Eigen::Matrix<double, 3, 3>::Identity()));
    link4->setAxis(Motor<double>::Generator({ 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 }));

    // Create some joints
    Translator<double> t(Translator<double>::Generator({ 0.0, 1.0, 0.0 }));

    std::unique_ptr<RevoluteJoint<double>> joint1 = std::make_unique<RevoluteJoint<double>>();
    joint1->setName("joint1");
    joint1->setAxis(RevoluteJoint<double>::Axis({ 0.0, 0.0, 1.0 }));
    joint1->setLimits(Joint<double>::Limits({ -0.5, 0.5, 1.0, 1.0 }));

    joint1->setFrame(Motor<double>(t));

    std::unique_ptr<RevoluteJoint<double>> joint2 = std::make_unique<RevoluteJoint<double>>();
    joint2->setName("joint2");
    joint2->setAxis(RevoluteJoint<double>::Axis({ 0.0, 0.0, 1.0 }));
    joint2->setLimits(Joint<double>::Limits({ -0.8, 0.8, 1.0, 1.0 }));
    joint2->setFrame(Motor<double>(t));

    std::unique_ptr<RevoluteJoint<double>> joint3 = std::make_unique<RevoluteJoint<double>>();
    joint3->setName("joint3");
    joint3->setAxis(RevoluteJoint<double>::Axis({ 0.0, 0.0, 1.0 }));
    joint3->setLimits(Joint<double>::Limits({ -0.8, 0.8, 1.0, 1.0 }));
    joint3->setFrame(Motor<double>(t));

    // Create the system
    System<double> system;

    joint1->setParentLink(link1.get());
    link1->addChildJoint(joint1.get());

    joint1->setChildLink(link2.get());
    link2->setParentJoint(joint1.get());

    joint2->setParentLink(link2.get());
    link2->addChildJoint(joint2.get());

    joint2->setChildLink(link3.get());
    link3->setParentJoint(joint2.get());

    joint3->setParentLink(link3.get());
    link3->addChildJoint(joint3.get());

    joint3->setChildLink(link4.get());
    link4->setParentJoint(joint3.get());

    system.addLink(std::move(link1));
    system.addLink(std::move(link2));
    system.addLink(std::move(link3));
    system.addLink(std::move(link4));

    system.addJoint(std::move(joint1));
    system.addJoint(std::move(joint2));
    system.addJoint(std::move(joint3));

    system.finalize();

    Manipulator<double, 3> manipulator(std::move(system), "joint3");

    auto position = manipulator.getRandomConfiguration();

    Motor<double> motor = manipulator.getEEMotor(position);

    MultivectorMatrix<double, Motor, 1, 3> analytic_jacobian = manipulator.getEEAnalyticJacobian(position);
    MultivectorMatrix<double, MotorGenerator, 1, 3> geometric_jacobian = manipulator.getEEGeometricJacobian(position);
    MultivectorMatrix<double, MotorGenerator, 1, 3> frame_jacobian = manipulator.getEEFrameJacobian(position);

    return 0;
}