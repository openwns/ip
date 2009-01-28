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

#ifndef IP_IPHEADER_HPP
#define IP_IPHEADER_HPP

//#include <WNS/ldk/CommandTypeSpecifier.hpp>
//#include <WNS/ldk/Forwarding.hpp>
#include <WNS/ldk/fu/Plain.hpp>

//#include <WNS/ldk/FUNConfigCreator.hpp>
//#include <WNS/ldk/HasReceptor.hpp>
//#include <WNS/ldk/HasConnector.hpp>
//#include <WNS/ldk/HasDeliverer.hpp>

#include <WNS/service/nl/Service.hpp>
#include <WNS/service/nl/Address.hpp>
#include <WNS/service/dll/Address.hpp>
#include <WNS/service/dll/DataTransmission.hpp>
#include <WNS/service/dll/FlowID.hpp>

namespace ip {

	class IPCommand :
		public wns::ldk::Command,
		public wns::IOutputStreamable
	{
	public:
		IPCommand()
		{
			this->local.dllName = "";
			this->local.isForwarded = false;
			this->peer.TTL = 255;
		}

		/** @brief The locally used part of the IP command */
		struct Local
		{
			wns::service::nl::Address nextHop;
			wns::service::dll::UnicastAddress destinationDLLAddress;
			std::string dllName;
			std::string arpZone;
			bool isForwarded;
			wns::service::dll::UnicastAddress macID;
			wns::service::dll::FlowID dllFlowID;
		};
		Local local;

		/** @brief The part of the IP command signalled to the peer entitity */
		struct Peer
		{
			wns::service::nl::Address source;
			wns::service::nl::Address destination;
			wns::service::nl::protocolNumber protocol;
			int TTL;
//			wns::service::dll::FlowID dllFlowID;
		};
		Peer peer;

		struct Magic
		{
		};
		Magic magic;

    private:
		virtual std::string
		doToString() const
		{
			std::stringstream str;
			str << "S: " << peer.source << " D: " << peer.destination
				<< " TTL: " << peer.TTL << " Prot: " << peer.protocol
				<< " Next: " << local.nextHop << " Via : " << local.dllName << " Forw: " << (local.isForwarded ? "True":"False");
			return str.str();
		}

	};

    /**
     * @brief Dummy Functional Unit that only provides the IP Header
     *
     * \pyco{ip.Component.IPHeader}
     */
	class IPHeader :
		public wns::ldk::fu::Plain<IPHeader, IPCommand>
	{
	public:
		IPHeader(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& config);

		virtual ~IPHeader() {}

		// We are blackboard, Resistance is futile
		virtual bool
		doIsAccepting(const wns::ldk::CompoundPtr&) const { return true; }

		virtual void
		doSendData(const wns::ldk::CompoundPtr&) {}

		virtual void
		doWakeup() {}

		virtual void
		doOnData(const wns::ldk::CompoundPtr&) {}

		virtual void
		calculateSizes(const wns::ldk::CommandPool* commandPool, Bit& commandPoolSize, Bit& dataSize) const;

	private:
		/**
		 * @brief Allow for changing the IP-header size from the default
		 *        20*8b
		 */
		Bit headerSize;



	};
} // ip


#endif // IP_IPHEADER_HPP
