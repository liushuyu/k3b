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


#ifndef K3BDVDDIRECTORIES_H
#define K3BDVDDIRECTORIES_H

#include <qgroupbox.h>
#include <qstring.h>

class KLineEdit;
class QToolButton;
class K3bDivxCodecData;
class K3bDivXDataGui;
class KCompletionBox;
class KDirOperator;


class K3bDivxDirectories : public QGroupBox  {
    Q_OBJECT
public:
    K3bDivxDirectories( K3bDivxCodecData *data, QWidget *parent=0, const char *name=0);
    ~K3bDivxDirectories();
signals:
    void dataChanged( );
private:
    KLineEdit *m_editVideoPath;
    QToolButton *m_buttonVideoDir;
    KLineEdit *m_editAudioPath;
    QToolButton *m_buttonAudioDir;
    KLineEdit *m_editAviPath;
    QToolButton *m_buttonAviDir;
    K3bDivxCodecData *m_data;
    KCompletionBox *m_completionBox;
    KDirOperator *m_ops;
    void setupGui();
    void init();

private slots:
    void slotAviClicked();
    void slotAudioClicked();
    void slotVideoClicked();
    void slotVideoEdited( const QString& );
    void slotAviEdited( const QString& );
    void slotCompletion( const QString& );
};

#endif