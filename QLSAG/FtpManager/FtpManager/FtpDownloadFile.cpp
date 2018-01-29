#include "FtpDownloadFile.h"

#include <QMetaType>
#include <QCryptographicHash>

// ÉÏ´«
FtpUploadFile::FtpUploadFile(QString ip, int port, QString user, QString pwd, QString serverpath, QList<QString> files)
{
	this->_ip = ip;
	this->_port = port;
	this->_user = user;
	this->_pwd = pwd;
	this->_serverpath = serverpath;
	this->_files = files;
}
FtpUploadFile::FtpUploadFile(QString ip, int port, QString user, QString pwd, QString serverpath)
{
	this->_ip = ip;
	this->_port = port;
	this->_user = user;
	this->_pwd = pwd;
	this->_serverpath = serverpath;
}
FtpUploadFile::FtpUploadFile()
{

}

QString FtpUploadFile::getIP(){
	return this->_ip;
}
int FtpUploadFile::getPort(){
	return this->_port;
}
QString FtpUploadFile::getUser(){
	return this->_user;
}
QString FtpUploadFile::getPwd(){
	return this->_pwd;
}
QString FtpUploadFile::getServerPath(){
	return this->_serverpath;
}
QList<QString> FtpUploadFile::getFiles(){
	return this->_files;
}

void FtpUploadFile::setIP(QString ip){
	this->_ip = ip;
}
void FtpUploadFile::setPort(int port){
	this->_port = port;
}
void FtpUploadFile::setUser(QString user){
	this->_user = user;
}
void FtpUploadFile::setPwd(QString pwd){
	this->_pwd = pwd;
}
void FtpUploadFile::setServerPath(QString serverpath){
	this->_serverpath = serverpath;
}
void FtpUploadFile::setFiles(QList<QString> files){
	this->_files = files;
}

QList<FtpUploadOneFile> FtpUploadFile::getFtpUploadOneFile()
{
	QList<FtpUploadOneFile> files;
	foreach(QString file, this->getFiles()) {
		FtpUploadOneFile f(this->getIP(), this->getPort(), this->getUser(), this->getPwd(), this->getServerPath(), file);
		files.append(f);
	}
	return files;
}


FtpUploadOneFile::FtpUploadOneFile(QString ip, int port, QString user, QString pwd, QString serverpath, QString file)
{
	this->_ip = ip;
	this->_port = port;
	this->_user = user;
	this->_pwd = pwd;
	this->_serverpath = serverpath;
	this->_file = file;
	qRegisterMetaType<FtpUploadOneFile>("FtpUploadOneFile");
	QString mdsstr;
	this->_id = QCryptographicHash::hash((mdsstr.append(ip).append(QString::number(port)).append(user).append(pwd).append(serverpath).append(file)).toLocal8Bit(), QCryptographicHash::Md5).toHex();
}

FtpUploadOneFile::FtpUploadOneFile()
{

}

FtpUploadOneFile::FtpUploadOneFile(QString id)
{
	this->_id = id;
}

bool FtpUploadOneFile::operator ==(const FtpUploadOneFile& a)
{
	return QString::compare(a.getID(), this->getID()) == 0;
}

bool FtpUploadOneFile::operator !=(const FtpUploadOneFile& a)
{
	return QString::compare(a.getID(), this->getID()) != 0;
}

QString FtpUploadOneFile::getID() const{
	return this->_id;
}
QString FtpUploadOneFile::getIP(){
	return this->_ip;
}
int FtpUploadOneFile::getPort(){
	return this->_port;
}
QString FtpUploadOneFile::getUser(){
	return this->_user;
}
QString FtpUploadOneFile::getPwd(){
	return this->_pwd;
}
QString FtpUploadOneFile::getServerPath(){
	return this->_serverpath;
}
QString FtpUploadOneFile::getFile(){
	return this->_file;
}



#if 1
// ÏÂÔØ
FtpDownloadFile::FtpDownloadFile(QString ip, int port, QString user, QString pwd, QString serverpath, QList<QString> files)
{
	this->_ip = ip;
	this->_port = port;
	this->_user = user;
	this->_pwd = pwd;
	this->_serverpath = serverpath;
	this->_files = files;
}
FtpDownloadFile::FtpDownloadFile(QString ip, int port, QString user, QString pwd, QString serverpath)
{
	this->_ip = ip;
	this->_port = port;
	this->_user = user;
	this->_pwd = pwd;
	this->_serverpath = serverpath;
}
FtpDownloadFile::FtpDownloadFile()
{

}

QString FtpDownloadFile::getIP(){
	return this->_ip;
}
int FtpDownloadFile::getPort(){
	return this->_port;
}
QString FtpDownloadFile::getUser(){
	return this->_user;
}
QString FtpDownloadFile::getPwd(){
	return this->_pwd;
}
QString FtpDownloadFile::getServerPath(){
	return this->_serverpath;
}
QList<QString> FtpDownloadFile::getFiles(){
	return this->_files;
}

void FtpDownloadFile::setIP(QString ip){
	this->_ip = ip;
}
void FtpDownloadFile::setPort(int port){
	this->_port = port;
}
void FtpDownloadFile::setUser(QString user){
	this->_user = user;
}
void FtpDownloadFile::setPwd(QString pwd){
	this->_pwd = pwd;
}
void FtpDownloadFile::setServerPath(QString serverpath){
	this->_serverpath = serverpath;
}
void FtpDownloadFile::setFiles(QList<QString> files){
	this->_files = files;
}

QList<FtpDownloadOneFile> FtpDownloadFile::getFtpDownloadOneFile()
{
	QList<FtpDownloadOneFile> files;
	foreach(QString file, this->getFiles()) {
		FtpDownloadOneFile f(this->getIP(), this->getPort(), this->getUser(), this->getPwd(), this->getServerPath(), file);
		files.append(f);
	}
	return files;
}


FtpDownloadOneFile::FtpDownloadOneFile(QString ip, int port, QString user, QString pwd, QString serverpath, QString file)
{
	this->_ip = ip;
	this->_port = port;
	this->_user = user;
	this->_pwd = pwd;
	this->_serverpath = serverpath;
	this->_file = file;
	qRegisterMetaType<FtpDownloadOneFile>("FtpDownloadOneFile");
	QString mdsstr;
	this->_id = QCryptographicHash::hash((mdsstr.append(ip).append(QString::number(port)).append(user).append(pwd).append(serverpath).append(file)).toLocal8Bit(), QCryptographicHash::Md5).toHex();
}

FtpDownloadOneFile::FtpDownloadOneFile(QString id)
{
	this->_id = id;
}

FtpDownloadOneFile::FtpDownloadOneFile()
{

}

bool FtpDownloadOneFile::operator ==(const FtpDownloadOneFile& a)
{
	return QString::compare(a.getID(), this->getID()) == 0;
}

bool FtpDownloadOneFile::operator !=(const FtpDownloadOneFile& a)
{
	return QString::compare(a.getID(), this->getID()) != 0;
}

QString FtpDownloadOneFile::getID() const
{
	return this->_id;
}

QString FtpDownloadOneFile::getIP()
{
	return this->_ip;
}

int FtpDownloadOneFile::getPort()
{
	return this->_port;
}

QString FtpDownloadOneFile::getUser()
{
	return this->_user;
}
QString FtpDownloadOneFile::getPwd()
{
	return this->_pwd;
}

QString FtpDownloadOneFile::getServerPath()
{
	return this->_serverpath;
}

QString FtpDownloadOneFile::getFile()
{
	return this->_file;
}
#endif