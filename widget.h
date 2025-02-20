#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_pushButton_send_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::Widget *ui;
    QHostAddress ip;
    int port;
    QString mes;
    QTcpSocket *socket;
};
#endif // WIDGET_H
