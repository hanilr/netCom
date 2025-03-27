#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "udpbase.h"
#include "tcpserver.h"
#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonTCPRed_clicked();

    void on_ButtonUDPRed_clicked();

    void on_ButtonLogSave_clicked();

    void on_ButtonLogClear_clicked();

    void on_ButtonTCPServererClear_clicked();

    void on_ButtonTCPServererSave_clicked();

    void on_ButtonTCPClienterClear_clicked();

    void on_ButtonTCPClienterSave_clicked();

    void on_ButtonTCPClientClear_clicked();

    void on_ButtonTCPClientSave_clicked();

    void on_ButtonTCPServerClear_clicked();

    void on_ButtonTCPServerSave_clicked();

    void on_ButtonUDPClear_clicked();

    void on_ButtonUDPSaveScreen_clicked();

    void on_ButtonUDPSenderClear_clicked();

    void on_ButtonUDPSenderSave_clicked();

    void on_ButtonUDPListenClear_clicked();

    void on_ButtonUDPListenSave_clicked();

    void on_ButtonUDPSendClear_clicked();

    void on_ButtonUDPSendSave_clicked();

    void on_ButtonRefresh_clicked();

    void on_TextHost_returnPressed();

    void on_TextPort_returnPressed();

    void on_ButtonConnectionSelect_clicked();

    void on_ButtonUDPListen_clicked();

    void onDataReceived(QByteArray data, QHostAddress sender, quint16 senderPort); // USER MADE

    void on_ButtonUDPSenderSend_clicked();

    void on_TextUDPSenderCommand_returnPressed();

    void on_ButtonUDPListenListen_clicked();

    void UDPDataReceived(QByteArray data, QHostAddress sender, quint16 senderPort); // USER MADE

    void on_ButtonUDPSendBind_clicked();

    void on_ButtonUDPSendSend_clicked();

    void on_TextUDPSendCommand_returnPressed();

    void log_message(QString msg); // USER MADE

    void on_ButtonTCPServererStart_clicked();

    void on_ButtonTCPClienterConnect_clicked();

    void onDataReceivedTcp(const QString &from, const QString &message); // USER MADE

    void on_ButtonTCPClienterSend_clicked();

    void on_TextTCPClienterCommand_returnPressed();

    void onDataReceivedTcpClient(const QString &from, const QString &message); // USER MADE

    void on_ButtonTCPServererSend_clicked();

    void on_TextTCPServererCommand_returnPressed();

    void on_ButtonTCPServerStart_clicked();

    void TcpServerDataReceived(const QString &from, const QString &message); // USER MADE

    void on_ButtonTCPServerSend_clicked();

    void on_TextTCPServerCommand_returnPressed();

    void on_ButtonTCPClientConnect_clicked();

    void TcpClientDataReceived(const QString &from, const QString &message); // USER MADE

    void on_ButtonTCPClientSend_clicked();

    void on_TextTCPClientCommand_returnPressed();

private:
    Ui::MainWindow *ui;
    UDPBase *socket;
    TCPServer *tcpServer;
    TCPClient *tcpClient;
};
#endif // MAINWINDOW_H
