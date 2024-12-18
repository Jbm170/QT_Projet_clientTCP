#include "client.h"
#include <QtNetwork/QHostAddress>

Client::Client(QObject *parent) : QObject(parent)
{
    qDebug() << QString::fromUtf8("Instancie un objet QTcpSocket");
    tcpSocket = new QTcpSocket(this); // 1.
    qDebug() << QString::fromUtf8("Creation de la socket et visualisation de l etat de la socket :") << tcpSocket->state();

    // Connexion des signaux aux slots
    connect(tcpSocket, &QTcpSocket::connected, this, &Client::estConnectee);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Client::estDeconnectee);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::recevoir);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), this, &Client::gestionErreur);
}

Client::~Client()
{
    qDebug() << QString::fromUtf8("Ferme la socket");
    tcpSocket->close();
}

void Client::demarrer()
{
    qDebug() << QString::fromUtf8("Connexion au serveur");
    tcpSocket->connectToHost(QHostAddress::LocalHost, PORT_SERVEUR); // 2. (ici le serveur sera localhost)
    qDebug() << QString::fromUtf8("État de la connexion de la socket :") << tcpSocket->state();
}

void Client::estConnectee()
{
    qDebug() << QString::fromUtf8("Le client est bien connecte au serveur ayant pour adresse :") << this->tcpSocket->peerAddress().toString() << "\n";
    qDebug() << QString::fromUtf8("et pour port :") << this->tcpSocket->peerPort() << "\n";
    this->envoyer("Bonjour a vous !");
}

void Client::estDeconnectee()
{
    qDebug() << QString::fromUtf8("Le client est bien deconnecte");
}

void Client::gestionErreur(QAbstractSocket::SocketError erreur)
{
    qDebug() << QString::fromUtf8("Message d'erreur :") << tcpSocket->errorString();
}

void Client::recevoir()
{
    qint64 maxSize = 64;
    QByteArray data = tcpSocket->read(maxSize);
    qDebug() << "Des données ont été reçues : " << data << "\n";
}

void Client::envoyer(QByteArray message)
{
    qint64 ecrits = -1;
    // Envoi du message
    ecrits = tcpSocket->write(message);

    switch(ecrits)
    {
    case -1:
        qDebug() << QString::fromUtf8("Erreur lors de l’envoi !");
        break;
    default:
        qDebug() << QString::fromUtf8("Message envoyé : ") << message;
        qDebug() << QString::fromUtf8("Octets envoyés : ") << ecrits;
        qDebug() << QString::fromUtf8("Message envoyé avec succès !");
    }
}
