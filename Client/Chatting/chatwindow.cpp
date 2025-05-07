#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QScrollBar>
#include <QBuffer>
#include <QImageReader>
#include "stringtool.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QUrl>

ChatWindow::ChatWindow(const FriendInfo& info,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow),
    m_info(info)
{
    ui->setupUi(this);
    m_type = 0;
    m_name = info.name;
    m_account = info.account;
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setLineWrapMode(QTextBrowser::WidgetWidth);
    QFont defaultFont = ui->textEdit->font();
    defaultFont.setPointSize(13); // 设置字体大小，根据您的需要调整大小
    ui->textEdit->setFont(defaultFont);
    connect(ui->textEdit, &QTextBrowser::anchorClicked, this, &ChatWindow::onFileAnchorClicked);
    ui->textEdit->setOpenLinks(false);
}

ChatWindow::ChatWindow(const GroupInfo& info, QWidget *parent):
        QWidget(parent),
        ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    m_groupInfo = info;
    m_type = 1;
    m_account = info.groupAccount;
    m_name = info.groupName;
    //ui->textEdit->setPlainText(QString("System :  you are chatting with %1\n").arg(m_info->name));
    connect(ui->textEdit, &QTextBrowser::anchorClicked, this, &ChatWindow::onFileAnchorClicked);
    ui->textEdit->setOpenLinks(false);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

//flag:0 self 1 other
void ChatWindow::pushMsg(const QString& msg, int flag)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);

    QTextBlockFormat blockFormat = cursor.blockFormat();

    QTextCharFormat blueFormat;
    if(flag == 0)   //自己的消息
    {
        blueFormat.setForeground(Qt::red);
        //ui->textEdit->setAlignment(Qt::AlignLeft);
        blockFormat.setAlignment(Qt::AlignRight);
    }
    else if(flag == 1)//别人的消息
    {
        blueFormat.setForeground(Qt::blue);
        blockFormat.setAlignment(Qt::AlignLeft);
    }

    cursor.setBlockFormat(blockFormat);
    cursor.insertText(msg,blueFormat);
    QScrollBar*bar = ui->textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}

#define textBrowser ui->textEdit
// 发送文本消息
void ChatWindow::sendMessage(const QString &text, int flag) {
    // 设置textBrowser光标到最后
    QTextCursor cursor = textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    textBrowser->setTextCursor(cursor);

    QString processedText = text.toHtmlEscaped();
    processedText.replace("\n", "<br>");

    QString alignment = flag == 1 ? "left" : "right";
    QString bubble = QString("<table style='background-color: #95EC69; margin: 10px; display: inline-table; text-align: %1; border-collapse: separate; border-spacing: 0;'>"
                             "<tr>"
                             "<td style='border-radius: 20px; padding: 6px;'>%2</td>"
                             "</tr>"
                             "</table>")
            .arg(alignment, processedText);

    textBrowser->insertHtml(bubble);
    textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum()); // 自动滚动到底部
    qDebug() << "send message";
}

// 发送图片消息
void ChatWindow::sendImage(const QString &imagePath,int flag) {
    //设置textBrowser光标到最后
    QTextCursor cursor = textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    textBrowser->setTextCursor(cursor);

    QImage image(imagePath);
    int maxWidth = 100;
    int maxHeight = 100;

    // 计算适当的宽度和高度，以保持图片的纵横比
    int newWidth = qMin(image.width(), maxWidth);
    int newHeight = newWidth * image.height() / image.width();

    if (newHeight > maxHeight) {
        newHeight = maxHeight;
        newWidth = newHeight * image.width() / image.height();
    }
    QString alignment = flag == 1?"left":"right";
    QString imageHtml = QString("<img src='%1' width='%2' height='%3' style='float: %4;' /><br style='clear: both;'>")
            .arg(imagePath).arg(newWidth).arg(newHeight).arg(alignment);
    textBrowser->insertHtml(imageHtml);
    textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum()); // 自动滚动到底部
    qDebug() << "send image";
}

void ChatWindow::sendFile(const QString &fileName, const QString &filePath,int flag) {
    QString alignment = flag == 1?"left":"right";
    QString fileHtml = QString("<a href='%1' style='text-decoration: none; float: %2;'>"
                               "<div style='background-color: #e0e0e0; border-radius: 10px; padding: 5px; margin: 5px; display: inline-block;'>"
                               "%3</div>"
                               "</a>"
                               "<br style='clear: both;'>")
            .arg(filePath,alignment,fileName);
    textBrowser->insertHtml(fileHtml);
    textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum()); // 自动滚动到底部
}

void ChatWindow::sendImages(const QList<QString>& base64Images, int flag) {
    for (const QString& base64Image : base64Images) {
        // 先插入时间戳（如果需要，可以传入时间戳字符串）
        // pushMsg("2025-05-07 23:23:13", flag); // 由外部调用保证

        // 插入一个空行，确保图片和时间戳分开
        textBrowser->append("");

        QByteArray imageData = QByteArray::fromBase64(base64Image.toLatin1());
        QImage image;
        image.loadFromData(imageData);
        // 保存原始图像的 Base64 编码
        QString originalBase64Image = "data:image/png;base64," + base64Image;
        // 创建缩略图
        int originalWidth = image.width();
        int originalHeight = image.height();
        int maxSize = 150;
        if (originalWidth > maxSize || originalHeight > maxSize) {
            float aspectRatio = static_cast<float>(originalWidth) / static_cast<float>(originalHeight);
            int newWidth, newHeight;
            if (aspectRatio >= 1) {
                newWidth = maxSize;
                newHeight = static_cast<int>((float)maxSize / aspectRatio);
            } else {
                newHeight = maxSize;
                newWidth = static_cast<int>((float)maxSize * aspectRatio);
            }
            image = image.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::FastTransformation);
        }
        QPixmap pixmap = QPixmap::fromImage(image);
        QTextImageFormat imageFormat;
        imageFormat.setWidth(pixmap.width());
        imageFormat.setHeight(pixmap.height());
        imageFormat.setName("data:image/png;base64," + base64Image);
        imageFormat.setProperty(QTextFormat::UserProperty, originalBase64Image);
        QTextCursor cursor = textBrowser->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.insertImage(imageFormat);
        // 插入换行，确保图片单独一行
        cursor.insertBlock();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(flag ? Qt::AlignLeft : Qt::AlignRight);
        cursor.setBlockFormat(blockFormat);
    }
    textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum());
    qDebug() << "send images";
}

void ChatWindow::sendContentFromInput(const QString& htmlContent, int flag) {
    // 设置textBrowser光标到最后
    QTextCursor cursor = textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    textBrowser->setTextCursor(cursor);

    QList<QPair<QString, QImage>> contents = StringTool::extractContent(htmlContent);

    for (const auto& content : contents) {
        if (!content.first.isEmpty()) {
            // 发送文字消息
            sendMessage(content.first, flag);
        }

        if (!content.second.isNull()) {
            // 发送图片消息
            QList<QString> base64Images;
            QByteArray ba;
            QBuffer buffer(&ba);
            buffer.open(QIODevice::WriteOnly);
            content.second.save(&buffer, "PNG");
            base64Images.append(ba.toBase64());
            sendImages(base64Images, flag);
        }
    }

    textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum()); // 自动滚动到底部
    qDebug() << "send content from input";
}

void ChatWindow::addFileMessage(const QString& fileName, const QString& fileDataBase64, bool isSender)
{
    // 构造 filedata:filename:base64 超链接
    QString html = QString("<a href=\"filedata:%1:%2\">📎%1</a>")
                       .arg(fileName)
                       .arg(fileDataBase64);

    if (isSender)
        html = QString("<div style='color:green;'>我发送了文件: %1</div>").arg(html);
    else
        html = QString("<div style='color:blue;'>对方发送了文件: %1</div>").arg(html);

    ui->textEdit->append(html);
    ui->textEdit->append("<br>");
}

void ChatWindow::onFileAnchorClicked(const QUrl &url)
{
    if (url.scheme() == "filedata") {
        QString urlStr = url.toString(); // filedata:filename:base64
        QStringList parts = urlStr.split(":");
        if (parts.size() >= 3) {
            QString fileName = parts[1];
            // 由于 base64 可能包含冒号，重新拼接
            QString fileDataBase64 = parts.mid(2).join(":");
            QString savePath = QFileDialog::getSaveFileName(this, "保存文件", fileName);
            if (!savePath.isEmpty()) {
                QFile outFile(savePath);
                if (outFile.open(QIODevice::WriteOnly)) {
                    QByteArray fileData = QByteArray::fromBase64(fileDataBase64.toUtf8());
                    outFile.write(fileData);
                    outFile.close();
                    QMessageBox::information(this, "保存成功", "文件已保存到: " + savePath);
                } else {
                    QMessageBox::warning(this, "保存失败", "无法保存文件");
                }
            }
        }
    }
}
