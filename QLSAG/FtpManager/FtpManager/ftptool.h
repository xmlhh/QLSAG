/************************************************************************
*   文件名称：ftptool.h
*   编写人员：LHH
*   创建日期：2018/01/09
*   功能描述：FTP上传/下载实现类
*   备    注：
*   修改描述：
************************************************************************/
#ifndef FTPTOOL_H
#define FTPTOOL_H

#include "ftpmanager_global.h"
#include "FtpDownloadFile.h"
#include "ftpthread.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QTimer>

// 上传
class FTPMANAGER_EXPORT FtpTool :public QObject
{
    Q_OBJECT
public:
    ~FtpTool();
    static FtpTool* getInstance();
    void putFileToServer(QList<FtpUploadFile> serverFileList);
private slots:
    void runsuccess(QString id);
    void runerror(QString id,QString message);
    void runprogress(QString id,qint64 bytesSent, qint64 bytesTotal);

    void timeout();
    void threadend(FtpThread* thread);
private:
    static FtpTool* _instance;
    QList<FtpThread*> _freethreads;
    QList<FtpThread*> _usedthreads;
	QList<FtpUploadOneFile> _uploadfiles;

    QTimer* _timer1;
    mutable QMutex mutex;
    FtpTool();

signals:
    void success(QString id);//成功（文件本地路径）
    void error(QString id,QString message);//错误（文件本地路径，错误信息）
    void progress(QString id,qint64 bytesSent, qint64 bytesTotal);//进度（上传大小byte，总大小byte）
};


// 下载
class FTPMANAGER_EXPORT FtpDTool :public QObject
{
	Q_OBJECT
public:
	~FtpDTool();
	static FtpDTool* getInstance();
	void getFileFormServer(QList<FtpDownloadFile> serverFileList);

private slots:
	void drunsuccess(QString id);
	void drunerror(QString id, QString message);
	void drunprogress(QString id, qint64 bytesSent, qint64 bytesTotal);

	void timeout();
	void dthreadend(FtpDThread* thread);
private:
	static FtpDTool* _instance;
	QList<FtpDThread*> _freeDThreads;
	QList<FtpDThread*> _usedDThreads;
	QList<FtpDownloadOneFile> _downloadfiles;

	QTimer* _timer2;
	mutable QMutex mutex;
	FtpDTool();

signals:
	void dsuccess(QString id);//成功（文件本地路径）
	void derror(QString id, QString message);//错误（文件本地路径，错误信息）
	void dprogress(QString id, qint64 bytesSent, qint64 bytesTotal);//进度（下载大小byte，总大小byte）
};

#endif // FTPTOOL_H
