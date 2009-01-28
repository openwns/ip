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

#ifndef IP_TRACE_PACKETTRACE_HPP
#define IP_TRACE_PACKETTRACE_HPP

#include <IP/IPHeader.hpp>

#include <WNS/simulator/Bit.hpp>

namespace ip { namespace trace {

	class PacketTrace
	{
	public:
		PacketTrace(simTimeType now,
					wns::service::dll::UnicastAddress destinationMAC,
					wns::service::dll::UnicastAddress sourceMAC,
					wns::service::nl::Address sourceIP,
					wns::service::nl::Address destinationIP,
					int TTL,
					wns::service::nl::protocolNumber protocol,
					Bit payloadSize);

		simTimeType now;
		wns::service::dll::UnicastAddress destinationMAC;
		wns::service::dll::UnicastAddress sourceMAC;
		wns::service::nl::Address sourceIP;
		wns::service::nl::Address destinationIP;
		int TTL;
		wns::service::nl::protocolNumber protocol;
		Bit payloadSize;

	private:
		PacketTrace() {};
	};
}// packet
}// ip


#endif // IP_TRACE_PACKETTRACE_HPP
