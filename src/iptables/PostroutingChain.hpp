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

#ifndef IP_IPTABLES_POSTROUTINGCHAIN_HPP
#define IP_IPTABLES_POSTROUTINGCHAIN_HPP

#include <IP/iptables/Chain.hpp>
#include <IP/iptables/targets/DLLFlowIDTarget.hpp>
#include <WNS/service/dll/Handler.hpp>

namespace ip { namespace iptables {

	class PostroutingChain:
		public Chain,
		public wns::Cloneable<PostroutingChain>,
		public wns::service::dll::IRuleControl
	{

	public:
		PostroutingChain(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco);

		virtual bool
		activateOutgoing(const IPCommand&) { return true; }

		virtual bool
		activateIncoming(const IPCommand&) { return false; }

		void
		onFlowRemoved(wns::service::dll::FlowID flowID);

		void
		registerDLLFlowIDTarget(targets::DLLFlowIDTarget* target);

	private:

		void
		removeFromDLLFlowIDTarget(wns::service::dll::FlowID flowID);

		targets::DLLFlowIDTarget* dllFlowIDTarget;
	};

} // iptables
} // ip

#endif // IP_IPTABLES_POSTROUTINGCHAIN_HPP
