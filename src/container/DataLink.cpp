/******************************************************************************
 * IPModule   Internet Protocol Implementation                                *
 * __________________________________________________________________________ *
 *                                                                            *
 * Copyright (C) 2005                                                         *
 * Lehrstuhl fuer Kommunikationsnetze (ComNets)                               *
 * Kopernikusstr. 16, D-52074 Aachen, Germany                                 *
 * phone: ++49-241-80-27910 (phone), fax: ++49-241-80-22242                   *
 * email: wns@comnetsrwth-aachen.de, www: http://wns.comnets.rwth-aachen.de/  *
 ******************************************************************************/

#include <IP/container/DataLink.hpp>

using namespace ip::container;

DataLink::DataLink():
  name(""),
  dts(NULL),
  notify(NULL),
  resolver(NULL)
{}

DataLink::DataLink(std::string _name,
				   wns::service::dll::UnicastDataTransmission* _dts,
				   wns::service::dll::Notification* _notify,
				   std::string _arpZone,
				   ip::resolver::ResolverInterface* _resolver,
				   bool _pointToPoint,
				   bool _traceEnabled,
				   trace::TraceCollector* _traceCollector
				   )
{
  name = _name;
  dts = _dts;
  notify = _notify;
  arpZone = _arpZone;
  resolver = _resolver;
  pointToPoint = _pointToPoint;
  traceEnabled = _traceEnabled;
  assure(_traceCollector, "No valid Tracecollector given!");
  traceCollector = _traceCollector;
}

