/************************************************************************
*   文件名称：FFTW.h
*   编写人员：LHH
*   创建日期：2018/01/09
*   功能描述：FFTW傅里叶变换
*   备    注：
*   修改描述：
************************************************************************/
#ifndef FFTW_H
#define FFTW_H

#include "fftw3.h"
#include <QWidget>
#include "ui_FFTW.h"

class FFTW : public QWidget
{
	Q_OBJECT

public:
	FFTW(QWidget *parent = 0);
	~FFTW();

	/**
	* @author by lhh
	* @brief 初始化界面
	* @param 无
	* @return void
	*/
	void InitUI();

	/**
	* @author by lhh
	* @brief 初始化数据
	* @param 无
	* @return void
	*/
	void InitData();

	/**
	* @author by lhh
	* @brief 信号槽连接
	* @param 无
	* @return void
	*/
	void SiganlConnect();

private:
	Ui::FFTW ui;
};

#endif // FFTW_H
