#include "tcpclient.h"

TCPClient::TCPClient(QObject *parent) : QObject{parent}
{
    tcpClient = new QTcpSocket();
}

void TCPClient::Connect(QHostAddress addr, quint16 port)
{
    tcpClient->connectToHost(addr, port);
    connect(tcpClient, &QTcpSocket::connected, this, &TCPClient::onConnected);
    connect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
}

void TCPClient::Disconnect() { tcpClient->disconnectFromHost(); }

void TCPClient::Close() { tcpClient->close(); }

void TCPClient::Abort() { tcpClient->abort(); }

void TCPClient::Send(QString string)
{
    QByteArray Data(string.toUtf8());
    if (tcpClient->state() == QTcpSocket::ConnectedState)
    {
        tcpClient->write(Data);
        tcpClient->flush();
        qDebug() << "Message sent: " << string;
    } else qDebug() << "Message not sent!";
}

void TCPClient::onConnected()
{
    disconnect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    connect(tcpClient, &QTcpSocket::disconnected, this, &TCPClient::onDisconnected);
    connect(tcpClient, &QTcpSocket::readyRead, this, &TCPClient::onMessage);
    emit tcpClientConnected(tcpClient->peerAddress().toString(), tcpClient->peerPort());
}

void TCPClient::onDisconnected()
{
    disconnect(tcpClient, &QTcpSocket::disconnected, this, &TCPClient::onDisconnected);
    disconnect(tcpClient, &QTcpSocket::readyRead, this, &TCPClient::onMessage);
    tcpClient->close();
    emit tcpClientDisconnected();
}

void TCPClient::onMessage()
{
    array = tcpClient->readAll();
    emit newMessage(tcpClient->peerAddress().toString(), array);
}

void TCPClient::onStateChanged(QAbstractSocket::SocketState state)
{
    disconnect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    switch (state)
    {
    case QAbstractSocket::UnconnectedState:
        emit connectionFailed();
        qDebug()<<"[TCP] Connecting Timeout";
        break;
    case QAbstractSocket::HostLookupState:
        qDebug()<<"[TCP] Host Lookup State";
        break;
    case QAbstractSocket::ConnectingState:
        qDebug()<<"[TCP] Connecting State";
        break;
    case QAbstractSocket::ConnectedState:
        qDebug()<<"[TCP] Connected State";
        break;
    case QAbstractSocket::BoundState:
        qDebug()<<"[TCP] Bound State";
        break;
    case QAbstractSocket::ListeningState:
        qDebug()<<"[TCP] Listening State";
        break;
    case QAbstractSocket::ClosingState:
        qDebug()<<"[TCP] Closing State";
        break;
    }
}
