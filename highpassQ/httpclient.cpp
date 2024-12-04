#include "httpclient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>

HttpClient::HttpClient(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &HttpClient::onReplyFinished);
}


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QDebug>
//void createCamera(const QString& cameraName, const QString& rtspUrl) {

//}


void HttpClient::addCamera(const QString &cameraName, const QString &rtspUrl)
{
    // 서버 URL 설정
    QUrl serverUrl("http://192.168.0.26:8080/camera"); // 서버의 REST API URL
    QNetworkRequest request(serverUrl);
    // 헤더 설정
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // JSON 데이터 생성
    QJsonObject jsonObj;
    jsonObj["Camera_Name"] = cameraName;
    jsonObj["Camera_RTSP_URL"] = rtspUrl;
    QJsonDocument jsonDoc(jsonObj);
    // POST 요청 전송
    manager->post(request, jsonDoc.toJson());
    qDebug() << "POST Request Sent: " << jsonDoc.toJson();

}
void HttpClient::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        // 성공 시 응답 처리
        QByteArray responseData = reply->readAll();
        qDebug() << "Response Received:" << responseData;
    } else {
        // 오류 처리
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater(); // 리소스 해제
}
void HttpClient::loadCameras()
{
    QUrl url("http://192.168.0.26:8080/cameras");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    //connect(reply,  SIGNAL(finished(QNetworkReply *reply)), this, SLOT(onCamerasLoaded(QNetworkReply *reply)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {onCamerasLoaded(reply);});
}
void HttpClient::onCameraAdded(QNetworkReply *reply)
{
//    if (reply->error() == QNetworkReply::NoError) {
//        qDebug() << "카메라 추가 성공: " << reply->readAll();
//    } else {
//         qDebug() << "카메라 추가 실패: " << reply->readAll();
//        qDebug() << "카메라 추가 실패: " << reply->errorString();
//    }
//    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
         // 성공 시 응답 처리
         QByteArray responseData = reply->readAll();
         qDebug() << "Response Received:" << responseData;
     } else {
         // 오류 처리
         qDebug() << "Error:" << reply->errorString();
     }
     reply->deleteLater(); // 리소스 해제
}
void HttpClient::onCamerasLoaded(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        qDebug()<<"load start??";
        QByteArray responseData = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        qDebug()<<"responseData: "<<responseData;
        if (doc.isArray()) {
            qDebug()<<"here is If !!";
            QJsonArray cameraArray = doc.array();
            for (const QJsonValue value : cameraArray) {
                QJsonObject cameraObject = value.toObject();
                qDebug() << "Camera ID:" << cameraObject["Camera_ID"].toInt()
                         << "Camera Name:" << cameraObject["Camera_Name"].toString()
                         << "RTSP URL:" << cameraObject["Camera_RTSP_URL"].toString();
            }
//             for(int i = 0; i<cameraArray.size();i++)
//             {
//                 qDebug()<<QString("cameraArray[%1]").arg(i);
//             }
        }
    } else {
        qDebug() << "카메라 목록 로드 실패: " << reply->errorString();
    }
    reply->deleteLater();

//    if (reply->error() == QNetworkReply::NoError) {
//           qDebug() << "Load started.";
//           QByteArray responseData = reply->readAll();
//           qDebug() << "Response Data:" << responseData;

//           QJsonParseError parseError;
//           QJsonDocument doc = QJsonDocument::fromJson(responseData, &parseError);
//           if (parseError.error != QJsonParseError::NoError) {
//               qWarning() << "JSON Parse Error:" << parseError.errorString();
//               return;
//           }

//           if (doc.isArray()) {
//               QJsonArray cameraArray = doc.array();
//               qDebug() << "Camera Array Size:" << cameraArray.size();
//               for (int i = 0; i < cameraArray.size(); ++i) {
//                   qDebug() << QString("cameraArray[%1]").arg(i);
//               }
//           } else if (doc.isObject()) {
//               QJsonObject obj = doc.object();
//               if (obj.contains("cameraArray") && obj["cameraArray"].isArray()) {
//                   QJsonArray cameraArray = obj["cameraArray"].toArray();
//                   qDebug() << "Camera Array Size:" << cameraArray.size();
//                   for (int i = 0; i < cameraArray.size(); ++i) {
//                       qDebug() << QString("cameraArray[%1]").arg(i);
//                   }
//               } else {
//                   qDebug() << "'cameraArray' not found or it's not an array.";
//               }
//           } else {
//               qDebug() << "Unexpected JSON structure.";
//           }
//       } else {
//           qDebug() << "Camera list loading failed: " << reply->errorString();
//       }
//       reply->deleteLater();
}
