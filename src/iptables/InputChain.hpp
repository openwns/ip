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

#ifndef IP_IPTABLES_INPUTCHAIN_HPP
#define IP_IPTABLES_INPUTCHAIN_HPP

#include <IP/iptables/Chain.hpp>

namespace ip { namespace iptables {

	class InputChain:
		public Chain,
		public wns::Cloneable<InputChain>
	{

	public:
		InputChain(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco);

		virtual bool
		activateOutgoing(const IPCommand&) { return false; }

		virtual bool
		activateIncoming(const IPCommand&) { return true; }

	};

} // iptables
} // ip

#endif // IP_IPTABLES_INPUTCHAIN_HPP
