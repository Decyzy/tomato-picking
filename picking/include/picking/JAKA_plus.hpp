//
// Created by dell on 2020/11/5.
//

#ifndef PICKING_JAKA_PLUS_HPP
#define PICKING_JAKA_PLUS_HPP


#include <QThread>
#include <QDebug>

#include <functional>
#include <QMessageBox>
#include <atomic>
#include <JAKAZuRobot.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <cmath>

#define TASK_BUSY -11
#define TASK_SUCC 5
#define TASK_INIT 9


class BaseRobot : public QThread {
Q_OBJECT
protected:
    QString m_currentActionName;
    std::string m_ip;
    int m_ajNum = 0;
    MoveMode m_moveMode = INCR;
    CoordType m_coordType = COORD_JOINT;
    double m_velCmd = 0;
    double m_posCmd = 0;

    IOType m_ioType;
    int m_ioIndex;
    BOOL m_ioValue;

    std::thread m_t;
    std::atomic_bool m_isRequestCloseThread;

    RobotState m_robotState{};
    JointValue m_jVal{};
    std::mutex m_mutex;


    errno_t m_doAction(const QString &actionName, const std::function<void(void)> &func) {
        if (isRunning()) {
            qDebug() << "busy";
            QMessageBox::critical(nullptr, "ERROR", "[JAKA]上一指令未完成", QMessageBox::Ok);
            return TASK_BUSY;
        } else {
            m_currentActionName = actionName;
            func();
            start();
            return TASK_SUCC;
        }
    };

    void m_tryClearThread() {
        if (m_t.joinable()) {
            m_isRequestCloseThread.exchange(true);
            m_t.join();
        }
        m_isRequestCloseThread.exchange(false);
    }


Q_SIGNALS:

    void onComplete(QString actionName, int res);

public:
    explicit BaseRobot(QObject *parent = nullptr) : QThread(parent), m_isRequestCloseThread(false) {
//        for (double & i : m_jVal.jVal) {
//            i = 0;
//        }
    }

    void getJointVal(JointValue *jVal) {
        std::lock_guard<std::mutex> lockGuard(m_mutex);
        jVal->jVal[0] = m_jVal.jVal[0] + M_PI / 2;
        jVal->jVal[1] = -m_jVal.jVal[1];
        jVal->jVal[2] = -m_jVal.jVal[2];
        jVal->jVal[3] = m_jVal.jVal[3];
        jVal->jVal[4] = -m_jVal.jVal[4];
        jVal->jVal[5] = -m_jVal.jVal[5];
    }

    ~BaseRobot() override {
        m_tryClearThread();
    }

    /**
     * @brief 创建机器人控制句柄
     * @param ip  控制器ip地址
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t login_in(const char *ip) {
        return m_doAction("log_in", [&]() { m_ip = std::string(ip); });
    };

    /**
     * @brief 断开控制器连接
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t login_out() {
        return m_doAction("log_out", []() {});
    };

    /**
     * @param handle  机器人控制句柄
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t power_on() {
        return m_doAction("power_on", []() {});
    };

    /**
     * @brief 关闭机器人电源
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t power_off() {
        return m_doAction("power_off", []() {});
    };

    /**
     * @brief 机器人控制柜关机
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t shut_down() {
        return m_doAction("shut_down", []() {});
    };

    /**
     * @brief 控制机器人上使能
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t enable_robot() {
        return m_doAction("enable_robot", []() {});
    };

    /**
     * @brief 控制机器人下使能
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t disable_robot() {
        return m_doAction("disable_robot", []() {});
    };

    /**
     * @brief 控制机器人手动模式下运动
     * @param aj_num 1_based标识值，在关节空间下代表关节号0-5，笛卡尔下依次为x，y，z，rx，ry，rz
     * @param move_mode 机器人运动模式，增量运动或者绝对运动
     * @param coord_type 机器人运动坐标系，工具坐标系，基坐标系（当前的世界/用户坐标系）或关节空间
     * @param vel_cmd 指令速度，旋转轴或关节运动单位为rad/s，移动轴单位为mm/s
     * @param pos_cmd 指令位置，旋转轴或关节运动单位为rad，移动轴单位为mm
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t jog(int aj_num, MoveMode move_mode, CoordType coord_type, double vel_cmd, double pos_cmd) {
        return m_doAction("jog", [&]() {
            m_ajNum = aj_num;
            m_moveMode = move_mode;
            m_coordType = coord_type;
            m_velCmd = vel_cmd;
            m_posCmd = pos_cmd;
        });
    };

    /**
     * @brief 控制机器人手动模式下运动停止
     * @return ERR_SUCC 成功 其他失败
     */
    errno_t jog_stop(int num) {
        return m_doAction("jog_stop", [&]() {
            m_ajNum = num;
        });
    };

    /**
    * @brief 终止当前机械臂运动
    * @return ERR_SUCC 成功 其他失败
    */
    errno_t motion_abort() {
        return m_doAction("motion_abort", []() {});
    }

    /**
    * @brief 碰撞之后从碰撞保护模式恢复
    * @return ERR_SUCC 成功 其他失败
    */
    errno_t collision_recover() { return m_doAction("collision_recover", []() {}); }

    /**
* @brief 设置数字输出变量(DO)的值
* @param type DO类型
* @param index DO索引
* @param value DO设置值
* @return ERR_SUCC 成功 其他失败
*/
    errno_t set_digital_output(IOType type, int index, BOOL value) {
        return m_doAction("set_digital_output", [&]() {
            m_ioType = type;
            m_ioIndex = index;
            m_ioValue = value;
        });
    };
};

class VirtualRobot : public BaseRobot {
private:


public:
    explicit VirtualRobot(QObject *parent = nullptr) : BaseRobot(parent) {
    }

    void run() override {
        qDebug() << "run " << m_currentActionName << " at " << QThread::currentThreadId();
        errno_t res = ERR_SUCC;
        if (m_currentActionName == "jog") {
            if (m_moveMode == ABS) {
                m_tryClearThread();
                m_isRequestCloseThread.exchange(false);
                m_t = std::thread([&]() {
                    int period = 100;  // ms
                    double step = m_velCmd / 1000.0 * period;
                    double currentVal = m_jVal.jVal[m_ajNum];
                    if (currentVal > m_posCmd) step = -step;
                    while (!m_isRequestCloseThread.load()) {
                        currentVal += step;
                        if (qAbs(currentVal - m_posCmd) <= step) {
                            std::lock_guard<std::mutex> lockGuard(m_mutex);
                            m_jVal.jVal[m_ajNum] = m_posCmd;
                            break;
                        }
                        {
                            std::lock_guard<std::mutex> lockGuard(m_mutex);
                            m_jVal.jVal[m_ajNum] = currentVal;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(period));
                    }
                });
            } else {
                std::lock_guard<std::mutex> lockGuard(m_mutex);
                m_jVal.jVal[m_ajNum] += m_posCmd;
            }
        } else if (m_currentActionName == "jog_stop") {
            m_tryClearThread();
        }

        Q_EMIT onComplete(m_currentActionName, res);
        qDebug() << m_currentActionName << "finished";
    }
};

class RealRobot : public BaseRobot {
private:
    JAKAZuRobot *m_robot;
public:
    explicit RealRobot(QObject *parent = nullptr) : BaseRobot(parent), m_robot(new JAKAZuRobot) {

    }

    void run() override {
        qDebug() << "run " << m_currentActionName << "at " << QThread::currentThreadId();
        errno_t res = TASK_INIT;
        if (m_currentActionName == "log_in") {
            res = m_robot->login_in(m_ip.c_str());
            if (res == ERR_SUCC) {
                m_tryClearThread();
                m_t = std::thread([&]() {
                    while (!m_isRequestCloseThread.load()) {
                        {
                            std::lock_guard<std::mutex> lockGuard(m_mutex);
                            m_robot->get_robot_state(&m_robotState);
                            if (m_robotState.servoEnabled) {
                                m_robot->get_joint_position(&m_jVal);
                            }
//                            qDebug() << m_robotState.servoEnabled;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                });
            }
        } else if (m_currentActionName == "log_out") {
            res = m_robot->login_out();
        } else if (m_currentActionName == "power_on")
            res = m_robot->power_on();
        else if (m_currentActionName == "power_off")
            res = m_robot->power_off();
        else if (m_currentActionName == "shut_down")
            res = m_robot->shut_down();
        else if (m_currentActionName == "enable_robot")
            res = m_robot->enable_robot();
        else if (m_currentActionName == "disable_robot")
            res = m_robot->disable_robot();
        else if (m_currentActionName == "jog")
            res = m_robot->jog(m_ajNum, m_moveMode, m_coordType, m_velCmd, m_posCmd);
        else if (m_currentActionName == "jog_stop")
            res = m_robot->jog_stop(m_ajNum);
        else if (m_currentActionName == "motion_abort")
            res = m_robot->motion_abort();
        else if (m_currentActionName == "collision_recover")
            res = m_robot->collision_recover();
        else if (m_currentActionName == "set_digital_output")
            res = m_robot->set_digital_output(m_ioType, m_ioIndex, m_ioValue);
        Q_EMIT onComplete(m_currentActionName, res);
        qDebug() << m_currentActionName << "finished, " << res;
    }
};

#endif //PICKING_JAKA_PLUS_HPP
