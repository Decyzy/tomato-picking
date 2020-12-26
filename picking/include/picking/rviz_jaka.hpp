//
// Created by dell on 2020/11/4.
//

#ifndef PICKING_RVIZ_JAKA_HPP
#define PICKING_RVIZ_JAKA_HPP

#include <ros/console.h>
#include <rviz/panel.h>   //plugin基类的头文件
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <thread>

#include "rviz_jaka_ui.h"
//#include "robot.hpp"
#include <atomic>
#include "JAKA_plus.hpp"

namespace rviz_jaka {

    class JAKAPanel : public rviz::Panel {
    Q_OBJECT
    public:
        // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
        explicit JAKAPanel(QWidget *parent = nullptr);

        // 重载rviz::Panel积累中的函数，用于保存、加载配置文件中的数据
        void load(const rviz::Config &config) override;

        void save(rviz::Config config) const override;

        ~JAKAPanel() override;

    public Q_SLOTS:

        void onActionComplete(QString actionName, int res);

    protected Q_SLOTS:


        void on_loginBt_clicked(bool checked = false);

        void on_applyBt_clicked(bool checked = false);

        void on_powerOnBt_clicked(bool checked = false);

        void on_enableBt_clicked(bool checked = false);

        void on_stopBt_clicked(bool checked = false);

        void on_j1SubBt_released();

        void on_j2SubBt_released();

        void on_j3SubBt_released();

        void on_j4SubBt_released();

        void on_j5SubBt_released();

        void on_j6SubBt_released();

        void on_j1SubBt_pressed();

        void on_j2SubBt_pressed();

        void on_j3SubBt_pressed();

        void on_j4SubBt_pressed();

        void on_j5SubBt_pressed();

        void on_j6SubBt_pressed();

        void on_j1AddBt_pressed();

        void on_j2AddBt_pressed();

        void on_j3AddBt_pressed();

        void on_j4AddBt_pressed();

        void on_j5AddBt_pressed();

        void on_j6AddBt_pressed();

        void on_j1AddBt_released();

        void on_j2AddBt_released();

        void on_j3AddBt_released();

        void on_j4AddBt_released();

        void on_j5AddBt_released();

        void on_j6AddBt_released();

        void on_isRealCk_stateChanged(int);

        void on_recoveryBt_clicked(bool);

        void on_doBox1_stateChanged(int);
        void on_doBox2_stateChanged(int);
        void on_doBox3_stateChanged(int);
        void on_doBox4_stateChanged(int);
        void on_doBox5_stateChanged(int);
        void on_doBox6_stateChanged(int);

    protected:
        Ui::Form *m_ui;
        ros::NodeHandle m_nh;

        QString m_ip;
        BaseRobot *m_robot;
        VirtualRobot *m_virtualRobot;
        RealRobot *m_realRobot;
        QString m_prefix;
        std::thread m_t;
        std::atomic_bool m_isRequestCloseThread;
        ros::Publisher m_jointStatesPub;
        sensor_msgs::JointState m_jointState;

        QTimer *m_timer;

        double jointLimits[6][2]{};

        void m_updateJointLabels();

        void m_handleJointBtClicked(bool isPressed, int index, bool isAdd = false);

        void m_handleDOChecked(int index, int state);

    };

} // end namespace rviz_jaka

#endif //PICKING_RVIZ_JAKA_HPP
