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

#ifndef IP_FORWARDING_HPP
#define IP_FORWARDING_HPP

#include <IP/IPHeader.hpp>

#include <WNS/ldk/CommandTypeSpecifier.hpp>
#include <WNS/ldk/HasConnector.hpp>
#include <WNS/ldk/HasReceptor.hpp>
#include <WNS/ldk/HasDeliverer.hpp>
#include <WNS/ldk/Dropper.hpp>
#include <WNS/ldk/Command.hpp>
#include <WNS/ldk/Delayed.hpp>

#include <WNS/logger/Logger.hpp>
#include <WNS/service/nl/Address.hpp>

namespace ip {

	/**
	 * @brief Command used by the Forwarding FU. The TTL is handled here.
	 */
	class ForwardingCommand :
		public wns::ldk::Command
	{
		friend class Forwarding;
	public:
		struct {

		} local;

		struct {

		} peer;

		struct {
		} magic;
	};

	/**
	 * @brief IPv4 Handler interface
	 *
	 * \pyco{ip.Component.Forwarding}
	 */
	class Forwarding :
		public wns::ldk::CommandTypeSpecifier<ForwardingCommand>,
		public wns::ldk::HasReceptor<>,
		public wns::ldk::HasConnector<>,
		public wns::ldk::HasDeliverer<>,
		public wns::ldk::Delayed<Forwarding>,
		public wns::Cloneable<Forwarding>
	{
		typedef wns::service::nl::Address Address;
		typedef std::list<wns::service::nl::Address> AddressContainer;

	public:
		/**
		 * @brief Forwarding functionality takes the component
		 * and a pyconfig::View for initialization
		 * @param[in] _component The corresponding component
		 * @param[in] _pyco Configuration for this component.
		 */
		Forwarding(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco);

		/**
		 * @brief Destructor
		 */
		virtual
		~Forwarding()
		{}

		virtual void
		onFUNCreated();

		virtual void processIncoming(const wns::ldk::CompoundPtr& compound);
		virtual void processOutgoing(const wns::ldk::CompoundPtr&);
		virtual bool hasCapacity() const;
		virtual const wns::ldk::CompoundPtr hasSomethingToSend() const;
		virtual wns::ldk::CompoundPtr getSomethingToSend();

/*		void
		doSendData(const wns::ldk::CompoundPtr& compound);

		void
		doOnData(const wns::ldk::CompoundPtr& compound);

		bool
		doIsAccepting(const wns::ldk::CompoundPtr& compound) const;

		void
		doWakeup();*/

		void
		addListeningAddress(wns::service::nl::Address listenerAddress);

		void
		removeListeningAddress(wns::service::nl::Address listenerAddress);

	private:
		/**
		 * @brief Helper function to decide wether the received compound is for this station.
		 */
		bool
		reachedDestination(const wns::ldk::CompoundPtr& compound);

		/**
		 * @brief Helper function to decide wether the compound can be forwarded to another hop.
		 */
		bool
		putOnNextHop(const wns::ldk::CompoundPtr& compound);

		wns::ldk::CommandReaderInterface* ipHeaderReader;

		/**
		 * @brief Configuration of this component
		 */
		wns::pyconfig::View pyco;

		/**
		 * @brief The logger for this component.
		 */
		wns::logger::Logger log;

		/**
		 * @brief Decide wether incoming data is forwarded to another
		 * connected dll if it's not addressed to itself
		 */
		bool isForwarding;

		/**
		 * @brief The TTL to use for new compounds
		 */
		int ttl;

		AddressContainer listeningAddresses;

		wns::ldk::CompoundPtr buffer;

	protected:
		/**
		 * @brief Returns the configuration for this component
		 */
		wns::pyconfig::View
		getConfig();

	};
} // ip
#endif //_IP_FORWARDING_HPP


