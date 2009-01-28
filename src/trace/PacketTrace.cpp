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

#include <IP/trace/PacketTrace.hpp>

using namespace ip::trace;

PacketTrace::PacketTrace(simTimeType _now,
						 wns::service::dll::UnicastAddress _destinationMAC,
						 wns::service::dll::UnicastAddress _sourceMAC,
						 wns::service::nl::Address _sourceIP,
						 wns::service::nl::Address _destinationIP,
						 int _TTL,
						 wns::service::nl::protocolNumber _protocol,
						 Bit _payloadSize) :
	now(_now),
	destinationMAC(_destinationMAC),
	sourceMAC(_sourceMAC),
	sourceIP(_sourceIP),
	destinationIP(_destinationIP),
	TTL(_TTL),
	protocol(_protocol),
	payloadSize(_payloadSize)
{
}

