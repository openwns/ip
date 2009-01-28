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

#ifndef IP_VIRTUALDHCP_HPP
#define IP_VIRTUALDHCP_HPP

#include <WNS/service/nl/Address.hpp>
#include <WNS/service/dll/DataTransmission.hpp>
#include <WNS/node/component/Component.hpp>
#include <WNS/container/Pool.hpp>
#include <WNS/ldk/fun/Main.hpp>
#include <WNS/ldk/Layer.hpp>
#include <WNS/logger/Logger.hpp>
#include <WNS/Singleton.hpp>

namespace ip {

	class DHCPAck
	{
	public:
		DHCPAck()
		{
			address = wns::service::nl::Address();
			subnetMask = wns::service::nl::Address();
		}

		DHCPAck(wns::service::nl::Address address,
			wns::service::nl::Address subnetMask)
		{
			this->address = address;
			this->subnetMask = subnetMask;
		}

		wns::service::nl::Address address;
		wns::service::nl::Address subnetMask;
	};

        /**
	 * @brief IPv4 Virtual DHCP realization.
	 *
	 * \pyco{ip.VirtualDHCP.VirtualDHCP}
	 */
	class VirtualDHCP:
		virtual public wns::ldk::Layer,
		public wns::node::component::Component
	{
		typedef wns::service::nl::Address Address;
		typedef wns::service::dll::UnicastDataTransmission DLLDataTransmission;
	public:
		/**
		 * @brief Components take a parent node and a pyconfig::View for
		 * initialization
		 * @param[in] _node The parent node.
		 * @param[in] _pyco Configuration for this component.
		 */
		VirtualDHCP(
			wns::node::Interface* _node,
			const wns::pyconfig::View& _pyco);

		/**
		 * @brief Component's destructor.
		 */
		virtual ~VirtualDHCP();

		virtual void
		doStartup();

		DHCPAck
		request();

		void
		release(Address);

		/**
		 * @brief Find partner components within your node as given by
		 * the configuration.
		 */
		virtual void
		onNodeCreated();

		/**
		 * @brief Find peer components in other nodes.
		 */
		virtual void
		onWorldCreated();

		virtual void
		onShutdown();

	private:

		/**
		 * @brief The logger for this component.
		 */
		wns::logger::Logger log;

		wns::container::Pool<Address> ipPool;

		Address subnetMask;
	};

	class VirtualDHCPService {

	public:
		typedef wns::service::nl::Address Address;

		VirtualDHCPService();

		void
		addSubnet(std::string subnetIdentifier,
			  VirtualDHCP* server);

		VirtualDHCP*
		getZoneManager(std::string subnetIdentifier);

	private:
		wns::logger::Logger log;

		wns::container::Registry<std::string, VirtualDHCP*> servers;
	};

	typedef wns::SingletonHolder<VirtualDHCPService> TheDHCPService;

} // ip
#endif //_IP_VIRTUALDHCP_HPP


