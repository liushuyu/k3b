
#include "k3bdeviceoptiontab.h"
#include "../device/k3bdevicemanager.h"
#include "../device/k3bdevicewidget.h"
#include "../k3b.h"

#include <qlabel.h>
#include <qstring.h>
#include <qlayout.h>

#include <kdialog.h>
#include <klocale.h>
#include <kconfig.h>
#include <kstandarddirs.h>


K3bDeviceOptionTab::K3bDeviceOptionTab( QWidget* parent, const char* name )
  : QWidget( parent, name )
{
  QGridLayout* frameLayout = new QGridLayout( this );
  frameLayout->setSpacing( KDialog::spacingHint() );
  frameLayout->setMargin( 0 );


  // Info Label
  // ------------------------------------------------
  m_labelDevicesInfo = new QLabel( this, "m_labelDevicesInfo" );
  m_labelDevicesInfo->setAlignment( int( QLabel::WordBreak | QLabel::AlignVCenter | QLabel::AlignLeft ) );
  m_labelDevicesInfo->setText( i18n( "K3b tries to detect all your devices properly. You can add not detected devices and change the cdrdao driver for the generic scsi drives. If K3b is not able to detect your drive please run K3bSetup to set the correct permissions." ) );
  // ------------------------------------------------

  m_deviceWidget = new K3bDeviceWidget( k3bMain()->deviceManager(), this );

  frameLayout->addWidget( m_labelDevicesInfo, 0, 0 );
  frameLayout->addWidget( m_deviceWidget, 1, 0 );

  connect( m_deviceWidget, SIGNAL(refreshButtonClicked()), this, SLOT(slotRefreshButtonClicked()) );
}


K3bDeviceOptionTab::~K3bDeviceOptionTab()
{
}


void K3bDeviceOptionTab::readDevices()
{
  m_deviceWidget->init();
}



void K3bDeviceOptionTab::saveDevices()
{
  // save changes to deviceManager
  m_deviceWidget->apply();

  // save the config
  k3bMain()->deviceManager()->saveConfig( k3bMain()->config() );
}


void K3bDeviceOptionTab::slotRefreshButtonClicked()
{
  k3bMain()->deviceManager()->clear();
  k3bMain()->deviceManager()->scanbus();
  
  // this is a little not to hard hack to ensure that we get the "global" k3b appdir
  // k3bui.rc should always be in $KDEDIR/share/apps/k3b/
  QString globalConfigDir = KGlobal::dirs()->findResourceDir( "data", "k3b/k3bui.rc" ) + "k3b";
  QString globalConfigFile =  globalConfigDir + "/k3bsetup";
  KConfig globalConfig( globalConfigFile );
  
  globalConfig.setGroup( "Devices" );
  k3bMain()->deviceManager()->readConfig( &globalConfig );

  m_deviceWidget->init();
}

#include "k3bdeviceoptiontab.moc"
