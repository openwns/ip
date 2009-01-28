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

#ifndef IP_IPTABLES_FORWARDCHAIN_HPP
#define IP_IPTABLES_FORWARDCHAIN_HPP

#include <IP/iptables/Chain.hpp>

namespace ip { namespace iptables {

	class ForwardChain:
		public Chain,
		public wns::Cloneable<ForwardChain>
	{

	public:
		ForwardChain(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco);

		virtual bool
		activateOutgoing(const IPCommand& ipHeader) { return ipHeader.local.isForwarded; }

		virtual bool
		activateIncoming(const IPCommand&) { return false; }

	};

} // iptables
} // ip

#endif // IP_IPTABLES_FORWARDCHAIN_HPP
