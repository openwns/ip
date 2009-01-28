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

#ifndef IP_VIRTUALARP_HPP
#define IP_VIRTUALARP_HPP

#include <WNS/service/nl/Address.hpp>
#include <WNS/service/dll/DataTransmission.hpp>
#include <WNS/node/component/Component.hpp>
#include <WNS/container/Registry.hpp>
#include <WNS/ldk/fun/Main.hpp>
#include <WNS/ldk/Layer.hpp>
#include <WNS/logger/Logger.hpp>
#include <WNS/Singleton.hpp>

#include <WNS/Subject.hpp>

namespace ip {

	class ResolveCallback
	{
	public:
		virtual ~ResolveCallback() {}

		virtual void
		onAddressResolved(wns::service::dll::UnicastAddress) = 0;
	};

        /**
	 * @brief IPv4 Virtual ARP realization.
	 *
	 * \pyco{ip.VirtualARP.VirtualARP}
	 */
	class VirtualARP:
		virtual public wns::ldk::Layer,
		public wns::node::component::Component
	{
	public:
		typedef wns::service::nl::Address NLAddress;
		typedef wns::service::dll::UnicastAddress DLLAddress;
		typedef wns::container::Registry<NLAddress, DLLAddress> ARPContainer;

		/**
		 * @brief Components take a parent node and a pyconfig::View for
		 * initialization
		 * @param[in] _node The parent node.
		 * @param[in] _pyco Configuration for this component.
		 */
		VirtualARP(
			wns::node::Interface* _node,
			const wns::pyconfig::View& _pyco);

		virtual void
		doStartup();

		/**
		 * @brief Component's destructor.
		 */
		virtual ~VirtualARP();


		void
		request(ResolveCallback& requester, NLAddress ip);

		void
		bind(DLLAddress macid, NLAddress ip);

		void
		unbind(NLAddress ip);

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

		class ResolveTimeout
		{
		public:
			ResolveTimeout(ResolveCallback& _requester, wns::service::dll::UnicastAddress _address) :
				address(_address),
				requester(_requester)
				{
				}

			void
			operator()()
				{
					requester.onAddressResolved(address);
				}

		private:
			wns::service::dll::UnicastAddress address;
			ResolveCallback& requester;
		};

		simTimeType resolveDelay;

		/**
		 * @brief The logger for this component.
		 */
		wns::logger::Logger log;

		ARPContainer arpLookup;
	};

	class VirtualARPService {

	public:
		typedef wns::service::nl::Address Address;

		VirtualARPService();

		void
		addSubnet(std::string subnetIdentifier,
			  VirtualARP* server);

		VirtualARP*
		getZoneManager(std::string subnetIdentifier);

	private:
		wns::logger::Logger log;

		wns::container::Registry<std::string, VirtualARP*> servers;
	};

	typedef wns::SingletonHolder<VirtualARPService> TheARPService;

} // ip
#endif //_IP_VIRTUALARP_HPP


