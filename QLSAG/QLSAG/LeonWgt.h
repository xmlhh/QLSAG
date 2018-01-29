/************************************************************************
*   文件名称：LeonWgt.h
*   编写人员：LHH
*   创建日期：2018/01/09
*   功能描述：Ftp下载界面及频谱分析界面
*   备    注：
*   修改描述：
************************************************************************/

#ifndef LEONWGT_H
#define LEONWGT_H

#include "../FtpManager/FtpManager/FtpDownloadFile.h"
#include "../FtpManager/FtpManager/ftptool.h"

#include "FFTW.h"

#include <QtWidgets/QWidget>
#include "ui_LeonWgt.h"

class QLSAG : public QWidget
{
	Q_OBJECT

public:
	QLSAG(QWidget *parent = 0);
	~QLSAG();

	/**
	* @author by lhh
	* @brief 初始化界面
	* @param 无
	* @return void
	*/
	void InitUI();

	/**
	* @author by lhh
	* @brief 信号槽连接
	* @param 无
	* @return void
	*/
	void SiganlConnect();

	/**
	* @author by lhh
	* @brief 初始化数据
	* @param 无
	* @return void
	*/
	void InitData();

	/*@author by lhh
	* @brief 接收下载的文件
	* @param IP与之相关的文件绝对路径
	* @return void
	*/
	void RecvFileFromServer(QMap<QString, QStringList> &mapIpFilePath);

	/**
	* @author by lhh
	* @brief 获取保存文件路径
	* @param 文件路径
	* @param 保存路径
	* @return void
	*/
	QString GetSaveFilePath(QString strFilePath, QString strSavePath);


Q_SIGNALS:
	/**
	* @author by lhh
	* @brief 发送成功的信号
	* @param 目标IP
	* @param 选择的文件
	* @return void
	*/
	void SignalSuccess(const QString& strIp, const QString& strFiles, bool bFlag);

	/**
	* @author by lhh
	* @brief 发送失败的信号
	* @param 目标IP
	* @param 选择的文件
	* @return void
	*/
	void SignalFailure(const QString& strIp, const QString& strFiles, bool bFlag);

	/**
	* @author by lhh
	* @brief 发送文件进度的信号
	* @param 当前设备IP
	* @param 已发送文件的字节数
	* @param 文件总字节数
	* @return void
	*/
	void Signal_download_progress(const QString& id, qint64 bytesSent, qint64 bytesTotal);

	/**
	* @author by lhh
	* @brief 文件下载成功后发送的信号
	* @param ip、port、key
	* @return void
	*/
	void Signal_download_sucess(const QString& ip, const QString& strFileName);

private slots:
	/**
	* @author by lhh
	* @brief 添加下载文件
	* @param 文件 
	* @return void
	*/
	void OnAddDownloadFileName(const QString &strFileName);

	/**
	* @author by lhh
	* @brief 选择保存文件路径
	* @param 无
	* @return void
	*/
	void OnSelectLocalPath();
	
	/**
	* @author by lhh
	* @brief 下载文件
	* @param 无
	* @return void
	*/
	void OnDownloadBtn();

	void download_success(QString id);//成功（文件本地路径）
	void download_error(QString id, QString message);//错误（文件本地路径，错误信息）
	void download_progress(QString id, qint64 bytesSent, qint64 bytesTotal);//进度（上传大小byte，总大小byte）

	/**
	* @author by lhh
	* @brief 发送成功的槽函数
	* @param 目标IP
	* @param 选择的文件
	* @return void
	*/
	void OnSuccess(const QString& strIp, const QString& strFile, bool bFlag);

	/**
	* @author by lhh
	* @brief 发送失败的槽函数
	* @param 目标IP
	* @param 选择的文件
	* @return void
	*/
	void OnFailure(const QString& strIp, const QString& strFile, bool bFlag);

	/**
	* @author by lhh
	* @brief 接收发送文件进度的槽函数
	* @param 当前设备IP
	* @param 已发送文件的字节数
	* @param 文件总字节数
	* @return void
	*/
	void OnUploadProgress(const QString& id, qint64 bytesSent, qint64 bytesTotal);

	/**
	* @author by lhh
	* @brief 解析文件
	* @param 服务器地址
	* @param 接收的文件
	* @return void
	*/
	void OnParseDownLoadFile(const QString& strIp, const QString& strFileName);

	/**
	* @author by lhh
	* @brief 傅里叶变换
	* @param 无
	* @return void
	*/
	void OnFFTWBtn();

private:
	QList<FtpUploadOneFile> _uploadfiles;
	QList<FtpDownloadOneFile> _downloadfiles;

private:
	Ui::QLSAGClass ui;

	QString m_strFilePath;
	QString m_strSavePath;

	FFTW *m_pfftw;

	
};

#endif // LEONWGT_H
