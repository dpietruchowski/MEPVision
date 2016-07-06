#ifndef MEP_GLOBAL
#define MEP_GLOBAL

#include <QtCore/qglobal.h>

#if defined(MEP_LIBRARY)
#  define MEPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MEPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MEP_GLOBAL
