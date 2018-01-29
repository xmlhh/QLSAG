/*********************************************************************************
*Auther:		YASAIKUN@Nanjing
*Date:  		20170415
*Description:	多线程实现类
**********************************************************************************/
#include "ftpthread.h"
#include <QString>
#include <QDebug>
#include <QUrl>
#include <QByteArray>
#include <QFileInfo>
#include <QException>
#include <QLatin1String>

FtpThread::FtpThread():QObject()
{
    this->_run = new FtpThreadRunner();
    this->_signal = new FtpThreadObject();
	this->_thread = new QThread();

	qDebug() << "------> uploadFiles <--------";
	
	QObject::connect(this->_signal, SIGNAL(start(FtpUploadOneFile)), this->_run, SLOT(run(FtpUploadOneFile)));
	QObject::connect(this->_run, SIGNAL(end()), this, SLOT(runend()));
	QObject::connect(this->_run, SIGNAL(success(QString)), this, SLOT(runsuccess(QString)));
	QObject::connect(this->_run, SIGNAL(error(QString, QString)), this, SLOT(runerror(QString, QString)));
	QObject::connect(this->_run, SIGNAL(progress(QString, qint64, qint64)), this, SLOT(runprogress(QString, qint64, qint64)));

	this->_run->moveToThread(this->_thread);

}

FtpThread::~FtpThread()
{
    delete this->_run;
    delete this->_signal;
    delete this->_thread;
}

void FtpThread::runsuccess(QString id)
{
	emit this->success(id);
}

void FtpThread::runerror(QString id,QString message)
{
	emit this->error(id, message);
}

void FtpThread::runprogress(QString id,qint64 bytesSent, qint64 bytesTotal)
{
	emit this->progress(id, bytesSent, bytesTotal);
}

void FtpThread::upload(FtpUploadOneFile files)
{
    this->_thread->start();
    this->_signal->upload(files);
}

void FtpThread::runend()
{
    emit this->end(this);
}


FtpThreadObject::FtpThreadObject():QObject(){

}
FtpThreadObject::~FtpThreadObject(){

}
void FtpThreadObject::upload(FtpUploadOneFile files){
    emit this->start(files);
}

FtpThreadRunner::FtpThreadRunner() :QObject(){

    this->manager = new QNetworkAccessManager(this);
}
FtpThreadRunner::~FtpThreadRunner(){

    delete this->manager;
}


/*
*Summary: 上传一个文件的单线程处理
*Parameters:
*     files: 需要上传的单个文件（包含FTP HOST IP PORT 文件绝对路径 等信息）
*Return : void
*/
void FtpThreadRunner::run(FtpUploadOneFile file){
	try{
		this->_file = file;
		QString strFtpUrl = "ftp://" + file.getIP() + ":" + QString::number(file.getPort());
		QFileInfo fileinfo(file.getFile());
		this->ftpUrl = new QUrl(strFtpUrl + file.getServerPath() + fileinfo.fileName());
		this->ftpUrl->setUserName(file.getUser());
		this->ftpUrl->setPassword(file.getPwd());

        data = new QFile(file.getFile(), this);
		// 上传
		if (data->open(QIODevice::ReadOnly))
		{
			this->putReply = manager->put(QNetworkRequest(*this->ftpUrl), data);
			connect(putReply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(OnUploadProgress(qint64, qint64)), Qt::QueuedConnection);
			connect(putReply, SIGNAL(finished()), this, SLOT(uploadFinished()), Qt::QueuedConnection);
			connect(putReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)), Qt::QueuedConnection);
		}
		else
		{
            emit this->error(this->_file.getID(), "file open  Failure");
			emit end();
		}

	}
    catch (QException &ex){
        emit this->error(this->_file.getID(), QString(QLatin1String(ex.what())));
	}
}
void FtpThreadRunner::uploadFinished(){
    emit end();
    emit success(this->_file.getID());
	delete this->ftpUrl;
	this->ftpUrl = NULL;
    delete this->putReply;
    this->putReply = NULL;
    try{
        if (data)
        {
            data->close();
            delete data;
            data = NULL;
        }
       
    }catch (QException &ex){
        //emit this->error(this->_file.getID(), QString(QLatin1String(ex.what())));
		throw ex;
    }
}

void FtpThreadRunner::upLoadError(QNetworkReply::NetworkError errorCode){
    emit this->error(this->_file.getID(),"errorCode:"+QString::number(errorCode));
    emit end();
	delete this->ftpUrl;
	this->ftpUrl = NULL;
    delete this->putReply;
    this->putReply = NULL;
    try{
        if (data)
        {
            data->close();
            delete data;
            data = NULL;
        }
    }catch (QException &ex){
        //emit this->error(this->_file.getID(), QString(QLatin1String(ex.what())));
		throw ex;
    }
}

void FtpThreadRunner::OnUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
	emit this->progress(this->_file.getID(), bytesSent, bytesTotal);
}



// 下载线程
FtpDThread::FtpDThread() :QObject()
{
	this->_drun = new FtpDThreadRunner();
	this->_dsignal = new FtpDThreadObject();
	this->_dThread = new QThread();

	qDebug() << "------> downloadFiles <--------";

	QObject::connect(this->_dsignal, SIGNAL(start(FtpDownloadOneFile)), this->_drun, SLOT(run(FtpDownloadOneFile)));
	QObject::connect(this->_drun, SIGNAL(end()), this, SLOT(drunend()));
	QObject::connect(this->_drun, SIGNAL(success(QString)), this, SLOT(drunsuccess(QString)));
	QObject::connect(this->_drun, SIGNAL(error(QString, QString)), this, SLOT(drunerror(QString, QString)));
	QObject::connect(this->_drun, SIGNAL(DownloadProgress(QString, qint64, qint64)), this, SLOT(drunprogress(QString, qint64, qint64)));
	this->_drun->moveToThread(this->_dThread);

}

FtpDThread::~FtpDThread()
{
	delete this->_drun;
	delete this->_dsignal;
	delete this->_dThread;
}

void FtpDThread::drunsuccess(QString id)
{
	emit this->dSuccess(id);
}

void FtpDThread::drunerror(QString id, QString message)
{
	emit this->dError(id, message);
}

void FtpDThread::drunprogress(QString id, qint64 bytesSent, qint64 bytesTotal)
{
	emit this->dProgress(id, bytesSent, bytesTotal);
}

void FtpDThread::download(FtpDownloadOneFile files)
{
	this->_dThread->start();
	this->_dsignal->download(files);
}

void FtpDThread::drunend()
{
	emit this->dEnd(this);
}

FtpDThreadObject::FtpDThreadObject() :QObject(){

}
FtpDThreadObject::~FtpDThreadObject(){

}

void FtpDThreadObject::download(FtpDownloadOneFile files)
{
	emit this->start(files);
}


FtpDThreadRunner::FtpDThreadRunner() :QObject(){

	this->dmanager = new QNetworkAccessManager(this);
}
FtpDThreadRunner::~FtpDThreadRunner(){

	delete this->dmanager;
}

void FtpDThreadRunner::run(FtpDownloadOneFile file)
{
	qDebug() << "------> download run <--------";
	try{
		this->_file = file;
		QString strFtpUrl = "ftp://" + file.getIP() + ":" + QString::number(file.getPort());
		QFileInfo fileinfo(file.getFile());
		this->ftpUrl = new QUrl(strFtpUrl + file.getServerPath() + fileinfo.fileName());
		this->ftpUrl->setUserName(file.getUser());
		this->ftpUrl->setPassword(file.getPwd());

		data = new QFile(file.getFile(), this);
		// 下载
		if (data->open(QIODevice::WriteOnly | QIODevice::Append))
		{
			this->getReply = dmanager->get(QNetworkRequest(*this->ftpUrl));
			connect(getReply, SIGNAL(finished()), this, SLOT(downloadFinished()), Qt::QueuedConnection);
			connect(getReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(OnDownloadProgress(qint64, qint64)), Qt::QueuedConnection);
			connect(getReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(downloadError(QNetworkReply::NetworkError)), Qt::QueuedConnection);
		}
		else
		{
			emit this->error(this->_file.getID(), "file open  Failure");
			emit end();
		}
	}
	catch (QException &ex){
		emit this->error(this->_file.getID(), QString(QLatin1String(ex.what())));
	}
}

void FtpDThreadRunner::downloadFinished()
{
	QNetworkReply *pReply = qobject_cast<QNetworkReply *>(sender());
	if (NULL == pReply)
	{
		return;
	}
	switch (pReply->error())
	{
	case QNetworkReply::NoError:
	{
        data->write(pReply->readAll());
        data->flush();
	}
		break;

	default:
		break;
	}

	//data->close();
	pReply->deleteLater();

	emit end();
	emit success(this->_file.getID());
	delete this->ftpUrl;
	this->ftpUrl = NULL;
	delete this->getReply;
	this->getReply = NULL;
	try{
		if (data)
		{
			data->close();
			delete data;
			data = NULL;
		}

	}
	catch (QException &ex)
	{
		throw ex;
	}
	
}

void FtpDThreadRunner::downloadError(QNetworkReply::NetworkError errorCode)
{
	emit this->error(this->_file.getID(), "errorCode:" + QString::number(errorCode));
	emit end();
	delete this->ftpUrl;
	this->ftpUrl = NULL;
	delete this->getReply;
	this->getReply = NULL;
	try{
		if (data)
		{
			data->close();
			delete data;
			data = NULL;
		}
	}
	catch (QException &ex)
	{
		throw ex;
	}
}

void FtpDThreadRunner::OnDownloadProgress(qint64 bytesSent, qint64 bytesTotal)
{
	emit this->DownloadProgress(this->_file.getID(), bytesSent, bytesTotal);
}

