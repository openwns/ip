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

#include <IP/container/RoutingTable.hpp>

using namespace ip::container;

RoutingTableEntry::RoutingTableEntry(const wns::pyconfig::View& _pyco) :
        netaddress(_pyco.get<std::string>("netaddress")),
        netmask(_pyco.get<std::string>("netmask")),
		gateway(_pyco.get<std::string>("gateway")),
		dllName(_pyco.get<std::string>("dllName"))
{
}
