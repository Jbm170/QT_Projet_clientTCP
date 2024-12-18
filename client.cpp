#include "client.h"
#include <QtNetwork/QHostAddress>

// Constructeur de la classe Client
Client::Client(QObject *parent) : QObject(parent)
{
    qDebug() << QString::fromUtf8("Instancie un objet QTcpSocket");
    tcpSocket = new QTcpSocket(this); // 1. Création de la socket TCP
    qDebug() << QString::fromUtf8("Creation de la socket et visualisation de l etat de la socket :") << tcpSocket->state();

    // Connexion des signaux aux slots appropriés
    connect(tcpSocket, &QTcpSocket::connected, this, &Client::estConnectee);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Client::estDeconnectee);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::recevoir);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), this, &Client::gestionErreur);
}

// Destructeur de la classe Client
Client::~Client()
{
    qDebug() << QString::fromUtf8("Ferme la socket");
    tcpSocket->close(); // Fermeture de la socket
}

// Méthode pour démarrer la connexion au serveur
void Client::demarrer()
{
    qDebug() << QString::fromUtf8("Connexion au serveur");
    tcpSocket->connectToHost(QHostAddress::LocalHost, PORT_SERVEUR); // 2. Connexion au serveur local sur le port spécifié
    qDebug() << QString::fromUtf8("État de la connexion de la socket :") << tcpSocket->state();
}

// Slot appelé lorsque la connexion au serveur est établie
void Client::estConnectee()
{
    qDebug() << QString::fromUtf8("Le client est bien connecte au serveur ayant pour adresse :") << this->tcpSocket->peerAddress().toString() << "\n";
    qDebug() << QString::fromUtf8("et pour port :") << this->tcpSocket->peerPort() << "\n";
    this->envoyer("Bonjour a vous !"); // Envoi d'un message de bienvenue au serveur
}

// Slot appelé lorsque la connexion au serveur est fermée
void Client::estDeconnectee()
{
    qDebug() << QString::fromUtf8("Le client est bien deconnecte");
}

// Slot appelé lorsqu'une erreur de socket se produit
void Client::gestionErreur(QAbstractSocket::SocketError erreur)
{
    qDebug() << QString::fromUtf8("Message d'erreur :") << tcpSocket->errorString();
}

// Slot appelé lorsque des données sont reçues du serveur
void Client::recevoir()
{
    qint64 maxSize = 64; // Taille maximale des données à lire
    QByteArray data = tcpSocket->read(maxSize); // Lecture des données
    qDebug() << "Des données ont été reçues : " << data << "\n";
}

// Méthode pour envoyer des données au serveur
void Client::envoyer(QByteArray message)
{
    qint64 ecrits = -1;
    // Envoi du message
    ecrits = tcpSocket->write(message);

    switch(ecrits)
    {
    case -1:
        qDebug() << QString::fromUtf8("Erreur lors de l’envoi !"); // En cas d'erreur d'envoi
        break;
    default:
        qDebug() << QString::fromUtf8("Message envoyé : ") << message; // Affichage du message envoyé
        qDebug() << QString::fromUtf8("Octets envoyés : ") << ecrits; // Affichage du nombre d'octets envoyés
        qDebug() << QString::fromUtf8("Message envoyé avec succès !"); // Confirmation de l'envoi réussi
    }
}
