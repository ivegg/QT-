#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QMap>
#include <QTimer>
#include <QProgressDialog>

class FileTransfer : public QObject
{
    Q_OBJECT

public:
    explicit FileTransfer(QObject *parent = nullptr);
    ~FileTransfer();

    // 发送文件
    void sendFile(const QString &filePath, int receiverId, bool isGroup = false);
    // 接收文件
    void receiveFile(const QString &fileName, const QByteArray &data, bool isSender = false);
    // 取消传输
    void cancelTransfer(const QString &transferId);
    // 暂停传输
    void pauseTransfer(const QString &transferId);
    // 恢复传输
    void resumeTransfer(const QString &transferId);

signals:
    void transferProgress(const QString &transferId, int progress);
    void transferComplete(const QString &transferId);
    void transferError(const QString &transferId, const QString &error);
    void transferPaused(const QString &transferId);
    void transferResumed(const QString &transferId);

private:
    static const int CHUNK_SIZE = 1024 * 1024; // 1MB chunks
    QMap<QString, QFile*> m_activeTransfers;
    QMap<QString, QProgressDialog*> m_progressDialogs;
    QMap<QString, qint64> m_transferProgress;
    QMap<QString, bool> m_transferPaused;
    QTimer m_retryTimer;

    QString generateTransferId(const QString &filePath, int receiverId);
    void sendChunk(const QString &transferId, qint64 offset);
    void handleTransferError(const QString &transferId, const QString &error);
};

#endif // FILETRANSFER_H 