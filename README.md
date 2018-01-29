# QLSAG
利用QNetworkAccessManager实现多线程Ftp上传/下载、利用FFTW库进行频谱分析

环境：VS2013+Qt5.7

1.FTP上传/下载服务器文件
FtpManager工程为Ftp上传/下载库

2.QLSAG工程为Ftp下载界面及频谱分析界面

3.FFTW3库的配置：
步骤1：
libfftw3-3.def
libfftw3f-3.def
libfftw3l-3.def
将以上三个文件放在C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin目录下

步骤2：
将fftw3.h头文件放在C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include目录下

步骤3：
libfftw3-3.lib
libfftw3f-3.lib
libfftw3l-3.lib
将以上生成的三个lib文件放在C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib目录下

步骤4：
libfftw3-3.lib
libfftw3f-3.lib
libfftw3l-3.lib
在QLSAG工程属性-》连接器-》输入-》-》附加依赖项，加入以上三个lib库文件

4.工程加载的库
Qt5.7库：
qtmaind.lib
Qt5Cored.lib
Qt5Guid.lib
Qt5Networkd.lib

Qt5Widgetsd.lib
FtpManager.lib
libfftw3-3.lib
libfftw3f-3.lib
libfftw3l-3.lib
