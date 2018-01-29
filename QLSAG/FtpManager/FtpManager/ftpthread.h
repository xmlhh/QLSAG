/************************************************************************
*   文件名称：ftpthread.h
*   编写人员：LHH
*   创建日期：2018/01/09
*   功能描述：线程实现类头文件，用于实现FTP上传/下载的多线程
*   备    注：
*   修改描述：
************************************************************************/
#ifndef FTPTHREAD_H
#define FTPTHREAD_H

#include <QObject>
#include <QThread>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include "FtpDownloadFile.h"
#include <QFile>

// 上传线程
class FtpThreadRunner:public QObject
{
    Q_OBJECT
public:
    FtpThreadRunner();
    ~FtpThreadRunner();

Q_SIGNALS:
    void end();
    void success(QString id);
    void error(QString id,QString message);
    void progress(QString id,qint64 bytesSent, qint64 bytesTotal);

public slots:
    void run(FtpUploadOneFile file);

    void uploadFinished();
    void upLoadError(QNetworkReply::NetworkError errorCode);
    void OnUploadProgress( qint64 bytesSent, qint64 bytesTotal );

private:
    FtpUploadOneFile _file;
    QNetworkAccessManager *manager;
    QNetworkReply *putReply;
	QUrl* ftpUrl;
    QFile* data;
};


class FtpThreadObject :public QObject
{
	Q_OBJECT
public:
	FtpThreadObject();
	~FtpThreadObject();
	void upload(FtpUploadOneFile files);
Q_SIGNALS:
	void start(FtpUploadOneFile files);
};


class FtpThread :public QObject
{
	Q_OBJECT
public:
	FtpThread();
	~FtpThread();
	void upload(FtpUploadOneFile files);
Q_SIGNALS:
	void end(FtpThread* uthread);
	void success(QString id);
	void error(QString id, QString message);
	void progress(QString id, qint64 bytesSent, qint64 bytesTotal);

private slots:
	void runend();
	void runsuccess(QString id);
	void runerror(QString id, QString message);
	void runprogress(QString id, qint64 bytesSent, qint64 bytesTotal);

private:
	QThread* _thread;
	FtpThreadObject* _signal;
	FtpThreadRunner* _run;
};



// 下载线程
class FtpDThreadRunner :public QObject
{
	Q_OBJECT
public:
	FtpDThreadRunner();
	~FtpDThreadRunner();

Q_SIGNALS:
	void end();
	void success(QString id);
	void error(QString id, QString message);
	void DownloadProgress(QString id, qint64 bytesSent, qint64 bytesTotal);

public slots:
	void run(FtpDownloadOneFile file);

	void downloadFinished();
	void downloadError(QNetworkReply::NetworkError errorCode);
	void OnDownloadProgress(qint64 bytesSent, qint64 bytesTotal);

private:
	FtpDownloadOneFile _file;
	QNetworkAccessManager *dmanager;
	QNetworkReply *getReply;
	QUrl* ftpUrl;
	QFile* data;
};


class FtpDThreadObject :public QObject
{
	Q_OBJECT
public:
	FtpDThreadObject();
	~FtpDThreadObject();
	void download(FtpDownloadOneFile files);
Q_SIGNALS:
	void start(FtpDownloadOneFile files);
};


class FtpDThread:public QObject
{
    Q_OBJECT
public:
	FtpDThread();
	~FtpDThread();
	void download(FtpDownloadOneFile files);

Q_SIGNALS:
	void dEnd(FtpDThread* dthread);
	void dSuccess(QString id);
	void dError(QString id, QString message);
	void dProgress(QString id, qint64 bytesSent, qint64 bytesTotal);

private slots:
		void drunend();
		void drunsuccess(QString id);
		void drunerror(QString id, QString message);
		void drunprogress(QString id, qint64 bytesSent, qint64 bytesTotal);
private:
	QThread* _dThread;
	FtpDThreadObject* _dsignal;
	FtpDThreadRunner* _drun;
};

#endif // FTPTHREAD_H
