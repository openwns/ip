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

#ifndef IP_CONTAINER_DATALINK_HPP
#define IP_CONTAINER_DATALINK_HPP

#include <IP/Resolver.hpp>
#include <IP/VirtualARP.hpp>
#include <IP/trace/TraceCollector.hpp>

#include <WNS/service/dll/DataTransmission.hpp>
#include <WNS/service/dll/Handler.hpp>
#include <WNS/container/Registry.hpp>

namespace ip { namespace container {

	class DataLink
	{
	public:
		DataLink();

		DataLink(std::string name,
				 wns::service::dll::UnicastDataTransmission* dts,
				 wns::service::dll::Notification* notify,
				 std::string arpZone,
				 ip::resolver::ResolverInterface* resolver,
				 bool pointToPoint,
				 bool traceEnabled,
				 trace::TraceCollector* traceCollector);

		~DataLink() {};
		std::string name;
		wns::service::dll::UnicastDataTransmission* dts;
		wns::service::dll::Notification* notify;
		std::string arpZone;
		ip::resolver::ResolverInterface* resolver;
		bool pointToPoint;
		bool traceEnabled;
		trace::TraceCollector* traceCollector;
  };

  typedef wns::container::Registry<std::string, DataLink> DataLinkContainer;

} // container
} // ip

#endif // IP_CONTAINER_DATALINK_HPP
