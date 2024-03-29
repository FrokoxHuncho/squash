/***************************************************************************
 * copyright            : (C) 2007-2008 Seb Ruiz <ruiz@kde.org>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2        *
 *   as published by the Free Software Foundation.                         *
 ***************************************************************************/

#ifndef SQUASH_IMAGERESIZER
#define SQUASH_IMAGERESIZER

#include <QDir>
#include <QMutex>
#include <QSize>
#include <QStringList>
#include <QThread>
#include <QWaitCondition>

class QImage;
class QIcon;

class ImageResizer : public QThread
{
    Q_OBJECT

    public:
        ImageResizer( QObject *parent = 0 );
        ~ImageResizer();

        void init();
        void load( QString filename );
        void cancel();

    signals:
        void imageResized( const QString &filename );
        void imageResizeFailed( const QString &filename, const QString &error );

    protected:
        void run();

    private:
        int  m_resizeMethod;
        enum ResizeScale
        {
            PERCENT = 0,
            WIDTH   = 1,
            HEIGHT  = 2,
            PIXEL   = 3,
            MAX     = 4
        };

        QMutex          m_mutex;
        QWaitCondition  m_condition;

        bool            m_abort;
        int             m_failCount;

        double          m_resizeX;
        double          m_resizeY;
        QDir            m_saveDirectory;
        QString         m_fileSuffix;
        bool            m_overwrite;

        QStringList     m_fileList;
};

#endif
