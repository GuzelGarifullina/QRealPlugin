/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#pragma once

#include <QtGlobal>

#if defined(QREALPLUGIN_LIBRARY)
#  define QREALPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QREALPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif


