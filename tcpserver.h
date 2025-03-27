#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    bool StartServer(QHostAddress addr, quint16 port);
    bool StopServer();
    void StopConnection();
    void Broadcast(QString msg);

signals:
    void newMessage(const QString &from, const QString &message);
    void tcpServerConnected(const QString &from, quint16 port);
    void tcpServerDisconnected();

private slots:
    void onConnected();
    void onDisconnected();
    void onMessage();

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QHostAddress clientAddr;
    quint16 clientPort;
    QByteArray array;
};

#endif // TCPSERVER_H
