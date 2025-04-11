#include "tcpclient.h"

TCPClient::TCPClient(QObject *parent) : QObject{parent}
{
    tcpClient = new QTcpSocket();
}

void TCPClient::Connect(QHostAddress addr, quint16 port)
{
    qDebug() << "[TCP] Attempting to connect. Host: " << addr << ", Port: " << port;
    tcpClient->connectToHost(addr, port);

    if (tcpClient->state() == QTcpSocket::ConnectedState) {
        qDebug() << "[TCP] Client connected to server.";
        connect(tcpClient, &QTcpSocket::connected, this, &TCPClient::onConnected);
        connect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    } else if (tcpClient->state() == QTcpSocket::UnconnectedState) {
        qDebug() << "[TCP] Connection error.";
        disconnect(tcpClient, &QTcpSocket::connected, this, &TCPClient::onConnected);
        disconnect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    }
}

void TCPClient::Disconnect()
{
    qDebug() << "[TCP] Attempting to disconnect.";
    tcpClient->disconnectFromHost();

    if (tcpClient->state() == QTcpSocket::UnconnectedState) {
        qDebug() << "[TCP] Client disconnected from server.";
        disconnect(tcpClient, &QTcpSocket::connected, this, &TCPClient::onConnected);
        disconnect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    } else if (tcpClient->state() == QTcpSocket::ConnectedState) { qDebug() << "[TCP] Disconnection error."; }
}

void TCPClient::Close()
{
    tcpClient->close();
    qDebug() << "[TCP] Client closed.";
}

void TCPClient::Abort()
{
    tcpClient->abort();
    qDebug() << "[TCP] Connection aborted.";
}

void TCPClient::Send(const QByteArray &data)
{
    if (tcpClient->state() == QTcpSocket::ConnectedState) {
        tcpClient->write(data);
        tcpClient->flush();
        qDebug() << "[TCP] Message sent: " << data;
    } else qDebug() << "[TCP] Message not sent!";
}

void TCPClient::onConnected()
{
    disconnect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    connect(tcpClient, &QTcpSocket::disconnected, this, &TCPClient::onDisconnected);
    connect(tcpClient, &QTcpSocket::readyRead, this, &TCPClient::onMessage);

    qDebug() << "[TCP] Connection verification.";
    emit tcpClientConnected(tcpClient->peerAddress().toString(), tcpClient->peerPort());
}

void TCPClient::onDisconnected()
{
    disconnect(tcpClient, &QTcpSocket::disconnected, this, &TCPClient::onDisconnected);
    disconnect(tcpClient, &QTcpSocket::readyRead, this, &TCPClient::onMessage);

    Close();
    emit tcpClientDisconnected();
}

void TCPClient::onMessage()
{
    qDebug() << "[TCP] New message arrived.";
    TcpArray = tcpClient->readAll();
    emit newMessage(tcpClient->peerAddress().toString(), TcpArray);
}

void TCPClient::onStateChanged(QAbstractSocket::SocketState state)
{
    disconnect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    switch (state)
    {
    case QAbstractSocket::UnconnectedState:
        emit connectionFailed();
        qDebug()<<"[TCP State] Connecting Timeout";
        break;
    case QAbstractSocket::HostLookupState:
        qDebug()<<"[TCP State] Host Lookup State";
        break;
    case QAbstractSocket::ConnectingState:
        qDebug()<<"[TCP State] Connecting State";
        break;
    case QAbstractSocket::ConnectedState:
        qDebug()<<"[TCP State] Connected State";
        break;
    case QAbstractSocket::BoundState:
        qDebug()<<"[TCP State] Bound State";
        break;
    case QAbstractSocket::ListeningState:
        qDebug()<<"[TCP State] Listening State";
        break;
    case QAbstractSocket::ClosingState:
        qDebug()<<"[TCP State] Closing State";
        break;
    }
}
