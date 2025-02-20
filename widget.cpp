#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayout);
    socket = new QTcpSocket(this);
    ui->pushButton_close->setDisabled(true);
    connect(socket, &QTcpSocket::connected, this, [=](){
        ui->textEdit_info->append("success connect to " + ip.toString() +", port: " + ui->lineEdit_port->text());
        QMessageBox::information(nullptr, "成功！", "连接成功");
    });
    connect(socket, &QTcpSocket::errorOccurred, [](QAbstractSocket::SocketError error) {
        QMessageBox::information(nullptr, "连接失败", "连接失败!");
        qDebug() << "连接失败：" << error;
    });
    connect(socket, &QTcpSocket::readyRead, this, [=](){
        QByteArray mes = socket->readAll();
        QString readData = QString::fromUtf8(mes);
        ui->textEdit_info->append("receive: " + readData);
    });
    // 已连接才启用断开按钮
    connect(socket, &QTcpSocket::stateChanged, this, [=](){
        if(socket->state() == QTcpSocket::ConnectedState)
            ui->pushButton_close->setDisabled(false);
        else
            ui->pushButton_close->setDisabled(true);
    });
}

Widget::~Widget()
{
    delete ui;
    if(socket->isValid()){
        socket->disconnect();
    }
}

void Widget::on_pushButton_send_clicked()
{
    mes = ui->lineEdit_messsage->text();
    if(socket->state() == QAbstractSocket::ConnectedState){
        socket->write(mes.toStdString().c_str());
        ui->textEdit_info->append("send: " + mes);
        ui->lineEdit_messsage->clear();
    }else{
        QMessageBox::warning(nullptr, "警告", "请先连接服务器");
    }
}


void Widget::on_pushButton_connect_clicked()
{
    ip = QHostAddress(ui->lineEdit_IpAddress->text());
    port = ui->lineEdit_port->text().toInt();
    if(socket->state() != QAbstractSocket::ConnectedState)
        socket->connectToHost(ip, port);


}


void Widget::on_pushButton_close_clicked()
{
    if(socket->state() == QTcpSocket::ConnectedState){
        socket->disconnectFromHost();
        ui->textEdit_info->append("Disconnect from " + ip.toString());
    }
}

