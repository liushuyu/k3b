/*
 * Copyright (C) 2016 Leslie Zhai <xiangzhai83@gmail.com>
 * Copyright (C) 2003-2009 Sebastian Trueg <trueg@k3b.org>
 *
 * This file is part of the K3b project.
 * Copyright (C) 1998-2009 Sebastian Trueg <trueg@k3b.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */


#ifndef K3B_CDRSKIN_WRITER_H
#define K3B_CDRSKIN_WRITER_H


#include "k3babstractwriter.h"

#include <QtCore/QProcess>
#include <QtCore/QStringList>

namespace K3b {
    class ExternalBin;
    class Process;
    namespace Device {
        class Device;
    }


    class CdrskinWriter : public AbstractWriter
    {
        Q_OBJECT

    public:
        CdrskinWriter( Device::Device*, JobHandler* hdl,
                        QObject* parent = 0 );
        ~CdrskinWriter();

        bool active() const;

        /**
         * to be used in chain: addArgument(x)->addArgument(y)
         */
        CdrskinWriter* addArgument( const QString& );
        void clearArguments();

        /**
         * Write to the writer process.
         * FIXME: make this an overloaded method from AbstractWriter
         */
        qint64 write( const char* data, qint64 maxSize );

        QIODevice* ioDevice() const;

    public Q_SLOTS:
        void start();
        void cancel();

        void setDao( bool b );
        void setWritingMode( WritingMode mode );
        void setFormattingMode( FormattingMode mode );
        void setCueFile( const QString& s);
        void setClone( bool b );
        void setMulti( bool b );
        void setForce( bool b );

        void setRawCdText( const QByteArray& a );

    protected Q_SLOTS:
        void slotStdLine( const QString& line );
        void slotProcessExited( int exitCode, QProcess::ExitStatus exitStatus );
        void slotThroughput( int t );

    protected:
        virtual bool prepareProcess();

        enum CdrskinError { UNKNOWN,
                             OVERSIZE,
                             BAD_OPTION,
                             SHMGET_FAILED,
                             OPC_FAILED,
                             CANNOT_SET_SPEED,
                             CANNOT_SEND_CUE_SHEET,
                             CANNOT_OPEN_NEW_SESSION,
                             CANNOT_FIXATE_DISK,
                             WRITE_ERROR,
                             PERMISSION_DENIED,
                             BUFFER_UNDERRUN,
                             HIGH_SPEED_MEDIUM,
                             LOW_SPEED_MEDIUM,
                             MEDIUM_ERROR,
                             DEVICE_BUSY,
                             BLANK_FAILED,
                             SHORT_READ };

    private:
        class Private;
        Private* d;
    };
}

#endif
