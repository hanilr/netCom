#include "udpbase.h"

UDPBase::UDPBase(QObject *parent) : QObject{parent}
{
    socket = new QUdpSocket();
}

bool UDPBase::Bind(QHostAddress addr, quint16 port)
{
    socket->abort();
    if (!socket->bind(addr, port)) {
        qDebug() << "[UDP] Failed to bind socket. Host: " << addr << ", Port: " << port;
        disconnect(socket, &QUdpSocket::readyRead, this, &UDPBase::Read);
        return false;
    } else {
        qDebug() << "[UDP] Socket bound. Host: " << addr << ", Port: " << port;
        connect(socket, &QUdpSocket::readyRead, this, &UDPBase::Read);

        if (isError(addr, port)) qDebug() << "[UDP] Bound error.";
        else return true;
    }
    return false;
}

void UDPBase::Unbind()
{
    disconnect(socket, &QUdpSocket::readyRead, this, &UDPBase::Read);
    socket->close();

    if (socket->state() != QUdpSocket::BoundState) qDebug() << "[UDP] Socket unbound.";
    else qDebug() << "[UDP] Failed to unbound socket.";
}

void UDPBase::Send(const QString &address, quint16 port, const QByteArray &data)
{
    QHostAddress ipAddress(address);
    if (data.isEmpty()) qDebug() << "[UDP] Empty datagram.";
    else if (isError(ipAddress, port)) qDebug() << "[UDP] Sending error.";
    else socket->writeDatagram(data, QHostAddress(address), port);
}

void UDPBase::Read()
{
    if (!socket) qDebug() << "[UDP] Socket is null.";
    else if (socket->state() != QUdpSocket::BoundState) qDebug() << "[UDP] Socket is not bound.";
    else {
        while (socket->hasPendingDatagrams()) {
            QHostAddress sender;
            quint16 senderPort;
            QByteArray datagram;

            if (socket->pendingDatagramSize() <= 0) qDebug() << "[UDP] Invalid datagram size.";
            else {
                datagram.resize(socket->pendingDatagramSize());
                qint64 bytesRead = socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
                if (bytesRead == -1) qDebug() << "[UDP] Failed to read datagram.";
                else emit newMessage(datagram, sender, senderPort);
            }
        }
    }
}

bool UDPBase::isError(const QHostAddress &address, quint16 port)
{
    if (!socket) qDebug() << "[UDP] Socket is null.";
    else if (socket->state() != QUdpSocket::BoundState) qDebug() << "[UDP] Socket is not bound.";
    else if (address.isNull()) qDebug() << "[UDP] Invalid IP Address.";
    else if (port == 0 || port > 65535) qDebug() << "[UDP] Invalid Port Address.";
    else return false;
    return true;
}
