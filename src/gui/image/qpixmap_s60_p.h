/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPIXMAPDATA_S60_P_H
#define QPIXMAPDATA_S60_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/private/qpixmap_raster_p.h>

QT_BEGIN_NAMESPACE

class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;

class QSymbianBitmapDataAccess;

class QSymbianFbsHeapLock
{
public:

    enum LockAction {
        Unlock
    };

    explicit QSymbianFbsHeapLock(LockAction a);
    ~QSymbianFbsHeapLock();
    void relock();

private:

    LockAction action;
    bool wasLocked;
};

class QS60PixmapData : public QRasterPixmapData
{
public:
    QS60PixmapData(PixelType type);
    ~QS60PixmapData();

    void resize(int width, int height);
    void fromImage(const QImage &image, Qt::ImageConversionFlags flags);
    void copy(const QPixmapData *data, const QRect &rect);
    bool scroll(int dx, int dy, const QRect &rect);

    int metric(QPaintDevice::PaintDeviceMetric metric) const;
    void fill(const QColor &color);
    void setMask(const QBitmap &mask);
    void setAlphaChannel(const QPixmap &alphaChannel);
    QImage toImage() const;
    QPaintEngine* paintEngine() const;

    void beginDataAccess();
    void endDataAccess(bool readOnly=false) const;

    void* toNativeType(NativeType type);
    void fromNativeType(void* pixmap, NativeType type);

private:
    void release();
    void fromSymbianBitmap(CFbsBitmap* bitmap);
    bool initSymbianBitmapContext();

    QSymbianBitmapDataAccess *symbianBitmapDataAccess;

    CFbsBitmap *cfbsBitmap;
    CFbsBitmapDevice *bitmapDevice;
    CFbsBitGc *bitmapGc;
    QPaintEngine *pengine;
    uchar* bytes;

    friend class QPixmap;
    friend class QS60WindowSurface;
    friend class QS60PaintEngine;
    friend class QS60Data;
};

QT_END_NAMESPACE

#endif // QPIXMAPDATA_S60_P_H
