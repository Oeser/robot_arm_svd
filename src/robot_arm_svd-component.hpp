#ifndef OROCOS_ROBOTARMSVD_COMPONENT_HPP
#define OROCOS_ROBOTARMSVD_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <limits>
#include <string>
#include <rtt/Port.hpp>
#include <urdf/model.h>
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/chain.hpp>
#include <kdl/tree.hpp>
#include <kdl/frames.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainjnttojacsolver.hpp>

class RobotArmSVD : public RTT::TaskContext
{
public:
    RobotArmSVD(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
private:
    // properties for easy reuse of component
    std::string path_to_urdf,
                base_left_arm,
                ee_left_arm,
                base_right_arm,
                ee_right_arm;

    // some ports to get current joint states
    // TODO 3 or 1 input port?
    //RTT::InputPort<rstrt::robot::JointState> torso_state;
    //RTT::InputPort<rstrt::robot::JointState> left_arm_state;
    //RTT::InputPort<rstrt::robot::JointState> right_arm_state;
    // OR
    //RTT::InputPort<rstrt::robot::JointState> joint_state;

    bool loadModel(); // loads urdf specified by 'path_to_urdf'
    // 'global' vars
    bool model_loaded;
    urdf::Model model;
    KDL::Tree model_tree;
    KDL::Chain chain_left_arm,
               chain_right_arm;
    KDL::JntArray q_left,
                  q_right;
    KDL::Jacobian j_left,
                  j_right;
    std::unique_ptr<KDL::ChainJntToJacSolver> jnt_to_jac_solver_left,
                                              jnt_to_jac_solver_right;
    Eigen::MatrixXd u_left,
                    u_right,
                    v_left,
                    v_right,
                    sv_left,
                    sv_right;

    // some debug functions. just some printing/setting to evade a proper debugger
    void DEBUGprintSVD();
    void DEBUGprintSVDLeft();
    void DEBUGprintSVDRight();
    void DEBUGprintProperties();
    void DEBUGsetupFakeStates();
};
#endif
