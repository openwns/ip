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

#ifndef IP_TUNNEL_TUNNELENTRYCOMPONENT_HPP
#define IP_TUNNEL_TUNNELENTRYCOMPONENT_HPP

#include <WNS/service/nl/Service.hpp>
#include <WNS/service/dll/DataTransmission.hpp>
#include <WNS/service/dll/Handler.hpp>
#include <WNS/node/component/Component.hpp>

namespace ip { namespace tunnel {

    /**
     * @brief Tunnel Entries
     *
     * \pyco{ip.Tunnel.TunnelEntryComponent}
     */
	class TunnelEntryComponent:
		public wns::node::component::Component,
		public wns::service::dll::UnicastDataTransmission
	{
	public:
		TunnelEntryComponent(
			wns::node::Interface* _node,
			const wns::pyconfig::View& _pyco);

		virtual ~TunnelEntryComponent();

		virtual void
		onNodeCreated();

		virtual void
		onWorldCreated();

		virtual void
		onShutdown();

		virtual void
		sendData(const wns::service::dll::UnicastAddress& macAddress,
				 const wns::osi::PDUPtr& data,
				 wns::service::dll::protocolNumber protocol,
				 int _dllFlowID);

		virtual wns::service::dll::UnicastAddress
		getMACAddress() const;

	private:

		virtual void
		doStartup();

		wns::service::nl::Service*
		ipService;

		wns::service::nl::Address
		tunnelEntryAddress;

		wns::service::nl::Address
		tunnelExitAddress;

		/**
		 * @brief The logger for this component.
		 */
		wns::logger::Logger log;

	};
} // tunnel
} // ip

#endif // IP_TUNNEL_TUNNELENTRYCOMPONENT_HPP
