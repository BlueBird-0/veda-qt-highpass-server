#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
class QNetworkAccessManager;
class QNetworkReply;
class HttpClient: public QObject
{
    Q_OBJECT
public:
    HttpClient(QObject *parent);
    void addCamera(const QString &cameraName, const QString &rtspUrl);
    void loadCameras();


private:
      QNetworkAccessManager* manager;

private slots:
       void onCameraAdded(QNetworkReply *reply);
       void onCamerasLoaded(QNetworkReply *reply);
       void onReplyFinished(QNetworkReply* reply);
};

#endif // HTTPCLIENT_H
