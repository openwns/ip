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

#ifndef IP_ROUTING_HPP
#define IP_ROUTING_HPP

#include <IP/IPHeader.hpp>
#include <IP/container/RoutingTable.hpp>
#include <IP/container/DataLink.hpp>

#include <WNS/service/nl/Address.hpp>
#include <WNS/service/dll/DataTransmission.hpp>

#include <WNS/ldk/CommandTypeSpecifier.hpp>
#include <WNS/ldk/HasConnector.hpp>
#include <WNS/ldk/HasReceptor.hpp>
#include <WNS/ldk/HasDeliverer.hpp>
#include <WNS/ldk/Processor.hpp>
#include <WNS/ldk/Command.hpp>

#include <WNS/logger/Logger.hpp>

namespace ip {

	/**
	 * @brief Implementation of IPv4 routing functionality
	 *
	 * \pyco{ip.Component.Routing}
	 */
	class Routing:
		public wns::ldk::CommandTypeSpecifier<>,
		public wns::ldk::HasReceptor<>,
		public wns::ldk::HasConnector<>,
		public wns::ldk::HasDeliverer<>,
		public wns::ldk::Processor<Routing>,
		public wns::Cloneable<Routing>
	{
		typedef wns::service::nl::Address Address;
		typedef wns::service::dll::UnicastDataTransmission DLLDataTransmission;
	public:
		/**
		 * @brief Routing functionality takes the component
		 * and a pyconfig::View for initialization
		 * @param[in] _component The corresponding component
		 * @param[in] _pyco Configuration for this component.
		 */
		Routing(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco);

		/**
		 * @brief Component's destructor.
		 */
		virtual
		~Routing();

		/**
		 * @brief Find my friends. This is currently the UpperConvergence to 
		 * get the AddressingCommand that is used for routing.
		 */
		void
		onFUNCreated();

		void
		addRoute(const wns::service::nl::Address& netAddress,
			 const wns::service::nl::Address& gateway,
			 const wns::service::nl::Address& netMask,
			 std::string dllName);

		void
		printRoutingTable(const wns::service::nl::Address& highlight = Routing::defaultGateway) const;

		void
		processOutgoing(const wns::ldk::CompoundPtr&);

		void
		processIncoming(const wns::ldk::CompoundPtr&);

		void
		setDLLs(container::DataLinkContainer dlc);

	private:
		static wns::service::nl::Address defaultGateway;

		wns::ldk::CommandReaderInterface* ipHeaderReader;

		/**
		 * @brief Try to forward pdu via routing table.
		 * @return Returns true if pdu could be  forwarded, false otherwise.
		 */
		bool
		forwardViaRoutingTable(const wns::ldk::CompoundPtr& c);

		/**
		 * @brief Routing table. Packets with destination address in
		 * unknown ip ranges are sent to next hops due to information
		 * preconfigured in routing table
		 */
		container::RoutingTable rt;

		/**
		 * @brief Configuration for this component
		 */
		wns::pyconfig::View pyco;

		/**
		 * @brief The logger for this component.
		 */
		wns::logger::Logger log;

		container::DataLinkContainer dlls;

	protected:
		/**
		 * @brief Returns the configuration for this component
		 */
		wns::pyconfig::View
		getConfig();
	};

} // ip
#endif // NOT defined IP_ROUTING_HPP


