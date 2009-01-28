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

#include <IP/iptables/filters/SourceDestinationFilter.hpp>
#include <IP/IPHeader.hpp>

#include <WNS/pyconfig/View.hpp>

using namespace ip::iptables::filters;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	SourceDestinationFilter,
	FilterInterface,
	"sourceDestinationFilter",
	wns::PyConfigViewCreator);

SourceDestinationFilter::SourceDestinationFilter(const wns::pyconfig::View& _pyco):
	source(wns::service::nl::Address(_pyco.get<std::string>("source"))),
	sourceMask(wns::service::nl::Address(_pyco.get<std::string>("sourceMask"))),
	destination(wns::service::nl::Address(_pyco.get<std::string>("destination"))),
	destinationMask(wns::service::nl::Address(_pyco.get<std::string>("destinationMask")))
{
}

SourceDestinationFilter::SourceDestinationFilter(wns::service::nl::Address _source,
 												 wns::service::nl::Address _sourceMask,
												 wns::service::nl::Address _destination,
 												 wns::service::nl::Address _destinationMask)
{
	source = _source;
	sourceMask = _sourceMask;
	destination = _destination;
	destinationMask = _destinationMask;
}

bool
SourceDestinationFilter::fires(const IPCommand* ipHeader)
{
	return (source == (ipHeader->peer.source & sourceMask)) && (destination == (ipHeader->peer.destination & destinationMask));
}

bool
SourceDestinationFilter::fires(const IPCommand* ipHeader, const wns::service::tl::IUDPHeader*)
{
    return fires(ipHeader);
}

bool
SourceDestinationFilter::fires(const IPCommand* ipHeader, const wns::service::tl::ITCPHeader*)
{
    return fires(ipHeader);
}

bool
SourceDestinationFilter::operator ==(const SourceDestinationFilter& other) const
{
	return ((source == other.source) &&
			(sourceMask == other.sourceMask) &&
			(destination == other.destination) &&
			(destinationMask == other.destinationMask));
}
