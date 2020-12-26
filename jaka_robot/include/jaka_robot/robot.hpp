//
// Created by dell on 2020/11/8.
//

#ifndef JAKA_ROBOT_ROBOT_HPP
#define JAKA_ROBOT_ROBOT_HPP

#include <JAKAZuRobot.h>
#include <string>
#include <ros/ros.h>

#include <QThread>
#include <mutex>
#include <atomic>
#include <thread>

#define ERR_INVALID_ACTION_NAME     -101        //无法打开文件

//class RobotBase : public QThread {
//Q_OBJECT
//protected:
//    std::mutex m_mutex;
//    std::atomic_bool m_isLogin;
//    std::atomic_bool m_isActionReady;
//    QString m_currentActionName;
//
//    JAKAZuRobot *m_robot;
//    RobotState m_robotState{};
//    RobotStatus m_robotStatus{};
//    CartesianPose m_cartesianPose{};
//
//
//    std::string m_ip;
//    int m_ajNum = 0;
//    MoveMode m_moveMode = INCR;
//    CoordType m_coordType = COORD_JOINT;
//    double m_velCmd = 0;
//    double m_posCmd = 0;
//    IOType m_ioType = IO_TOOL;
//    int m_ioIndex{};
//    BOOL m_ioValue{};
//
//Q_SIGNALS:
//
//    void actionStatus(QString info, int res);
//
//private:
//    void m_handleAction() {
//        errno_t res = ERR_INVALID_ACTION_NAME;
//        if (m_currentActionName == "log_out") {
//            res = m_robot->login_out();
//        } else if (m_currentActionName == "power_on")
//            res = m_robot->power_on();
//        else if (m_currentActionName == "power_off")
//            res = m_robot->power_off();
//        else if (m_currentActionName == "shut_down")
//            res = m_robot->shut_down();
//        else if (m_currentActionName == "enable_robot")
//            res = m_robot->enable_robot();
//        else if (m_currentActionName == "disable_robot")
//            res = m_robot->disable_robot();
//        else if (m_currentActionName == "jog")
//            res = m_robot->jog(m_ajNum, m_moveMode, m_coordType, m_velCmd, m_posCmd);
//        else if (m_currentActionName == "jog_stop")
//            res = m_robot->jog_stop(m_ajNum);
//        else if (m_currentActionName == "motion_abort")
//            res = m_robot->motion_abort();
//        else if (m_currentActionName == "collision_recover")
//            res = m_robot->collision_recover();
//        else if (m_currentActionName == "set_digital_output")
//            res = m_robot->set_digital_output(m_ioType, m_ioIndex, m_ioValue);
//        Q_EMIT actionStatus(m_currentActionName, res);
//    }
//
//public:
//
//    explicit RobotBase(QObject *parent = Q_NULLPTR) : QThread(parent), m_isLogin(false), m_isActionReady(false),
//                                                      m_robot(new JAKAZuRobot) {}
//
//    virtual void loginIn(const std::string &ip) {
//        m_ip = ip;
//    }
//
//    virtual void LogOut() {}
//
//    virtual void powerOn() {}
//
//    virtual void powerOff() {}
//
//    virtual void enableRobot() {}
//
//    virtual void disableRobot() {}
//
//
//    void run() override {
//        errno_t res;
//        if (!m_isLogin.load()) {
//            res = m_robot->login_in(m_ip.c_str());
//            if (res == ERR_SUCC) m_isLogin.exchange(true);
//            Q_EMIT actionStatus("login_in", res);
//        } else {
//            int counter = 0;
//            while (ros::ok() && !isInterruptionRequested()) {
//                if (m_isActionReady.load()) {
//                    m_isActionReady.exchange(false);
//                    m_handleAction();
//                }
//                if (counter % 50 == 1) {
//                    res = m_robot->get_robot_state(&m_robotState);
//                    m_robot->get_robot_status(&m_robotStatus);
//                    m_robot->get_tcp_position(&m_cartesianPose);
//                }
//
//                if (counter % 50 == 1)
//
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));  // ms
//            }
////            ROS_INFO("<Robot> quit thread.");
//        }
//    }
//
//
//    ~RobotBase() override {
//        if (isRunning()) {
//            requestInterruption();
//            wait();
//        }
//        delete m_robot;
//    }
//};

class RobotBase {
public:
    explicit RobotBase() = default;

    ~RobotBase() {

    }
};


class JAKARobot : public RobotBase {
private:
    JAKAZuRobot m_robot;

    bool handleError(errno_t error_code) {
        switch (error_code) {
            case ERR_INVALID_HANDLER:
                ROS_ERROR("[JAKA]无效的句柄");
                break;
            case ERR_INVALID_PARAMETER:
                ROS_ERROR("[JAKA]无效的参数");
                break;
            case ERR_COMMUNICATION_ERR:
                ROS_ERROR("[JAKA]tcp/ip通信错误");
                break;
            case ERR_KINE_INVERSE_ERR:
                ROS_ERROR("[JAKA]逆解失败");
                break;
            case ERR_EMERGENCY_PRESSED:
                ROS_ERROR("[JAKA]急停按钮按下");
                break;
            case ERR_NOT_POWERED:
                ROS_ERROR("[JAKA]没有上电");
                break;
            case ERR_NOT_ENABLED:
                ROS_ERROR("[JAKA]没有使能");
                break;
            case ERR_DISABLE_SERVOMODE:
                ROS_ERROR("[JAKA]没有进入servo模式");
                break;
            case ERR_NOT_OFF_ENABLE:
                ROS_ERROR("[JAKA]没有关闭机器人使能");
                break;
            case ERR_PROGRAM_IS_RUNNING:
                ROS_ERROR("[JAKA]作业程序正在运行");
                break;
            case ERR_CANNOT_OPEN_FILE:
                ROS_ERROR("[JAKA]无法打开文件");
                break;
            default:
                break;
        }
        return error_code == ERR_SUCC;
    }

public:
    bool init(std::string &ip) {
        return handleError(m_robot.login_in(ip.c_str())) &&
               handleError(m_robot.enable_robot()) &&
               handleError(m_robot.power_on());
    }



};

class VirtualRobot : public RobotBase {

};

#endif //JAKA_ROBOT_ROBOT_HPP
