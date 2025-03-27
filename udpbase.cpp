#include "udpbase.h"

UDPBase::UDPBase(QObject *parent) : QObject{parent}
{
    socket = new QUdpSocket();
}

bool UDPBase::Bind(QHostAddress addr, quint16 port)
{
    socket->abort();
    if (!socket->bind(QHostAddress::Any, port)) {
        qDebug() << "Failed to bind UDP socket on port" << port;
        return false;
    } else {
        qDebug() << "UDP socket bound on port" << port;
        connect(socket, &QUdpSocket::readyRead, this, &UDPBase::Read);
        return true;
    }
}

void UDPBase::Unbind()
{
    disconnect(socket, &QUdpSocket::readyRead, this, &UDPBase::Read);
    socket->close();
}

void UDPBase::Send(const QString &address, quint16 port, const QByteArray &data)
{
    socket->writeDatagram(data, QHostAddress(address), port);
}

void UDPBase::Read()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        emit newMessage(datagram, sender, senderPort);
    }
}
