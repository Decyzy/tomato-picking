#ifndef ROBOT_H
#define ROBOT_H

#include <QThread>
#include <QDebug>
#include <JAKAZuRobot.h>
#include <functional>
#include <QMessageBox>
#include <atomic>

#define TASK_BUSY -11
#define TASK_SUCC 5
#define TASK_INIT 9


class Robot : public QThread {
Q_OBJECT
private:
    JAKAZuRobot *m_robot;
    std::string m_ip;
    int m_ajNum = 0;
    MoveMode m_moveMode = INCR;
    CoordType m_coordType = COORD_JOINT;
    double m_velCmd = 0;
    double m_posCmd = 0;

    QString m_currentActionName;
    std::atomic_bool isSim;

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
Q_SIGNALS:

    void onComplete(QString actionName, int res);

public:
    explicit Robot(QObject *parent = nullptr) : QThread(parent), m_robot(new JAKAZuRobot()), isSim(true) {
    }

    void run() override {
        qDebug() << "run " << m_currentActionName << "at " << QThread::currentThreadId();
        errno_t res = TASK_INIT;
        if (m_currentActionName == "log_in")
            res = m_robot->login_in(m_ip.c_str());
        else if (m_currentActionName == "log_out")
            res = m_robot->login_out();
        else if (m_currentActionName == "power_on")
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

        Q_EMIT onComplete(m_currentActionName, res);
        qDebug() << m_currentActionName << "finished";
    };

    ~Robot() override {
        qDebug() << "[Robot] closing robot thread...";
        exit();
        terminate();
        qDebug() << "[Robot] robot thread is closed";
    };

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

//    /**
//     * @brief 机器人关节运动
//     * @param joint_pos 机器人关节运动目标位置
//     * @move_mode 指定运动模式：增量运动或绝对运动
//     * @param is_block 设置接口是否为阻塞接口，TRUE为阻塞接口 FALSE为非阻塞接口
//     * @param speed 机器人关节运动速度，单位：rad/s
//     * @return ERR_SUCC 成功 其他失败
//     */
//    errno_t joint_move(const JointValue *joint_pos, MoveMode move_mode, BOOL is_block, double speed) {};
//
//    /**
//     * @brief 机器人末端直线运动
//     * @param end_pos 机器人末端运动目标位置
//     * @param is_block 设置接口是否为阻塞接口，TRUE 为阻塞接口 FALSE 为非阻塞接口
//     * @param speed 机器人直线运动速度，单位：mm/s
//     * @return ERR_SUCC 成功 其他失败
//     */
//    errno_t linear_move(const CartesianPose *end_pos, MoveMode move_mode, BOOL is_block, double speed) {};
//
//    /**
//     * @brief 机器人SERVO MOVE模式使能
//     * @param enable  TRUE为进入SERVO MOVE模式，FALSE表示退出该模式
//     * @return ERR_SUCC 成功 其他失败
//     */
//    errno_t servo_move_enable(BOOL enable) {};
//
//    /**
//     * @brief 机器人关节空间位置控制模式
//     * @param joint_pos 机器人关节运动目标位置
//     * @move_mode 指定运动模式：增量运动或绝对运动
//     * @return ERR_SUCC成功 其他失败
//     */
//    errno_t servo_j(const JointValue *joint_pos, MoveMode move_mode) {};
//
//    /**
//     * @brief 机器人笛卡尔空间位置控制模式
//     * @param cartesian_pose 机器人笛卡尔空间运动目标位置
//     * @move_mode 指定运动模式：增量运动或绝对运动
//     * @return ERR_SUCC 成功 其他失败
//     */
//    errno_t servo_p(const CartesianPose *cartesian_pose, MoveMode move_mode) {};
};

#endif  // ROBOT_H
