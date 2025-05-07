#pragma once
#include <QWidget>
#include <QRubberBand>
#include <QPixmap>
#include <QScreen>
#include <QMouseEvent>
#include <QShowEvent>
#include <QPainter>

class ScreenShotWidget : public QWidget {
    Q_OBJECT
public:
    ScreenShotWidget(QWidget *parent = nullptr);
    QRect getSelectedRect() const;
    QPixmap getScreenPixmap() const;

signals:
    void regionSelected();

protected:
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint origin;
    QRect selectedRect;
    QRubberBand *rubberBand = nullptr;
    QPixmap screenPixmap;
};
