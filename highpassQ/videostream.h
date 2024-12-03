#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <QWidget>
#include <QMap>
class QTextEdit;
class rtpClient;
class stream_ui;

namespace Ui {
class videoStream;
}

class videoStream : public QWidget
{
    Q_OBJECT

public:
    explicit videoStream(QWidget *parent = nullptr);
    ~videoStream();

private slots:

    void slot_ffmpeg_debug(QString error,rtpClient* textedit_key);
    void showContextMenu(const QPoint& pos);
    void addNewTab();
    void slot_tab_del(stream_ui*);
private:
    Ui::videoStream *ui;
    QMap <rtpClient*,QTextEdit*> map_textedit;
    QMap <stream_ui*, QTextEdit*> map_stream_ui;
signals:
    //void signal_clikQuit();
   // void send_url(QString url);
};

#endif // VIDEOSTREAM_H
