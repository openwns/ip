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

#ifndef IP_IPTABLES_CHAIN_HPP
#define IP_IPTABLES_CHAIN_HPP

#include <IP/IPHeader.hpp>
#include <IP/iptables/filters/FilterInterface.hpp>
#include <IP/iptables/targets/TargetInterface.hpp>
#include <IP/iptables/Rule.hpp>
#include <IP/iptables/IRuleControl.hpp>

#include <WNS/ldk/CommandTypeSpecifier.hpp>
#include <WNS/ldk/HasConnector.hpp>
#include <WNS/ldk/HasReceptor.hpp>
#include <WNS/ldk/HasDeliverer.hpp>
#include <WNS/ldk/Processor.hpp>
#include <WNS/ldk/Command.hpp>

#include <WNS/ldk/fun/FUN.hpp>
#include <WNS/service/dll/DataTransmission.hpp>
#include <WNS/service/dll/Handler.hpp>
#include <WNS/service/tl/TCPHeader.hpp>

//#include <list>
#include <map>

namespace ip { namespace iptables {

	/**
	 * @brief Implementation of IPv4 routing functionality
	 */
	class Chain:
		public wns::ldk::CommandTypeSpecifier<>,
		public wns::ldk::HasReceptor<>,
		public wns::ldk::HasConnector<>,
		public wns::ldk::HasDeliverer<>,
		virtual public wns::ldk::FunctionalUnit,
		public ip::iptables::IRuleControl
	{
	public:
		typedef std::list<ip::iptables::Rule> RuleContainer;

		Chain(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco);

		virtual
		~Chain();

		virtual void
		onFUNCreated();

		virtual bool
		doIsAccepting(const wns::ldk::CompoundPtr&) const;

		virtual void
		doSendData(const wns::ldk::CompoundPtr&);

		virtual void
		doWakeup();

		virtual void
		doOnData(const wns::ldk::CompoundPtr&);

		targets::TargetResult
        activateChain(IPCommand*, wns::service::tl::ITCPHeader*, wns::service::tl::IUDPHeader*);

		/**
		 * @brief Derived Classed need to decide here if the IP packet is to be
		 * processed in the outgoing path
		 */
		virtual bool
		activateOutgoing(const IPCommand&) = 0;

		/**
		 * @brief Derived Classed need to decide here if the IP packet is to be
		 * processed in the incoming path
		 */
		virtual bool
		activateIncoming(const IPCommand&) = 0;


		/**
		 * @brief Implementation of IRuleControl.
		 */

		/**
		 * @brief Adds Rule to the RuleContainer.
		 */
		virtual void
		addRule(ip::iptables::Rule);

		/**
		 * @brief Removes all Rules from the RuleContainer with ruleTag ruleTag.
		 */
		virtual void
		removeRules(ip::iptables::Rule::RuleTag ruleTag);

		virtual bool
		hasRules(ip::iptables::Rule::RuleTag ruleTag);

		virtual ip::iptables::Rule
		getRule(ip::iptables::Rule::RuleTag ruleTag);

		virtual void
		showRules();

	protected:
		/**
		 * @brief The logger for this component.
		 */
		wns::logger::Logger log;

	private:
		wns::ldk::CommandReaderInterface* ipHeaderReader;
		RuleContainer rules;
	};


}// iptables
}// ip

#endif // IP_IPTABLES_CHAIN_HPP
