// Copyright 2014 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

#include "untitled.h"

#include "MapGraphicsView.h"
#include "ArcGISRuntime.h"

// Uncomment if needed
//#include "Graphic.h"
//#include "SimpleMarkerSymbol.h"
//#include "Point.h"
//#include "ServiceInfoTask.h"
//#include "GeodatabaseFeatureServiceTable.h"

Untitled::Untitled(QWidget *parent)
    : QMainWindow(parent)
{
    // set to openGL rendering
    EsriRuntimeQt::ArcGISRuntime::setRenderEngine(EsriRuntimeQt::RenderEngine::OpenGL);

    m_mapGraphicsView = EsriRuntimeQt::MapGraphicsView::create(m_map, this);
    setCentralWidget(m_mapGraphicsView);
    m_map.setWrapAroundEnabled(false);

    // show Esri logo by default
    m_map.setEsriLogoVisible(true);

    QString path = EsriRuntimeQt::ArcGISRuntime::installDirectory();
    path.append("/sdk/samples/data");
    QDir dataDir(path); // using QDir to convert to correct file separator
    QString pathSampleData = dataDir.path() + QDir::separator();

    //// ArcGIS Online Tiled Basemap Layer
    //m_tiledServiceLayer = EsriRuntimeQt::ArcGISTiledMapServiceLayer("http://services.arcgisonline.com/ArcGIS/rest/services/World_Topo_Map/MapServer");
    //m_map.addLayer(m_tiledServiceLayer);

    //// Local Tiled Basemap Layer using: sdk/samples/data/tpks/Topographic.tpk
    //QString tiledBaseMapLayer = pathSampleData + "tpks" + QDir::separator() + "Topographic.tpk";
    //m_tiledLayer = EsriRuntimeQt::ArcGISLocalTiledLayer(tiledBaseMapLayer);
    //m_map.addLayer(m_tiledLayer);

    //// ArcGIS Online Dynamic Map Service Layer
    //m_dynamicServiceLayer = EsriRuntimeQt::ArcGISDynamicMapServiceLayer("http://sampleserver1.arcgisonline.com/ArcGIS/rest/services/Specialty/ESRI_StateCityHighway_USA/MapServer");
    //m_map.addLayer(m_dynamicServiceLayer);

    //Local Dynamic Layer using: sdk/samples/data/mpks/USCitiesStates.mpk
    /*
  QString dataPath = pathSampleData + "mpks" + QDir::separator() + "USCitiesStates.mpk";
  m_localMapService = EsriRuntimeQt::LocalMapService(dataPath);

  // connect to signal that is emitted when the service is created successfully
  connect(&m_localMapService, SIGNAL(serviceCreationSuccess(const QString&, const QString&)), this, SLOT(onLocalServiceCreationSuccess(const QString&, const QString&)));

  // connect to signal that is emitted when the service failed
  connect(&m_localMapService, SIGNAL(serviceCreationFailure(const QString&)), this, SLOT(onLocalServiceCreationFailure(const QString&)));

  // start the service and the Local Server
  m_localMapService.start();
  */

    // Feature service using: sdk/samples/data/mpks/USCitiesStates.mpk
    /*
  QString localFeatureService = pathSampleData + "mpks" + QDir::separator() + "USCitiesStates.mpk";
  m_localFeatureService = EsriRuntimeQt::LocalFeatureService(localFeatureService);
  m_localFeatureService.setMaximumRecords(3000);

  // connect to signal that is emitted when the service is created successfully
  connect(&m_localFeatureService, SIGNAL(serviceCreationSuccess(const QString&, const QString&)), this, SLOT(onFeatureServiceCreationSuccess(const QString&, const QString&)));

  // connect to signal that is emitted when the service failed
  connect(&m_localFeatureService, SIGNAL(serviceCreationFailure(const QString&)), this, SLOT(onFeatureServiceCreationFailure(const QString&)));

  // start the service and the Local Server
  m_localFeatureService.start();
  */

    // Graphics Layer
    /*
  EsriRuntimeQt::Point point1(0, 0);
  EsriRuntimeQt::SimpleMarkerSymbol redCircle(Qt::red, 8, EsriRuntimeQt::SimpleMarkerSymbolStyle::Circle);
  EsriRuntimeQt::Graphic graphic1(point1, redCircle);
  m_graphicsLayer.addGraphic(graphic1);
  m_map.addLayer(m_graphicsLayer);
  */

    //// connect to signal that is emitted when the map is ready
    //// the mapReady signal is emitted when the Map has obtained a
    //// spatial reference from an added layer
    // connect(&m_map, SIGNAL(mapReady()), this, SLOT(onMapReady()));
}

Untitled::~Untitled()
{
    // stop the Local Map Service
    /*
  if(m_localMapService.status() == EsriRuntimeQt::LocalServiceStatus::Running)
     m_localMapService.stopAndWait();
  */

    // stop the Local Feature Service
    /*
  if(m_localFeatureService.status() == EsriRuntimeQt::LocalServiceStatus::Running)
    m_localFeatureService.stopAndWait();
  */

    // stop the Local Server Instance for local service
    /*
  if (EsriRuntimeQt::LocalServer::instance().isRunning())
    EsriRuntimeQt::LocalServer::instance().shutdownAndWait();
  */

    //// disconnect signals for Local Map Service
    //disconnect(&m_localMapService, SIGNAL(serviceCreationSuccess(const QString&, const QString&)), this, SLOT(onLocalServiceCreationSuccess(const QString&, const QString&)));
    //disconnect(&m_localMapService, SIGNAL(serviceCreationFailure(const QString&)), this, SLOT(onLocalServiceCreationFailure(const QString&)));

    //// disconnect signals for Feature Service
    //disconnect(&m_localFeatureService, SIGNAL(serviceCreationSuccess(const QString&, const QString&)), this, SLOT(onFeatureServiceCreationSuccess(const QString&, const QString&)));
    //disconnect(&m_localFeatureService, SIGNAL(serviceCreationFailure(const QString&)), this, SLOT(onFeatureServiceCreationFailure(const QString&)));

    // disconnect signal for Map
    //disconnect(&m_map, SIGNAL(mapReady()), this, SLOT(onMapReady()));

    m_map.dispose();
    delete m_mapGraphicsView;
}

/*
void Untitled::onMapReady()
{
  // set the map extent
  //m_map.setExtent(EsriRuntimeQt::Envelope(xmin, ymin, xmax, ymax));

  //// Feature Layer
  //// Initialize the FeatureLayer with a GeodatabaseFeatureServiceTable after the Map has
  //// obtained a spatial reference so its features can be projected correctly

  //// specify the URL to create a Service Info Task to get a specific layer by name or id
  //EsriRuntimeQt::ServiceInfoTask serviceTaskInfo("http://sampleserver1.arcgisonline.com/ArcGIS/rest/services/Demographics/ESRI_Census_USA/MapServer/");
  //EsriRuntimeQt::FeatureServiceInfo featureServiceInfo = serviceTaskInfo.createFeatureServiceInfo();
  //QList<EsriRuntimeQt::FeatureLayerInfo> layerInfoList= featureServiceInfo.layers("states");

  //if(layerInfoList.size() > 0 && !layerInfoList.at(0).url().isEmpty())
  //{
  //  // give the feature service table the URL to the feature service layer
  //  EsriRuntimeQt::GeodatabaseFeatureServiceTable featureServiceTable(layerInfoList.at(0).url());
  //  // initialize the feature layer with the feature service table as its feature source
  //  m_featureLayer = EsriRuntimeQt::FeatureLayer(featureServiceTable);
  //  m_map.addLayer(m_featureLayer);
  //}
}
*/

/*
void Untitled::onLocalServiceCreationSuccess(const QString& url, const QString& name)
{
  Q_UNUSED(url);
  Q_UNUSED(name);

   // create the ArcGISDynamicMapServiceLayer using the LocalMapService's url
   m_dynamicLocalServiceLayer = EsriRuntimeQt::ArcGISDynamicMapServiceLayer(m_localMapService.urlMapService());
   m_map.addLayer(m_dynamicLocalServiceLayer);
}
*/

/*
void Untitled::onLocalServiceCreationFailure(const QString& name)
{
  qWarning() << name + " failed to start";
  qWarning() << m_localMapService.error().what();
}
*/

/*
void Untitled::onFeatureServiceCreationSuccess(const QString& url, const QString& name)
{
  Q_UNUSED(url);
  Q_UNUSED(name);

  QString serviceUrl;
  EsriRuntimeQt::FeatureServiceInfo featureServiceInfo = m_localFeatureService.featureServiceInfo();
  QList<EsriRuntimeQt::FeatureLayerInfo> layerInfoList= featureServiceInfo.layers("Cities");

  if(layerInfoList.size() > 0)
    serviceUrl = layerInfoList.at(0).url();

  if (serviceUrl.isEmpty())
  {
    qWarning() << "The required layer does not exist";
    return;
  }

  m_localFeatureLayer = EsriRuntimeQt::ArcGISFeatureLayer(serviceUrl);
  m_map.addLayer(m_localFeatureLayer);
}
*/

/*
void Untitled::onFeatureServiceCreationFailure(const QString& name)
{
  qWarning() << name + " failed to start";
  qWarning() << m_localFeatureService.error().what();
}
*/

