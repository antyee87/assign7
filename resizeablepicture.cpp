#include "resizeablepicture.h"

#include <QLabel>

ResizeablePicture::ResizeablePicture(QWidget* parent)
    : QLabel(parent) {
    picture = QPixmap();
}

ResizeablePicture::ResizeablePicture(QWidget* parent, const QPixmap& pixmap)
    : QLabel(parent){
    picture = pixmap;
    QLabel::setPixmap(pixmap);
    setFixedSize(pixmap.size());
}

ResizeablePicture::ResizeablePicture(QWidget* parent, const QPixmap& pixmap, QSize size)
    : QLabel(parent){
    picture = pixmap;
    QLabel::setPixmap(pixmap);
    setFixedSize(size);
}

void ResizeablePicture::setPixmap(const QPixmap& pixmap) {
    picture = pixmap;
    QLabel::setPixmap(pixmap);
    setFixedSize(pixmap.size());
}

void ResizeablePicture::setPixmap(const QPixmap& pixmap, QSize size) {
    picture = pixmap;
    QLabel::setPixmap(pixmap);
    setFixedSize(size);
}

void ResizeablePicture::resize(QSize size, Qt::AspectRatioMode aspectRatioMode) {
    if (!picture) return;
    QPixmap scaled = picture.scaled(size, aspectRatioMode, Qt::SmoothTransformation);
    setFixedSize(scaled.size());
    setPixmap(scaled);
}

ResizeablePicture::~ResizeablePicture(){

}
