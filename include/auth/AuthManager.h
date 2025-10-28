#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <memory>

class AuthManager : public QObject
{
    Q_OBJECT

public:
    enum AuthProvider {
        None,
        Keycloak,
        Auth0,
        Custom
    };

    enum LicenseType {
        Free,
        Basic,
        Professional,
        Enterprise
    };

    explicit AuthManager(QObject *parent = nullptr);
    ~AuthManager();

    bool isAuthenticated() const { return m_authenticated; }
    QString userEmail() const { return m_userEmail; }
    LicenseType licenseType() const { return m_licenseType; }

    void setKeycloakConfig(const QString &realm, const QString &clientId, const QString &serverUrl);
    void setStripeConfig(const QString &publicKey);

public slots:
    void authenticate();
    void logout();
    void refreshToken();
    void checkSubscription();

signals:
    void authenticationChanged(bool authenticated);
    void licenseChanged(LicenseType type);
    void authError(const QString &error);

private:
    void handleAuthResponse(const QByteArray &response);
    void handleTokenRefresh(const QByteArray &response);

    bool m_authenticated;
    QString m_userEmail;
    QString m_userId;
    QString m_accessToken;
    QString m_refreshToken;
    LicenseType m_licenseType;

    // Keycloak config
    QString m_keycloakRealm;
    QString m_keycloakClientId;
    QString m_keycloakServerUrl;

    // Stripe config
    QString m_stripePublicKey;

    std::unique_ptr<QNetworkAccessManager> m_networkManager;
};

#endif // AUTHMANAGER_H