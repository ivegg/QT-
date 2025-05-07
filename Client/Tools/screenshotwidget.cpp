#include "screenshotwidget.h"
#include <QGuiApplication>

ScreenShotWidget::ScreenShotWidget(QWidget *parent)
    : QWidget(parent), rubberBand(nullptr) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowFullScreen);
    setAttribute(Qt::WA_TranslucentBackground);
    setCursor(Qt::CrossCursor);
}

QRect ScreenShotWidget::getSelectedRect() const { return selectedRect; }
QPixmap ScreenShotWidget::getScreenPixmap() const { return screenPixmap; }

void ScreenShotWidget::showEvent(QShowEvent *event) {
    QScreen *screen = QGuiApplication::primaryScreen();
    screenPixmap = screen->grabWindow(0);
    QWidget::showEvent(event);
}
void ScreenShotWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, screenPixmap);
    painter.setBrush(QColor(0, 0, 0, 100));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());
    if (!selectedRect.isNull()) {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::red, 2));
        painter.drawRect(selectedRect);
    }
    QWidget::paintEvent(event);
}
void ScreenShotWidget::mousePressEvent(QMouseEvent *event) {
    origin = event->pos();
    if (!rubberBand)
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
}
void ScreenShotWidget::mouseMoveEvent(QMouseEvent *event) {
    if (rubberBand)
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    selectedRect = QRect(origin, event->pos()).normalized();
    update();
}
void ScreenShotWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (rubberBand)
        rubberBand->hide();
    selectedRect = QRect(origin, event->pos()).normalized();
    update();
    emit regionSelected();
    close();
}
