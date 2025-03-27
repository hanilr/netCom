#ifndef UDPBASE_H
#define UDPBASE_H

#include <QObject>
#include <QUdpSocket>

class UDPBase : public QObject
{
    Q_OBJECT
public:
    explicit UDPBase(QObject *parent = nullptr);
    bool Bind(QHostAddress addr, quint16 port);
    void Unbind();

signals:
    void newMessage(QByteArray data, QHostAddress sender, quint16 senderPort);

public slots:
    void Send(const QString &address, quint16 port, const QByteArray &data);
    void Read();

private:
    QUdpSocket *socket;
};

#endif // UDPBASE_H
