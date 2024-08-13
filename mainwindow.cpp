#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * Qt에서 드래그 & 드롭 기능을 사용하기 위해서는
     * 우선 AcceptDrops 옵션이 "true"로 설정되어 있어야 한다.
     * AcceptDrops 옵션이 켜져 있어야 dragEnterEvent, dropEvent 순으로 처리가 가능하다.
     *
     * 이 예제에서는 setAcceptDrops() API 함수를 호출하여 Dialog에 드래그 & 드롭 기능을 Enable하도록 하였음.
    */
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    qDebug() << Q_FUNC_INFO;
    event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragEnterEvent* event)
{
    qDebug() << Q_FUNC_INFO;
    event->acceptProposedAction();
}

/*
 * 사진 파일을 Mouse 로 끌어다 놓으면 표시가 된다.
 *
 * NOTE:
 *	QT에서 이미지를 로드하여 화면에 출력하는 	순서:
 *	QImage로 이미지를 불러온다 -> QPixmap에 옮긴다 -> QLabel에서 QPixmap를 불러와서 화면에 출력한다.
*/
void MainWindow::dropEvent(QDropEvent* event)
{
    qDebug() << Q_FUNC_INFO;
    const QMimeData* mimeData = event->mimeData();
    QPixmap pixmap;
    ui->label->clear();

    if (mimeData->hasUrls()) {
        QList<QUrl> paths = mimeData->urls();
        foreach(QUrl path, paths) {
            ui->lineEdit->setText(path.toLocalFile());
            pixmap.load(path.toLocalFile());

            if (!pixmap.isNull()) {
                ui->label->setPixmap(pixmap);
            }
        }
    }
}
