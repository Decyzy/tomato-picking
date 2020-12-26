//
// Created by dell on 2020/11/4.
//

#include "picking/rviz_jaka.hpp"
#include <cstdio>
#include <dlfcn.h>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

#include <geometry_msgs/Twist.h>
#include <QDebug>


namespace rviz_jaka {

    double degree2rad(double degree) {
        return degree / 180.0 * M_PI;
    }

    double rad2degree(double degree) {
        return degree * 180.0 / M_PI;
    }

// 构造函数，初始化变量
    JAKAPanel::JAKAPanel(QWidget *parent)
            : rviz::Panel(parent), m_ui(new Ui::Form), m_robot(nullptr), m_virtualRobot(new VirtualRobot),
              m_realRobot(new RealRobot), m_timer(new QTimer(this)) {
        m_ui->setupUi(this);


        if (m_ui->isRealCk->isChecked()) {
            m_robot = m_realRobot;
        } else {
            m_robot = m_virtualRobot;
        }
        connect(m_realRobot, &BaseRobot::onComplete, this, &JAKAPanel::onActionComplete);
        connect(m_virtualRobot, &BaseRobot::onComplete, this, &JAKAPanel::onActionComplete);


        connect(m_timer, &QTimer::timeout, this, &JAKAPanel::m_updateJointLabels);
        m_timer->start(100);  // ms

        m_jointState.position.resize(6);
        m_jointState.name.resize(6);
        m_jointState.name[0] = "joint_1";
        m_jointState.name[1] = "joint_2";
        m_jointState.name[2] = "joint_3";
        m_jointState.name[3] = "joint_4";
        m_jointState.name[4] = "joint_5";
        m_jointState.name[5] = "joint_6";
        m_updateJointLabels();
        jointLimits[0][0] = -270;
        jointLimits[0][1] = 270;
        jointLimits[1][0] = -50;
        jointLimits[1][1] = 230;
        jointLimits[2][0] = -155;
        jointLimits[2][1] = 155;
        jointLimits[3][0] = -85;
        jointLimits[3][1] = 265;
        jointLimits[4][0] = -270;
        jointLimits[4][1] = 270;
        jointLimits[5][0] = -270;
        jointLimits[5][1] = 270;
    }


// 重载父类的功能
    void JAKAPanel::save(rviz::Config config) const {
        rviz::Panel::save(config);
    }

// 重载父类的功能，加载配置数据
    void JAKAPanel::load(const rviz::Config &config) {
        rviz::Panel::load(config);
    }

    JAKAPanel::~JAKAPanel() {
        ROS_DEBUG("~JAKAPanel");
        delete m_ui;
        delete m_robot;
        if (m_t.joinable()) {
            m_isRequestCloseThread.exchange(true);
            m_t.join();
        }
    }


    void JAKAPanel::onActionComplete(QString actionName, int res) {
        ROS_DEBUG("%s,%d", actionName.toStdString().c_str(), res);
        if (actionName == "log_in") {
            m_ui->loginBt->setEnabled(true);
            if (res == ERR_SUCC) {
                m_ui->loginBt->setText(tr("注销"));
                m_ui->powerOnBt->setEnabled(true);
            }
        } else if (actionName == "log_out") {
            m_ui->loginBt->setEnabled(true);
            if (res == ERR_SUCC) {
                m_ui->loginBt->setText(tr("登录"));
                m_ui->powerOnBt->setDisabled(true);
                m_ui->enableBt->setDisabled(true);
            }
        } else if (actionName == "power_on") {
            m_ui->powerOnBt->setEnabled(true);
            if (res == ERR_SUCC) {
                m_ui->powerOnBt->setText(tr("关电"));
                m_ui->enableBt->setEnabled(true);
            }
        } else if (actionName == "power_off") {
            m_ui->powerOnBt->setEnabled(true);
            if (res == ERR_SUCC) {
                m_ui->powerOnBt->setText(tr("上电"));
                m_ui->enableBt->setDisabled(true);
            }
        } else if (actionName == "enable_robot") {
            m_ui->enableBt->setEnabled(true);
            if (res == ERR_SUCC) {
                m_ui->enableBt->setText(tr("下使能"));
            }
        } else if (actionName == "disable_robot") {
            m_ui->enableBt->setEnabled(true);
            if (res == ERR_SUCC) {
                m_ui->enableBt->setText(tr("使能"));
            }
        }

        switch (res) {
            case ERR_INVALID_HANDLER:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]无效的句柄", QMessageBox::Ok);
                break;
            case ERR_INVALID_PARAMETER:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]无效的参数", QMessageBox::Ok);
                break;
            case ERR_COMMUNICATION_ERR:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]tcp/ip通信错误", QMessageBox::Ok);
                break;
            case ERR_KINE_INVERSE_ERR:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]逆解失败", QMessageBox::Ok);
                break;
            case ERR_EMERGENCY_PRESSED:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]急停按钮按下", QMessageBox::Ok);
                break;
            case ERR_NOT_POWERED:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]没有上电", QMessageBox::Ok);
                break;
            case ERR_NOT_ENABLED:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]没有使能", QMessageBox::Ok);
                break;
            case ERR_DISABLE_SERVOMODE:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]没有进入servo模式", QMessageBox::Ok);
                break;
            case ERR_NOT_OFF_ENABLE:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]没有关闭机器人使能", QMessageBox::Ok);
                break;
            case ERR_PROGRAM_IS_RUNNING:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]作业程序正在运行", QMessageBox::Ok);
                break;
            case ERR_CANNOT_OPEN_FILE:
                QMessageBox::critical(nullptr, "ERROR", "[JAKA]无法打开文件", QMessageBox::Ok);
                break;
            default:
                break;
        }
    }

    void JAKAPanel::on_applyBt_clicked(bool checked) {
        ROS_DEBUG("on_applyBt_clicked");
        m_prefix = m_ui->prefixLineEdit->text();
        std::string ip;
        m_nh.getParam((m_prefix + "/ip").toStdString(), ip);
        if (!ip.empty())
            m_ui->ipLineEdit->setText(QString::fromStdString(ip));
        if (m_t.joinable()) {
            ROS_INFO("close old thread...");
            m_isRequestCloseThread.exchange(true);
            m_t.join();
            ROS_INFO("old thread is closed");
        }
        m_t = std::thread([&]() {
            m_isRequestCloseThread.exchange(false);
            m_jointStatesPub = m_nh.advertise<sensor_msgs::JointState>((m_prefix + "/joint_states").toStdString(), 100);
            ros::Rate loopRate(50);
            while (ros::ok() && !m_isRequestCloseThread.load()) {
                JointValue jVal;
                m_robot->getJointVal(&jVal);
                for (int i = 0; i < 6; i++) {
                    m_jointState.position[i] = jVal.jVal[i];
                }
                m_jointState.header.stamp = ros::Time::now();
                m_jointStatesPub.publish(m_jointState);
                ros::spinOnce();
                loopRate.sleep();
            }
            m_jointStatesPub.shutdown();
        });
    }

    void JAKAPanel::on_loginBt_clicked(bool checked) {
        ROS_DEBUG("on_loginBt_clicked");
        m_ui->loginBt->setDisabled(true);
        if (m_ui->loginBt->text() == "登录") {
            m_ip = m_ui->ipLineEdit->text();
            ROS_INFO("login %s ...", m_ip.toStdString().c_str());
            m_robot->login_in(m_ip.toStdString().c_str());
            m_ui->loginBt->setText("登录...");
        } else {
            m_ui->loginBt->setText("注销...");
            m_robot->login_out();
        }

    }

    void JAKAPanel::on_powerOnBt_clicked(bool checked) {
        ROS_DEBUG("on_powerOnBt_clicked");
        m_ui->powerOnBt->setDisabled(true);
        if (m_ui->powerOnBt->text() == "上电") {
            m_robot->power_on();
            m_ui->powerOnBt->setText("上电...");

        } else {
            m_robot->power_off();
            m_ui->powerOnBt->setText("关电...");
        }
    }

    void JAKAPanel::on_enableBt_clicked(bool checked) {
        ROS_DEBUG("on_enableBt_clicked %d", checked);
        m_ui->enableBt->setDisabled(true);
        if (m_ui->enableBt->text() == "使能") {
            m_robot->enable_robot();
            m_ui->enableBt->setText("使能...");
        } else {
            m_robot->disable_robot();
            m_ui->enableBt->setText("下使能...");
        }
    }


    void JAKAPanel::m_updateJointLabels() {
        JointValue jVal;
        m_robot->getJointVal(&jVal);
        m_ui->j1->setText(QString("%1").arg(rad2degree(jVal.jVal[0]), 5, 'f', 2));
        m_ui->j2->setText(QString("%1").arg(rad2degree(jVal.jVal[1]), 5, 'f', 2));
        m_ui->j3->setText(QString("%1").arg(rad2degree(jVal.jVal[2]), 5, 'f', 2));
        m_ui->j4->setText(QString("%1").arg(rad2degree(jVal.jVal[3]), 5, 'f', 2));
        m_ui->j5->setText(QString("%1").arg(rad2degree(jVal.jVal[4]), 5, 'f', 2));
        m_ui->j6->setText(QString("%1").arg(rad2degree(jVal.jVal[5]), 5, 'f', 2));
    }

    void JAKAPanel::on_j1SubBt_pressed() { m_handleJointBtClicked(true, 0); }

    void JAKAPanel::on_j2SubBt_pressed() { m_handleJointBtClicked(true, 1); }

    void JAKAPanel::on_j3SubBt_pressed() { m_handleJointBtClicked(true, 2); }

    void JAKAPanel::on_j4SubBt_pressed() { m_handleJointBtClicked(true, 3); }

    void JAKAPanel::on_j5SubBt_pressed() { m_handleJointBtClicked(true, 4); }

    void JAKAPanel::on_j6SubBt_pressed() { m_handleJointBtClicked(true, 5); }


    void JAKAPanel::on_j1SubBt_released() { m_handleJointBtClicked(false, 0); }

    void JAKAPanel::on_j2SubBt_released() { m_handleJointBtClicked(false, 1); }

    void JAKAPanel::on_j3SubBt_released() { m_handleJointBtClicked(false, 2); }

    void JAKAPanel::on_j4SubBt_released() { m_handleJointBtClicked(false, 3); }

    void JAKAPanel::on_j5SubBt_released() { m_handleJointBtClicked(false, 4); }

    void JAKAPanel::on_j6SubBt_released() { m_handleJointBtClicked(false, 5); }

    void JAKAPanel::on_j1AddBt_pressed() { m_handleJointBtClicked(true, 0, true); }

    void JAKAPanel::on_j2AddBt_pressed() { m_handleJointBtClicked(true, 1, true); }

    void JAKAPanel::on_j3AddBt_pressed() { m_handleJointBtClicked(true, 2, true); }

    void JAKAPanel::on_j4AddBt_pressed() { m_handleJointBtClicked(true, 3, true); }

    void JAKAPanel::on_j5AddBt_pressed() { m_handleJointBtClicked(true, 4, true); }

    void JAKAPanel::on_j6AddBt_pressed() { m_handleJointBtClicked(true, 5, true); }

    void JAKAPanel::on_j1AddBt_released() { m_handleJointBtClicked(false, 0, true); }

    void JAKAPanel::on_j2AddBt_released() { m_handleJointBtClicked(false, 1, true); }

    void JAKAPanel::on_j3AddBt_released() { m_handleJointBtClicked(false, 2, true); }

    void JAKAPanel::on_j4AddBt_released() { m_handleJointBtClicked(false, 3, true); }

    void JAKAPanel::on_j5AddBt_released() { m_handleJointBtClicked(false, 4, true); }

    void JAKAPanel::on_j6AddBt_released() { m_handleJointBtClicked(false, 5, true); }

    void JAKAPanel::m_handleJointBtClicked(bool isPressed, int index, bool isAdd) {
        if (isPressed) {
            if (m_ui->moveContinuouslyBt->isChecked()) {
                m_robot->jog(index, ABS, COORD_JOINT, degree2rad(m_ui->maxDegSp->value()),
                             degree2rad(jointLimits[index][isAdd ? 1 : 0]));
            }
        } else {
            if (m_ui->moveOnceBt->isChecked()) {
                m_robot->jog(index, INCR, COORD_JOINT, degree2rad(m_ui->maxDegSp->value()),
                             isAdd ? degree2rad(m_ui->moveOnceSp->value()) : -degree2rad(m_ui->moveOnceSp->value()));
            } else {
                m_robot->jog_stop(index);
            }
        }
    }

    void JAKAPanel::on_stopBt_clicked(bool checked) {
        ROS_INFO("jaka %s motion_abort", m_prefix.toStdString().c_str());
        m_robot->motion_abort();
    }

    void JAKAPanel::on_isRealCk_stateChanged(int state) {
        if (state == 0) {
            m_robot = m_virtualRobot;
        } else {
            m_robot = m_realRobot;
        }
    }

    void JAKAPanel::on_recoveryBt_clicked(bool) {
        ROS_INFO("jaka %s collision_recover", m_prefix.toStdString().c_str());
        m_robot->collision_recover();
    }

    void JAKAPanel::on_doBox1_stateChanged(int state) {
        m_handleDOChecked(1, state);
    }

    void JAKAPanel::on_doBox2_stateChanged(int state) {
        m_handleDOChecked(2, state);
    }

    void JAKAPanel::on_doBox3_stateChanged(int state) {
        m_handleDOChecked(3, state);
    }

    void JAKAPanel::on_doBox4_stateChanged(int state) {
        m_handleDOChecked(4, state);
    }

    void JAKAPanel::on_doBox5_stateChanged(int state) {
        m_handleDOChecked(5, state);
    }
    void JAKAPanel::on_doBox6_stateChanged(int state) {
        m_handleDOChecked(6, state);
    }

    void JAKAPanel::m_handleDOChecked(int index, int state) {
        if (state == 0) {
            m_robot->set_digital_output(IO_CABINET, index, FALSE);
        } else {
            m_robot->set_digital_output(IO_CABINET, index, TRUE);
        }
    }
} // end namespace rviz_plugin_tutorials


// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(rviz_jaka::JAKAPanel, rviz::Panel)
