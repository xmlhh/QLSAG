#ifndef FTPMANAGER_GLOBAL_H
#define FTPMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef FTPMANAGER_LIB
# define FTPMANAGER_EXPORT Q_DECL_EXPORT
#else
# define FTPMANAGER_EXPORT Q_DECL_IMPORT
#endif

#endif // FTPMANAGER_GLOBAL_H
