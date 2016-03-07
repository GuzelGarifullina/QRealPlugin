#ifndef QREAL_GLOBAL_H
#define QREAL_GLOBAL_H

#include <QtGlobal>

#if defined(QREAL_LIBRARY)
#  define QREALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QREALSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QREAL_GLOBAL_H

