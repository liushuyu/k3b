/***************************************************************************
                          k3bfileview.cpp  -  description
                             -------------------
    begin                : Sun Oct 28 2001
    copyright            : (C) 2001 by Sebastian Trueg
    email                : trueg@informatik.uni-freiburg.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "k3bfileview.h"
#include "k3b.h"
#include "k3baudioplayer.h"
#include "k3bdoc.h"
#include "k3bdiroperator.h"

#include <qwidget.h>
#include <qdragobject.h>
#include <qlayout.h>
#include <qdir.h>
#include <qvbox.h>
#include <qlabel.h>

#include <kfiledetailview.h>
#include <klistview.h>
#include <kaction.h>
#include <ktoolbar.h>
#include <ktoolbarbutton.h>
#include <kurl.h>
#include <kurldrag.h>
#include <kfilefiltercombo.h>
#include <klocale.h>
#include <kfileitem.h>
#include <kmessagebox.h>



K3bFileView::K3bFileView(QWidget *parent, const char *name ) 
  : K3bCdContentsView(parent,name) 
{
  setupGUI();

  connect( k3bMain(), SIGNAL(saveConfig(KConfig*)), this, SLOT(saveConfig(KConfig*)) );
}


K3bFileView::~K3bFileView()
{
}


KActionCollection* K3bFileView::actionCollection() const
{
  return m_dirOp->actionCollection();
}


void K3bFileView::setupGUI()
{
  QVBoxLayout* layout = new QVBoxLayout( this );
  layout->setAutoAdd( true );

  m_dirOp           = new K3bDirOperator( QDir::home().absPath(), this );

  m_dirOp->readConfig( k3bMain()->config(), "file view" );
  m_dirOp->setMode( KFile::Files );
  m_dirOp->setView( KFile::Default );

  KToolBar* toolBar = new KToolBar( this, "fileviewtoolbar" );

  KAction* actionPlay = new KAction( i18n("&Play"), "1rightarrow", 0, this, SLOT(slotAudioFilePlay()), 
				     m_dirOp->actionCollection(), "audio_file_play");
  KAction* actionEnqueue = new KAction( i18n("&Enqueue"), "1rightarrow", 0, this, SLOT(slotAudioFileEnqueue()), 
					m_dirOp->actionCollection(), "audio_file_enqueue");
  KAction* actionAddFilesToProject = new KAction( i18n("&Add to project"), 0, this, SLOT(slotAddFilesToProject()), 
						  m_dirOp->actionCollection(), "add_file_to_project");

  // add some actions to the toolbar
  m_dirOp->actionCollection()->action("up")->plug( toolBar );
  actionPlay->plug( toolBar );
  toolBar->insertSeparator();

  KActionMenu* dirOpMenu = (KActionMenu*)m_dirOp->actionCollection()->action("popupMenu");
  dirOpMenu->insert( actionAddFilesToProject, 0 );
  dirOpMenu->insert( new KActionSeparator( m_dirOp->actionCollection() ), 1 );
  dirOpMenu->insert( actionPlay, 2 );
  dirOpMenu->insert( actionEnqueue, 3 );
  dirOpMenu->insert( new KActionSeparator( m_dirOp->actionCollection() ), 4 );

  // check if some actions should be enabled
  connect( dirOpMenu, SIGNAL(activated()), this, SLOT(slotCheckActions()) );

  // create filter selection combobox
  QLabel* filterLabel = new QLabel( i18n("&Filter:"), toolBar, "filterLabel" );
  m_filterWidget = new KFileFilterCombo( toolBar, "filterwidget" );

  m_filterWidget->setEditable( true );
  QString filter = i18n("*|All files");
  filter += "\n" + i18n("audio/x-mp3 application/x-ogg audio/wav |Sound files");
  filter += "\n" + i18n("audio/x-mp3 |MP3 sound files");
  filter += "\n" + i18n("application/x-ogg |Ogg Vorbis sound files");
  m_filterWidget->setFilter(filter);

  filterLabel->setBuddy(m_filterWidget);
  connect( m_filterWidget, SIGNAL(filterChanged()), SLOT(slotFilterChanged()) );

  connect( m_dirOp, SIGNAL(fileHighlighted(const KFileItem*)), this, SLOT(slotFileHighlighted(const KFileItem*)) );
  connect( m_dirOp, SIGNAL(urlEntered(const KURL&)), this, SIGNAL(urlEntered(const KURL&)) );
  connect( m_dirOp, SIGNAL(doubleClicked(KFileItem*)), this, SLOT(slotAddFilesToProject()) );

  actionPlay->setEnabled( false );
}


void K3bFileView::setUrl(const KURL& url, bool forward)
{
  m_dirOp->setURL( url, forward );
}


void K3bFileView::slotFileHighlighted( const KFileItem* item )
{
  // check if there are audio files under the selected ones
  bool play = false;
  for( QListIterator<KFileItem> it( *(m_dirOp->selectedItems()) ); it.current(); ++it ) {
    if( k3bMain()->audioPlayer()->supportsMimetype(it.current()->mimetype()) ) {
      play = true;
      break;
    }
  }

  if( play ) {
    m_dirOp->actionCollection()->action( "audio_file_play" )->setEnabled( true );
    m_dirOp->actionCollection()->action( "audio_file_enqueue" )->setEnabled( true );
  }
  else {
    m_dirOp->actionCollection()->action( "audio_file_play" )->setEnabled( false );
    m_dirOp->actionCollection()->action( "audio_file_enqueue" )->setEnabled( false );
  }
}


void K3bFileView::slotAudioFilePlay()
{
  // play selected audio files
  QStringList files;

  for( QListIterator<KFileItem> it( *(m_dirOp->selectedItems()) ); it.current(); ++it ) {
    if( k3bMain()->audioPlayer()->supportsMimetype(it.current()->mimetype()) ) {
      files.append( it.current()->url().path() );
    }
  }

  if( !files.isEmpty() )
    k3bMain()->audioPlayer()->playFiles( files );
}


void K3bFileView::slotAudioFileEnqueue()
{
  // play selected audio files
  QStringList files;

  for( QListIterator<KFileItem> it( *(m_dirOp->selectedItems()) ); it.current(); ++it ) {
    if( k3bMain()->audioPlayer()->supportsMimetype(it.current()->mimetype()) ) {
      files.append( it.current()->url().path() );
    }
  }

  if( !files.isEmpty() )
    k3bMain()->audioPlayer()->enqueueFiles( files );
}


void K3bFileView::slotAddFilesToProject()
{
  if( !k3bMain()->activeDoc() )
    KMessageBox::error( this, i18n("Please create a project before adding files"), i18n("No active Project"));
  else {
    KURL::List files;
    for( QListIterator<KFileItem> it( *(m_dirOp->selectedItems()) ); it.current(); ++it ) {
      files.append( it.current()->url() );
    }
    
    if( !files.isEmpty() )
      k3bMain()->activeDoc()->addUrls( files );
  }
}


void K3bFileView::slotFilterChanged()
{
  QString filter = m_filterWidget->currentFilter();
  m_dirOp->clearFilter();

  if( filter.find( '/' ) > -1 ) {
    QStringList types = QStringList::split( " ", filter );
    types.prepend( "inode/directory" );
    m_dirOp->setMimeFilter( types );
  }
  else
    m_dirOp->setNameFilter( filter );
  
  m_dirOp->rereadDir();
  //  emit filterChanged( filter );
}


void K3bFileView::slotCheckActions()
{
  m_dirOp->actionCollection()->action("add_file_to_project")->setEnabled( k3bMain()->activeView() != 0 );
}


void K3bFileView::reload()
{
  m_dirOp->actionCollection()->action("reload")->activate();
}


void K3bFileView::saveConfig( KConfig* c )
{
  m_dirOp->writeConfig( k3bMain()->config(), "file view" );
}


#include "k3bfileview.moc"
