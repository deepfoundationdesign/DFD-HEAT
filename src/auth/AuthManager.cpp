#include "auth/AuthManager.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QUrl>
#include <QUrlQuery>
#include <QTimer>

AuthManager::AuthManager(QObject *parent)
    : QObject(parent)
    , m_authenticated(false)
    , m_licenseType(Free)
    , m_networkManager(std::make_unique<QNetworkAccessManager>(this))
{
}

AuthManager::~AuthManager() = default;

void AuthManager::setKeycloakConfig(const QString &realm, const QString &clientId, const QString &serverUrl)
{
    m_keycloakRealm = realm;
    m_keycloakClientId = clientId;
    m_keycloakServerUrl = serverUrl;
}

void AuthManager::setStripeConfig(const QString &publicKey)
{
    m_stripePublicKey = publicKey;
}

void AuthManager::authenticate()
{
    if (m_keycloakServerUrl.isEmpty()) {
        emit authError("Authentication not configured");
        return;
    }

    // In production, implement OAuth2/OIDC flow with Keycloak
    // For now, simulate authentication
    QTimer::singleShot(1000, this, [this]() {
        m_authenticated = true;
        m_userEmail = "user@example.com";
        m_userId = "user123";
        m_accessToken = "mock_access_token";
        m_refreshToken = "mock_refresh_token";
        m_licenseType = Professional;

        emit authenticationChanged(true);
        emit licenseChanged(m_licenseType);

        // Check subscription status
        checkSubscription();
    });
}

void AuthManager::logout()
{
    m_authenticated = false;
    m_userEmail.clear();
    m_userId.clear();
    m_accessToken.clear();
    m_refreshToken.clear();
    m_licenseType = Free;

    emit authenticationChanged(false);
    emit licenseChanged(m_licenseType);
}

void AuthManager::refreshToken()
{
    if (m_refreshToken.isEmpty()) {
        emit authError("No refresh token available");
        return;
    }

    // In production, implement token refresh with Keycloak
    QUrl url(QString("%1/realms/%2/protocol/openid-connect/token")
             .arg(m_keycloakServerUrl).arg(m_keycloakRealm));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("grant_type", "refresh_token");
    params.addQueryItem("refresh_token", m_refreshToken);
    params.addQueryItem("client_id", m_keycloakClientId);

    QNetworkReply *reply = m_networkManager->post(request, params.toString().toUtf8());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            handleTokenRefresh(reply->readAll());
        } else {
            emit authError("Token refresh failed");
        }
        reply->deleteLater();
    });
}

void AuthManager::checkSubscription()
{
    if (!m_authenticated || m_userId.isEmpty()) {
        m_licenseType = Free;
        emit licenseChanged(m_licenseType);
        return;
    }

    // In production, check with Stripe Customer Portal API
    // For now, simulate subscription check
    QTimer::singleShot(500, this, [this]() {
        // Mock subscription status
        m_licenseType = Professional;
        emit licenseChanged(m_licenseType);
    });
}

void AuthManager::handleAuthResponse(const QByteArray &response)
{
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonObject obj = doc.object();

    m_accessToken = obj["access_token"].toString();
    m_refreshToken = obj["refresh_token"].toString();

    if (!m_accessToken.isEmpty()) {
        m_authenticated = true;
        emit authenticationChanged(true);
    }
}

void AuthManager::handleTokenRefresh(const QByteArray &response)
{
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonObject obj = doc.object();

    m_accessToken = obj["access_token"].toString();

    if (obj.contains("refresh_token")) {
        m_refreshToken = obj["refresh_token"].toString();
    }
}