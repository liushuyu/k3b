/***************************************************************************
                          k3bdatadoc.h  -  description
                             -------------------
    begin                : Sun Apr 22 2001
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

#ifndef K3BDATADOC_H
#define K3BDATADOC_H

#include "../k3bdoc.h"

#include <qqueue.h>
#include <qfileinfo.h>

class K3bDataItem;
class K3bRootItem;
class K3bDirItem;
class K3bFileItem;
class K3bJob;

class K3bView;
class QString;
class QStringList;
class QWidget;
class QDomDocument;



/**
 *@author Sebastian Trueg
 */

class K3bDataDoc : public K3bDoc
{
  Q_OBJECT

 public:
  K3bDataDoc( QObject* parent );
  ~K3bDataDoc();

  enum whiteSpaceTreatments { normal = 0, convertToUnderScore = 1, strip = 2, extendedStrip = 3 };
		
  K3bRootItem* root() const { return m_root; }

  /** reimplemented from K3bDoc */
  K3bView* newView( QWidget* parent );
  /** reimplemented from K3bDoc */
  void addView(K3bView* view);

  bool newDocument();	
  long size() const;
  int length() const;
	
  const QString& name() const { return m_name; }
	
  void removeItem( K3bDataItem* item );

  K3bDirItem* addEmptyDir( const QString& name, K3bDirItem* parent );
	
  /** writes a mkisofs-path-spec file with graft-points **/
  QString writePathSpec( const QString& fileName );
	
  /** returns an empty dummy dir for use with K3bDirItems.
      Creates one if nessessary.
      The dummy dir is used to create empty dirs on the iso-filesystem! */
  const QString& dummyDir();
  const QString& isoImage() const { return m_isoImage; }
  void setIsoImage( const QString& s ) { m_isoImage = s; }
	
  K3bBurnJob* newBurnJob();
	
  int whiteSpaceTreatment() const { return m_whiteSpaceTreatment; }
  bool deleteImage() const { return m_deleteImage; }
  bool onlyCreateImage() const { return m_onlyCreateImage; }
	
  void setWhiteSpaceTreatment( int i ) { m_whiteSpaceTreatment = i; }
  void setDeleteImage( bool b ) { m_deleteImage = b; }
  void setOnlyCreateImage( bool b ) { m_onlyCreateImage = b; }
	
  // -- mkisofs-options ----------------------------------------------------------------------
  bool createRockRidge() const { return m_createRockRidge; }
  bool createJoliet() const { return m_createJoliet; }
  bool ISOallowLowercase() const { return m_ISOallowLowercase; }
  bool ISOallowPeriodAtBegin() const { return m_ISOallowPeriodAtBegin; }
  bool ISOallow31charFilenames() const { return m_ISOallow31charFilenames; }
  bool ISOomitVersionNumbers() const { return m_ISOomitVersionNumbers; }
  bool ISOmaxFilenameLength() const { return m_ISOmaxFilenameLength; }
  bool ISOrelaxedFilenames() const { return m_ISOrelaxedFilenames; }
  bool ISOnoIsoTranslate() const { return m_ISOnoIsoTranslate; }
  bool ISOallowMultiDot() const { return m_ISOallowMultiDot; }
  bool ISOuntranslatedFilenames() const { return m_ISOuntranslatedFilenames; }
  bool noDeepDirectoryRelocation() const { return m_noDeepDirectoryRelocation; }
  bool followSymbolicLinks() const { return m_followSymbolicLinks; }
  bool hideRR_MOVED() const { return m_hideRR_MOVED; }
  bool createTRANS_TBL() const { return m_createTRANS_TBL; }
  bool hideTRANS_TBL() const { return m_hideTRANS_TBL; }
  bool padding() const { return m_padding; }

  int ISOLevel() const { return m_isoLevel; }
  const QString& applicationID() const { return m_applicationID; }
  const QString& volumeID() const { return m_volumeID; }
  const QString& publisher() const { return m_publisher; }
  const QString& preparer() const { return m_preparer; }
	
  void setCreateRockRidge( bool b ) { m_createRockRidge = b; }
  void setCreateJoliet( bool b ) {  m_createJoliet = b; }
  void setISOallowLowercase( bool b ) {  m_ISOallowLowercase = b; }
  void setISOallowPeriodAtBegin( bool b ) {  m_ISOallowPeriodAtBegin = b; }
  void setISOallow31charFilenames( bool b ) {  m_ISOallow31charFilenames = b; }
  void setISOomitVersionNumbers( bool b ) {  m_ISOomitVersionNumbers = b; }
  void setISOmaxFilenameLength( bool b ) {  m_ISOmaxFilenameLength = b; }
  void setISOrelaxedFilenames( bool b ) {  m_ISOrelaxedFilenames = b; }
  void setISOnoIsoTranslate( bool b ) {  m_ISOnoIsoTranslate = b; }
  void setISOallowMultiDot( bool b ) {  m_ISOallowMultiDot = b; }
  void setISOuntranslatedFilenames( bool b ) {  m_ISOuntranslatedFilenames = b; }
  void setNoDeepDirectoryRelocation( bool b ) {  m_noDeepDirectoryRelocation = b; }
  void setFollowSymbolicLinks( bool b ) {  m_followSymbolicLinks = b; }
  void setHideRR_MOVED( bool b ) {  m_hideRR_MOVED = b; }
  void setCreateTRANS_TBL( bool b ) {  m_createTRANS_TBL = b; }
  void setHideTRANS_TBL( bool b ) {  m_hideTRANS_TBL = b; }
  void setPadding( bool b ) {  m_padding = b; }
	
  void setISOLevel( int i ) { m_isoLevel = i; }
  void setApplicationID( const QString& s ) { m_applicationID = s; }
  void setVolumeID( const QString& s ) { m_volumeID = s; }
  void setPublisher( const QString& s ) { m_publisher = s; }
  void setPreparer( const QString& s ) { m_preparer = s; }
	
  // ----------------------------------------------------------------- mkisofs-options -----------
	
 public slots:
  /** add urls to the compilation.
   * @param dir the directory where to add the urls, by default this is the root directory.
   **/
  void slotAddURLs( const QStringList&, K3bDirItem* dir = 0 );

 signals:
  void itemRemoved( K3bDataItem* );
  void newFileItems();
	
 private slots:
  void slotAddQueuedItems();

 protected:
  /** reimplemented from K3bDoc */
  bool loadDocumentData( QDomDocument* );
  /** reimplemented from K3bDoc */
  bool saveDocumentData( QDomDocument* );

  QString documentType() const;

  QString treatWhitespace( const QString& );
 	 		
 private:
  void saveDataItem( K3bDataItem* item, QDomDocument* doc, QDomElement* parent );

  class PrivateItemToAdd {
  public:
    PrivateItemToAdd( const QString& p, K3bDirItem* i )
      :fileInfo(p) { parent = i; }
    QFileInfo fileInfo;
    K3bDirItem* parent;
  };

  QQueue<PrivateItemToAdd> m_queuedToAddItems;
  QTimer* m_queuedToAddItemsTimer;

  K3bRootItem* m_root;
  QString m_name;
  QString m_dummyDir;
  QString m_isoImage;

  QString m_volumeID;
  QString m_applicationID;
  QString m_preparer;
  QString m_publisher;
	
  bool m_deleteImage;
  bool m_onlyCreateImage;

  long m_size;
		
  int m_whiteSpaceTreatment;
	
  // mkisofs options -------------------------------------
  bool m_createRockRidge;    // -r or -R
  bool m_createJoliet;             // -J
  bool m_ISOallowLowercase;   // -allow-lowercase
  bool m_ISOallowPeriodAtBegin;   // -L
  bool m_ISOallow31charFilenames;  // -I
  bool m_ISOomitVersionNumbers;   // -N
  bool m_ISOmaxFilenameLength;     // -max-iso9660-filenames (forces -N)
  bool m_ISOrelaxedFilenames;      // -relaxed-filenames
  bool m_ISOnoIsoTranslate;        // -no-iso-translate
  bool m_ISOallowMultiDot;          // -allow-multidot
  bool m_ISOuntranslatedFilenames;   // -U (forces -d, -I, -L, -N, -relaxed-filenames, -allow-lowercase, -allow-multidot, -no-iso-translate)
  bool m_noDeepDirectoryRelocation;   // -D
  bool m_followSymbolicLinks;       // -f
  bool m_hideRR_MOVED;  // -hide-rr-moved
  bool m_createTRANS_TBL;    // -T
  bool m_hideTRANS_TBL;    // -hide-joliet-trans-tbl
  bool m_padding;           // -pad
	
  int m_isoLevel;
};

#endif
