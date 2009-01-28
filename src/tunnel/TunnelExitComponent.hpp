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

#ifndef IP_TUNNEL_TUNNELEXITCOMPONENT_HPP
#define IP_TUNNEL_TUNNELEXITCOMPONENT_HPP

#include <WNS/service/nl/DataHandler.hpp>
#include <WNS/service/dll/Handler.hpp>
#include <WNS/node/component/Component.hpp>
#include <WNS/logger/Logger.hpp>

namespace ip { namespace tunnel {

    /**
     * @brief Tunnel Exits
     *
     * \pyco{ip.Tunnel.TunnelExitComponent}
     */
	class TunnelExitComponent:
		public wns::node::component::Component,
		public wns::service::nl::DataHandler,
		public wns::service::dll::Notification

	{
	public:
		TunnelExitComponent(
			wns::node::Interface* _node,
			const wns::pyconfig::View& _pyco);

		virtual ~TunnelExitComponent();

		virtual void
		onNodeCreated();

		virtual void
		onWorldCreated();

		virtual void
		onShutdown();

		virtual void
		onData(wns::service::nl::Address _sourceIP, const wns::osi::PDUPtr& _pdu);

		virtual void
		registerHandler(wns::service::dll::protocolNumber protocol, wns::service::dll::Handler* handler);

		virtual void
		registerFlowHandler(wns::service::dll::FlowHandler*){};

		virtual void 
		registerIRuleControl(wns::service::dll::IRuleControl*){};


	private:

		virtual void
		doStartup();

		wns::service::dll::Handler* dllHandler;

		/**
		 * @brief The logger for this component.
		 */
		wns::logger::Logger log;

	};
} // tunnel
} // ip

#endif // IP_TUNNEL_TUNNELEXITCOMPONENT_HPP
