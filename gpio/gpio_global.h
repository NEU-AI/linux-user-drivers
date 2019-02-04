#ifndef GPIO_GLOBAL_H
#define GPIO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GPIO_LIBRARY)
#  define GPIOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GPIOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GPIO_GLOBAL_H
