/* 
 *
 * $Id$
 * Copyright (C) 2003 Thomas Froescher <tfroescher@k3b.org>
 *
 * This file is part of the K3b project.
 * Copyright (C) 1998-2004 Sebastian Trueg <trueg@k3b.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */


#ifndef K3BDIVXENCODINGPROCESS_H
#define K3BDIVXENCODINGPROCESS_H

#include <qwidget.h>
#include <k3bjob.h>
#include <kio/job.h>

class K3bDivxCodecData;
class KProcess;
class KShellProcess;

/**
  *@author Thomas Froescher
  */
class K3bDivXEncodingProcess : public K3bJob  {
   Q_OBJECT

public:
    K3bDivXEncodingProcess(K3bDivxCodecData *data, QWidget *parent=0, const char *name=0);
    ~K3bDivXEncodingProcess();

    QString jobDescription() const;
    QString jobDetails() const;
	
public slots:
    void start();
    void cancel();

private slots:
    void slotEncodingExited( KProcess *p );
    void slotParseEncoding( KProcess *p, char *buffer, int lenght);
    void slotAudioExited( KProcess *p );
    void slotParseAudio( KProcess *p, char *buffer, int lenght);
    void slotStartAudioProcessing( );
    void slotStartEncoding();
    void slotFinishedCheckVobDirectory( );
    void slotFinishedRestoreBackup();
    void slotFinishedCopyIfos(KIO::Job*);
    //void slotPercent( unsigned int );
private:
    K3bDivxCodecData *m_data;
    KShellProcess *m_process;
    QString m_debugBuffer;
    QStringList m_movefiles;
 
    int m_speedFlag;
    int m_speedTrigger;
    int m_pass;
    int m_speedInitialFlag;
    bool m_interalInterrupt; // true if error detected starting encoding process
    void copyIfos();
    void deleteIfos();
    bool shutdown();
    void checkVobDirectory();
    void restoreBackupFiles();
};

#endif