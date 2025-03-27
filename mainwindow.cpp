#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "udpbase.h"

#include <QFile>
#include <QFileDialog>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(new UDPBase)
    , tcpServer(new TCPServer)
    , tcpClient(new TCPClient)
{
    ui->setupUi(this);

    // PROTOCOL TABS
    ui->TabConnectionProtocols->setTabEnabled(1, false);
    ui->TabConnectionProtocols->setTabEnabled(2, false);
    ui->TabConnectionProtocols->setTabEnabled(4, false);
    ui->TabConnectionProtocols->setTabEnabled(5, false);

    ui->TabConnectionProtocols->setCurrentIndex(0);
    ui->TextHost->setFocus();

    // NETWORK INTERFACE AND IP ADDRESS
    on_ButtonRefresh_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
    delete tcpServer;
    delete tcpClient;
}

void MainWindow::on_ButtonTCPRed_clicked() { ui->FrameTCPWarning->close(); }

void MainWindow::on_ButtonUDPRed_clicked() { ui->FrameUDPWarning->close(); }

void MainWindow::on_ButtonLogSave_clicked()
{
    if (ui->TextLog->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextLog->toPlainText() + "\n";

            file.close();
            log_message("[Log] Log screen saved successfully.");
        }
    } else {
        log_message("[Log] Log screen is empty.");
    }
}

void MainWindow::on_ButtonTCPServererSave_clicked()
{
    if (ui->TextTCPServerer->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextTCPServerer->toPlainText() + "\n";

            file.close();
            log_message("[Log] Screen saved successfully.");
        }
    } else {
        log_message("[Log] Screen is empty.");
    }
}

void MainWindow::on_ButtonTCPClienterSave_clicked()
{
    if (ui->TextTCPClienter->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextTCPClienter->toPlainText() + "\n";

            file.close();
            log_message("[Log] Screen saved successfully.");
        }
    } else {
        log_message("[Log] Screen is empty.");
    }
}

void MainWindow::on_ButtonTCPClientSave_clicked()
{
    if (ui->TextTCPClient->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextTCPClient->toPlainText() + "\n";

            file.close();
            log_message("[Log] Screen saved successfully.");
        }
    } else {
        log_message("[Log] Screen is empty.");
    }
}

void MainWindow::on_ButtonTCPServerSave_clicked()
{
    if (ui->TextTCPServer->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextTCPServer->toPlainText() + "\n";

            file.close();
            log_message("[Log] Screen saved successfully.");
        }
    } else {
        log_message("[Log] Screen is empty.");
    }
}

void MainWindow::on_ButtonUDPSaveScreen_clicked()
{
    if (ui->TextUDPListener->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextUDPListener->toPlainText() + "\n";

            file.close();
            log_message("[Log] Screen saved successfully.");
        }
    } else {
        log_message("[Log] Screen is empty.");
    }
}

void MainWindow::on_ButtonUDPSenderSave_clicked()
{
    if (ui->TextUDPSender->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextUDPSender->toPlainText() + "\n";

            file.close();
            log_message("[Log] Screen saved successfully.");
        }
    } else {
        log_message("[Log] Screen is empty.");
    }
}

void MainWindow::on_ButtonUDPListenSave_clicked()
{
    if (ui->TextUDPListen->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextUDPListen->toPlainText() + "\n";

            file.close();
            log_message("[Log] Screen saved successfully.");
        }
    } else {
        log_message("[Log] Screen is empty.");
    }
}

void MainWindow::on_ButtonUDPSendSave_clicked()
{
    if (ui->TextUDPSend->toPlainText() != "") {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All (*.)"));
        if (file_name == "") log_message("[Log] Save screen closed.");
        else {
            QFile file(file_name);

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << ui->TextUDPSend->toPlainText() + "\n";

            file.close();
            log_message("[Log] Screen saved successfully.");
        }
    } else {
        log_message("[Log] Screen is empty.");
    }
}

void MainWindow::on_ButtonLogClear_clicked() { ui->TextLog->clear(); }

void MainWindow::on_ButtonTCPServererClear_clicked() { ui->TextTCPServerer->clear(); }

void MainWindow::on_ButtonTCPClienterClear_clicked() { ui->TextTCPClienter->clear(); }

void MainWindow::on_ButtonTCPClientClear_clicked() { ui->TextTCPClient->clear(); }

void MainWindow::on_ButtonTCPServerClear_clicked() { ui->TextTCPServer->clear(); }

void MainWindow::on_ButtonUDPClear_clicked() { ui->TextUDPListener->clear(); }

void MainWindow::on_ButtonUDPSenderClear_clicked() { ui->TextUDPSender->clear(); }

void MainWindow::on_ButtonUDPListenClear_clicked() { ui->TextUDPListen->clear(); }

void MainWindow::on_ButtonUDPSendClear_clicked() { ui->TextUDPSend->clear(); }

void MainWindow::on_ButtonRefresh_clicked()
{
    ui->BoxInterface->clear();
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    int i = 0;

    for (const QNetworkInterface &interface : interfaces) {
        ui->BoxInterface->addItem(interface.humanReadableName());
        if (ui->BoxInterface->itemText(i) == "Wi-Fi") ui->BoxInterface->setCurrentIndex(i);
        else i += 1;

        for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
            if (entry.ip().toString().startsWith("192.168.")) ui->LabelIpAddress->setText(entry.ip().toString());
        }
    }
}

void MainWindow::on_TextHost_returnPressed() { ui->TextPort->setFocus(); }

void MainWindow::on_TextPort_returnPressed() { on_ButtonConnectionSelect_clicked(); }

void MainWindow::on_ButtonConnectionSelect_clicked()
{
    if (ui->TextPort->text() != "") {
        if (ui->ButtonConnectionSelect->text() == "Select") {
            ui->ButtonConnectionSelect->setText("Drop");
            ui->TextHost->setText(ui->LabelIpAddress->text());

            ui->LabelHost->setEnabled(false);
            ui->LabelPort->setEnabled(false);
            ui->TextHost->setEnabled(false);
            ui->TextPort->setEnabled(false);

            ui->TabConnectionProtocols->setTabEnabled(0, false);
            ui->TabConnectionProtocols->setTabEnabled(1, true);
            ui->TabConnectionProtocols->setTabEnabled(2, true);
            ui->TabConnectionProtocols->setTabEnabled(3, false);
            ui->TabConnectionProtocols->setTabEnabled(4, true);
            ui->TabConnectionProtocols->setTabEnabled(5, true);

            ui->TabConnectionProtocols->setCurrentIndex(1);
            log_message("[Connection] Host: " + ui->TextHost->text() + ", Port: " + ui->TextPort->text() + " selected.");
        } else if (ui->ButtonConnectionSelect->text() == "Drop") {
            ui->ButtonConnectionSelect->setText("Select");
            ui->LabelHost->setEnabled(true);
            ui->LabelPort->setEnabled(true);
            ui->TextHost->setEnabled(true);
            ui->TextPort->setEnabled(true);

            ui->TabConnectionProtocols->setTabEnabled(0, true);
            ui->TabConnectionProtocols->setTabEnabled(1, false);
            ui->TabConnectionProtocols->setTabEnabled(2, false);
            ui->TabConnectionProtocols->setTabEnabled(3, true);
            ui->TabConnectionProtocols->setTabEnabled(4, false);
            ui->TabConnectionProtocols->setTabEnabled(5, false);

            ui->TabConnectionProtocols->setCurrentIndex(0);
            log_message("[Connection] Selection dropped.");
        }
    } else {
        log_message("[Log] IP Address or Port is empty.");
    }
}

void MainWindow::on_ButtonUDPListen_clicked()
{
    if (ui->ButtonUDPListen->text() == "Listen") {
        ui->ButtonUDPListen->setText("Drop");
        ui->TabConnectionProtocols->setTabEnabled(0, false);
        ui->FrameConnection->setEnabled(false);
        ui->TextUDPSenderCommand->setEnabled(true);
        ui->ButtonUDPSenderSend->setEnabled(true);

        // LISTEN PROCESS
        QHostAddress IpAdress(ui->LabelIpAddress->text());
        socket->Bind(IpAdress, 8080);
        connect(socket, &UDPBase::newMessage, this, &MainWindow::onDataReceived);
        log_message("[UDP] Port now listening.");
    } else if ( ui->ButtonUDPListen->text() == "Drop") {
        ui->ButtonUDPListen->setText("Listen");
        ui->TabConnectionProtocols->setTabEnabled(0, true);
        ui->FrameConnection->setEnabled(true);
        ui->TextUDPSenderCommand->setEnabled(false);
        ui->ButtonUDPSenderSend->setEnabled(false);

        // LISTEN PROCESS
        socket->Unbind();
        disconnect(socket, &UDPBase::newMessage, this, &MainWindow::onDataReceived);
        log_message("[UDP] Port no longer listening.");
    }
}

void MainWindow::onDataReceived(QByteArray data, QHostAddress sender, quint16 senderPort)
{
    QString receivedMessage = QString::fromUtf8(data);
    qDebug() << "Received from" << sender.toString() << ":" << senderPort << "->" << receivedMessage;
    ui->TextUDPListener->append(sender.toString().mid(sender.toString().indexOf("192.168.")) + ": " + receivedMessage);
}

void MainWindow::on_ButtonUDPSenderSend_clicked()
{
    ui->TextUDPSender->append(ui->TextUDPSenderCommand->text());
    QByteArray data(ui->TextUDPSenderCommand->text().toUtf8());
    socket->Send(ui->LabelIpAddress->text(), 8080, data);
    ui->TextUDPSenderCommand->clear();
}

void MainWindow::on_TextUDPSenderCommand_returnPressed() { on_ButtonUDPSenderSend_clicked(); }

void MainWindow::on_ButtonUDPListenListen_clicked()
{
    if (ui->ButtonUDPListenListen->text() == "Listen") {
        ui->ButtonUDPListenListen->setText("Drop");

        // LISTEN PROCESS
        QHostAddress IpAdress(ui->TextHost->text());
        socket->Bind(IpAdress, ui->TextPort->text().toInt());
        connect(socket, &UDPBase::newMessage, this, &MainWindow::onDataReceived);
        log_message("[UDP] Port now listening.");
    } else if ( ui->ButtonUDPListenListen->text() == "Drop") {
        ui->ButtonUDPListenListen->setText("Listen");

        // LISTEN PROCESS
        socket->Unbind();
        disconnect(socket, &UDPBase::newMessage, this, &MainWindow::UDPDataReceived);
        log_message("[UDP] Port no longer listening.");
    }
}

void MainWindow::UDPDataReceived(QByteArray data, QHostAddress sender, quint16 senderPort)
{
    QString receivedMessage = QString::fromUtf8(data);
    qDebug() << "Received from" << sender.toString() << ":" << senderPort << "->" << receivedMessage;
    ui->TextUDPListen->append(sender.toString() + ": " + receivedMessage);
}

void MainWindow::on_ButtonUDPSendBind_clicked()
{
    if (ui->ButtonUDPSendBind->text() == "Bind") {
        QHostAddress IpAdress(ui->TextHost->text());
        socket->Bind(IpAdress, ui->TextPort->text().toInt());
        log_message("[UDP] Bind done.");

        ui->TextUDPSendCommand->setEnabled(true);
        ui->ButtonUDPSendSend->setEnabled(true);
        ui->ButtonUDPSendBind->setText("Unbind");
    } else if (ui->ButtonUDPSendBind->text() == "Unbind") {
        socket->Unbind();
        log_message("[UDP] Unbind done.");

        ui->TextUDPSendCommand->setEnabled(false);
        ui->ButtonUDPSendSend->setEnabled(false);
        ui->ButtonUDPSendBind->setText("Bind");
    }
}

void MainWindow::on_ButtonUDPSendSend_clicked()
{
    ui->TextUDPSend->append(ui->TextUDPSendCommand->text());
    QByteArray data(ui->TextUDPSendCommand->text().toUtf8());
    socket->Send(ui->TextHost->text(), ui->TextPort->text().toInt(), data);
    ui->TextUDPSendCommand->clear();
}

void MainWindow::on_TextUDPSendCommand_returnPressed() { on_ButtonUDPSendSend_clicked(); }

void MainWindow::log_message(QString msg) { ui->TextLog->append(msg); }

void MainWindow::on_ButtonTCPServererStart_clicked()
{
    if (ui->ButtonTCPServererStart->text() == "Start Server") {
        ui->ButtonTCPServererStart->setText("Stop Server");
        ui->TabConnectionProtocols->setTabEnabled(3, false);
        ui->FrameConnection->setEnabled(false);
        ui->ButtonTCPClienterConnect->setEnabled(true);
        ui->TextTCPServererCommand->setEnabled(true);
        ui->ButtonTCPServererSend->setEnabled(true);

        // SERVER PROCESS
        QHostAddress IpAdress(ui->LabelIpAddress->text());
        tcpServer->StartServer(IpAdress, 8080);
        connect(tcpServer, &TCPServer::newMessage, this, &MainWindow::onDataReceivedTcp);
        log_message("[TCP] Server Started.");
    } else if (ui->ButtonTCPServererStart->text() == "Stop Server") {
        ui->ButtonTCPServererStart->setText("Start Server");
        ui->TabConnectionProtocols->setTabEnabled(3, true);
        ui->FrameConnection->setEnabled(true);
        ui->ButtonTCPClienterConnect->setEnabled(false);
        ui->TextTCPClienterCommand->setEnabled(false);
        ui->ButtonTCPClienterSend->setEnabled(false);
        ui->TextTCPServererCommand->setEnabled(false);
        ui->ButtonTCPServererSend->setEnabled(false);

        if (ui->ButtonTCPClienterConnect->text() == "Disconnect") on_ButtonTCPClienterConnect_clicked();
        // SERVER PROCESS
        tcpServer->StopServer();
        disconnect(tcpServer, &TCPServer::newMessage, this, &MainWindow::onDataReceivedTcp);
        log_message("[TCP] Server Stopped.");
    }
}

void MainWindow::onDataReceivedTcp(const QString &from, const QString &message)
{
    qDebug() << "Server Received from" << from << "->" << message;
    ui->TextTCPServerer->append(from + ": " + message);
}

void MainWindow::onDataReceivedTcpClient(const QString &from, const QString &message)
{
    qDebug() << "Client Received from" << from << "->" << message;
    ui->TextTCPClienter->append(from + ": " + message);
}

void MainWindow::on_ButtonTCPClienterConnect_clicked()
{
    if (ui->ButtonTCPClienterConnect->text() == "Connect") {
        ui->ButtonTCPClienterConnect->setText("Disconnect");
        ui->TextTCPClienterCommand->setEnabled(true);
        ui->ButtonTCPClienterSend->setEnabled(true);

        QHostAddress IpAdress(ui->LabelIpAddress->text());
        tcpClient->Connect(IpAdress, 8080);
        connect(tcpClient, &TCPClient::newMessage, this, &MainWindow::onDataReceivedTcpClient);
        log_message("[TCP] Connected.");
    } else if (ui->ButtonTCPClienterConnect->text() == "Disconnect") {
        ui->ButtonTCPClienterConnect->setText("Connect");
        ui->TextTCPClienterCommand->setEnabled(false);
        ui->ButtonTCPClienterSend->setEnabled(false);

        tcpClient->Disconnect();
        disconnect(tcpClient, &TCPClient::newMessage, this, &MainWindow::onDataReceivedTcpClient);
        log_message("[TCP] Disconnected.");
    }
}

void MainWindow::on_ButtonTCPClienterSend_clicked()
{
    if (ui->TextTCPClienterCommand->text() != "") {
        tcpClient->Send(ui->TextTCPClienterCommand->text());
        ui->TextTCPClienter->append("me ->" + ui->TextTCPClienterCommand->text());
        ui->TextTCPClienterCommand->clear();
    } else { log_message("[TCP Client] There is a whole gap in command."); }
}

void MainWindow::on_TextTCPClienterCommand_returnPressed() { on_ButtonTCPClienterSend_clicked(); }

void MainWindow::on_ButtonTCPServererSend_clicked()
{
    if (ui->TextTCPServererCommand->text() != "") {
        tcpServer->Broadcast(ui->TextTCPServererCommand->text());
        ui->TextTCPServerer->append("server ->" + ui->TextTCPServererCommand->text());
        ui->TextTCPServererCommand->clear();
    } else { log_message("[TCP Server] There is a whole gap in command."); }
}

void MainWindow::on_TextTCPServererCommand_returnPressed() { on_ButtonTCPServererSend_clicked();}

void MainWindow::on_ButtonTCPServerStart_clicked()
{
    if (ui->ButtonTCPServerStart->text() == "Start") {
        ui->ButtonTCPServerStart->setText("Stop");
        ui->TextTCPServerCommand->setEnabled(true);
        ui->ButtonTCPServerSend->setEnabled(true);
        ui->TabConnectionProtocols->setTabEnabled(2, false);
        ui->TabConnectionProtocols->setTabEnabled(4, false);
        ui->TabConnectionProtocols->setTabEnabled(5, false);

        // SERVER PROCESS
        QHostAddress IpAdress(ui->LabelIpAddress->text());
        tcpServer->StartServer(IpAdress, ui->TextPort->text().toInt());
        connect(tcpServer, &TCPServer::newMessage, this, &MainWindow::TcpServerDataReceived);
        log_message("[TCP] Server Started.");
    } else if (ui->ButtonTCPServerStart->text() == "Stop") {
        ui->ButtonTCPServerStart->setText("Start");
        ui->TextTCPServerCommand->setEnabled(false);
        ui->ButtonTCPServerSend->setEnabled(false);
        ui->TabConnectionProtocols->setTabEnabled(2, true);
        ui->TabConnectionProtocols->setTabEnabled(4, true);
        ui->TabConnectionProtocols->setTabEnabled(5, true);

        // SERVER PROCESS
        tcpServer->StopServer();
        disconnect(tcpServer, &TCPServer::newMessage, this, &MainWindow::TcpServerDataReceived);
        log_message("[TCP] Server Stopped.");
    }
}

void MainWindow::TcpServerDataReceived(const QString &from, const QString &message)
{
    qDebug() << "Server Received from" << from << "->" << message;
    ui->TextTCPServer->append(from + ": " + message);
}

void MainWindow::on_ButtonTCPServerSend_clicked()
{
    if (ui->TextTCPServerCommand->text() != "") {
        tcpServer->Broadcast(ui->TextTCPServerCommand->text());
        ui->TextTCPServer->append("server ->" + ui->TextTCPServerCommand->text());
        ui->TextTCPServerCommand->clear();
    } else { log_message("[TCP Server] There is a whole gap in command."); }
}

void MainWindow::on_TextTCPServerCommand_returnPressed() { on_ButtonTCPServerSend_clicked(); }

void MainWindow::on_ButtonTCPClientConnect_clicked()
{
    if (ui->ButtonTCPClientConnect->text() == "Connect") {
        ui->ButtonTCPClientConnect->setText("Disconnect");
        ui->TextTCPClientCommand->setEnabled(true);
        ui->ButtonTCPClientSend->setEnabled(true);
        ui->TabConnectionProtocols->setTabEnabled(1, false);
        ui->TabConnectionProtocols->setTabEnabled(4, false);
        ui->TabConnectionProtocols->setTabEnabled(5, false);

        QHostAddress IpAdress(ui->LabelIpAddress->text());
        tcpClient->Connect(IpAdress, ui->TextPort->text().toInt());
        connect(tcpClient, &TCPClient::newMessage, this, &MainWindow::TcpClientDataReceived);
        log_message("[TCP] Connected.");
    } else if (ui->ButtonTCPClientConnect->text() == "Disconnect") {
        ui->ButtonTCPClientConnect->setText("Connect");
        ui->TextTCPClientCommand->setEnabled(false);
        ui->ButtonTCPClientSend->setEnabled(false);
        ui->TabConnectionProtocols->setTabEnabled(1, true);
        ui->TabConnectionProtocols->setTabEnabled(4, true);
        ui->TabConnectionProtocols->setTabEnabled(5, true);

        tcpClient->Disconnect();
        disconnect(tcpClient, &TCPClient::newMessage, this, &MainWindow::TcpClientDataReceived);
        log_message("[TCP] Disconnected.");
    }
}

void MainWindow::TcpClientDataReceived(const QString &from, const QString &message)
{
    qDebug() << "Received from" << from << "->" << message;
    ui->TextTCPClient->append(from + ": " + message);
}

void MainWindow::on_ButtonTCPClientSend_clicked()
{
    if (ui->TextTCPClientCommand->text() != "") {
        tcpClient->Send(ui->TextTCPClientCommand->text());
        ui->TextTCPClient->append("me ->" + ui->TextTCPClientCommand->text());
        ui->TextTCPClientCommand->clear();
    } else { log_message("[TCP Client] There is a whole gap in command."); }
}

void MainWindow::on_TextTCPClientCommand_returnPressed() { on_ButtonTCPClientSend_clicked(); }
