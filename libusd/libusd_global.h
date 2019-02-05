#ifndef LIBUSD_GLOBAL_H
#define LIBUSD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBUSD_LIBRARY)
#  define LIBUSDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBUSDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBUSD_GLOBAL_H
