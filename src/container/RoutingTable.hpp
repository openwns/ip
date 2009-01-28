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

#ifndef IP_CONTAINER_ROUTINGTABLEENTRY_HPP
#define IP_CONTAINER_ROUTINGTABLEENTRY_HPP

#include <WNS/pyconfig/View.hpp>
#include <WNS/node/Node.hpp>
#include <WNS/service/nl/Address.hpp>

namespace ip { namespace container {

	class RoutingTableEntry
	{
	public:
		RoutingTableEntry() :
			netaddress(0),
			netmask(0),
			gateway(0),
			dllName("")
		{}

		RoutingTableEntry(const wns::pyconfig::View& _pyco);

		void operator=(const RoutingTableEntry& that)
		{
			netaddress = that.netaddress;
			netmask = that.netmask;
			gateway = that.gateway;
			dllName = that.dllName;
		}

		wns::service::nl::Address netaddress;
		wns::service::nl::Address netmask;
		wns::service::nl::Address gateway;
		std::string dllName;
	};

	typedef std::list<RoutingTableEntry> RoutingTable;

} //container
} //ip
#endif // NOT defined IP_CONTAINER_ROUTINGTABLEENTRY_HPP
