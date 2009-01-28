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

#ifndef IP_IPTABLES_PREROUTINGCHAIN_HPP
#define IP_IPTABLES_PREROUTINGCHAIN_HPP

#include <WNS/ldk/fun/FUN.hpp>
#include <IP/iptables/Chain.hpp>
#include <IP/iptables/IRuleControl.hpp>
#include <IP/iptables/targets/TargetInterface.hpp>
#include <IP/iptables/targets/DLLFlowIDTarget.hpp>

namespace ip { namespace iptables {

	class PreroutingChain:
		public Chain,
		public wns::Cloneable<PreroutingChain>
	{

	public:
		PreroutingChain(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco);

		virtual void
		onFUNCreated();

		virtual bool
		activateOutgoing(const IPCommand&) { return false; }

		virtual bool
		activateIncoming(const IPCommand&) { return true; }

	private:
		wns::ldk::fun::FUN* fun;
		ip::iptables::IRuleControl* postroutingChain;
		wns::logger::Logger log;
		ip::iptables::targets::DLLFlowIDTarget* dllFlowIDTarget;
	};

} // iptables
} // ip

#endif // IP_IPTABLES_PREROUTINGCHAIN_HPP
