#ifndef RESIZEABLEPICTURE_H
#define RESIZEABLEPICTURE_H

#include <QObject>
#include <QPixmap>
#include <QLabel>

class ResizeablePicture : public QLabel
{
    Q_OBJECT

public:
    ResizeablePicture(QWidget* parent);
    ResizeablePicture(QWidget* parent, const QPixmap& pixmap);
    ResizeablePicture(QWidget* parent, const QPixmap& pixmap, QSize size);
    ~ResizeablePicture();
    void setPixmap(const QPixmap& pixmap);
    void setPixmap(const QPixmap& pixmap, QSize size);
    void resize(QSize size, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio);

private:
    QPixmap picture;
};

#endif // RESIZEABLEPICTURE_H
