#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(QObject *parent = nullptr);
    void Connect(QHostAddress addr, quint16 port);
    void Disconnect();
    void Close();
    void Abort();
    void Send(QString string);

signals:
    void newMessage(const QString &from, const QString &message);
    void tcpClientConnected(const QString &from, quint16 port);
    void tcpClientDisconnected();
    void connectionFailed();

private slots:
    void onConnected();
    void onDisconnected();
    void onMessage();
    void onStateChanged(QAbstractSocket::SocketState state);

private:
    QTcpSocket *tcpClient;
    QByteArray array;
};

#endif // TCPCLIENT_H
