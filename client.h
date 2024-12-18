#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#define PORT_SERVEUR 8000 // Définition du port du serveur

// Déclaration de la classe Client
class Client : public QObject
{
    Q_OBJECT
public:
    // Constructeur explicite, avec un QObject parent par défaut
    explicit Client(QObject *parent = 0);
    // Destructeur
    ~Client();

    // Méthode pour démarrer la connexion au serveur
    void demarrer();

private:
    QTcpSocket *tcpSocket; // Pointeur vers un objet QTcpSocket pour gérer la connexion au serveur

signals:
    // Signaux (ajoutez ici si nécessaire)

public slots:
    // Slot appelé lorsque le client se connecte au serveur
    void estConnectee ();
    // Slot appelé lorsque le client se déconnecte du serveur
    void estDeconnectee();
    // Slot appelé lorsqu'une erreur de socket se produit
    void gestionErreur(QAbstractSocket::SocketError);
    // Slot appelé lorsque des données sont reçues du serveur
    void recevoir();
    // Méthode pour envoyer des données au serveur
    void envoyer(QByteArray);
};

#endif // CLIENT_H
