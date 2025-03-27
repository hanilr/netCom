#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent) : QObject{parent}
{
    tcpServer = new QTcpServer();
    tcpSocket = new QTcpSocket();
}

bool TCPServer::StartServer(QHostAddress addr, quint16 port)
{
    if (tcpServer->listen(addr, port))
    {
        connect(tcpServer, &QTcpServer::newConnection, this, &TCPServer::onConnected);
        qDebug() << "[TCP Started] Host: " << addr << ", Port: " << port;
        return true;
    } else {
        qDebug() << "[TCP Not Started!]";
        return false;
    }
}

bool TCPServer::StopServer()
{ // IF NOT LISTEN THEN TRUE
    if (tcpServer->isListening())
    {
        disconnect(tcpServer, &QTcpServer::newConnection, this, &TCPServer::onConnected);
        tcpServer->close();
        if (tcpServer->isListening()) {
            qDebug() << "[TCP Still Working!]";
            return false;
        }
        else {
            qDebug() << "[TCP Stopped!]";
            return true;
        }
    }

    qDebug() << "[TCP Already Not Working!]";
    return true;
}

void TCPServer::StopConnection()
{
    tcpSocket->disconnectFromHost();
    qDebug() << "TCP Connection Stopped.";
}

void TCPServer::Broadcast(QString msg)
{
    QByteArray Data(msg.toUtf8());
    if (tcpSocket->state() == QTcpSocket::ConnectedState)
    {
        tcpSocket->write(Data);
        tcpSocket->flush();
        qDebug() << "Message sent: " << msg;
    } else qDebug() << "Message not sent!";
}

void TCPServer::onConnected()
{
    disconnect(tcpServer, &QTcpServer::newConnection, this, &TCPServer::onConnected);
    tcpSocket = tcpServer->nextPendingConnection();
    if (tcpSocket->state() == QTcpSocket::ConnectedState)
    {
        clientAddr = tcpSocket->peerAddress();
        clientPort = tcpSocket->peerPort();
        connect(tcpSocket, &QTcpSocket::disconnected, this, &TCPServer::onDisconnected);
        connect(tcpSocket, &QTcpSocket::readyRead, this, &TCPServer::onMessage);
        emit tcpServerConnected(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
        qDebug() << "TCP Connected.";
    } else { qDebug() << "TCP Not Connected."; }
}

void TCPServer::onDisconnected()
{
    disconnect(tcpSocket, SIGNAL(disconnected()));
    disconnect(tcpSocket, SIGNAL(readyRead()));
    emit tcpServerDisconnected();
    tcpSocket->close();
    tcpSocket->deleteLater();
    connect(tcpServer, &QTcpServer::newConnection, this, &TCPServer::onConnected);
    qDebug() << "TCP Disconnected.";
}

void TCPServer::onMessage()
{
    array = tcpSocket->readAll();
    emit newMessage(tcpSocket->peerAddress().toString(), array);
}
