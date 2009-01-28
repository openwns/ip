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

#ifndef IP_ARPRESOLVER_HPP
#define IP_ARPRESOLVER_HPP

#include <IP/IPHeader.hpp>
#include <IP/VirtualARP.hpp>

#include <WNS/ldk/CommandTypeSpecifier.hpp>
#include <WNS/ldk/HasReceptor.hpp>
#include <WNS/ldk/HasConnector.hpp>
#include <WNS/ldk/HasDeliverer.hpp>

#include <WNS/pyconfig/View.hpp>
#include <WNS/logger/Logger.hpp>

#include <WNS/service/dll/Address.hpp>
#include <WNS/Observer.hpp>

namespace ip {
    /**
     * @brief Functional unit that resolves IP to MAC addresses
     *
     * To resolve the MAC addresses this Functional Unit collaborates
     * with the VirtualARP
     *
     * \pyco{ip.Component.ARPResolver}
     */
	class ARPResolver :
		public virtual wns::ldk::FunctionalUnit,
		public wns::ldk::CommandTypeSpecifier<>,
		public wns::ldk::HasReceptor<>,
		public wns::ldk::HasConnector<>,
		public wns::ldk::HasDeliverer<>,
		public wns::Cloneable<ARPResolver>,
                public ResolveCallback
	{
	public:
		ARPResolver(wns::ldk::fun::FUN* fuNet, const wns::pyconfig::View& config);

		virtual void
		onFUNCreated();

		virtual void
		doSendData(const wns::ldk::CompoundPtr& compound);

		virtual void
		doOnData(const wns::ldk::CompoundPtr& compound);

		virtual bool
		doIsAccepting(const wns::ldk::CompoundPtr& compound) const;

		virtual void
		doWakeup();

        virtual void
		onAddressResolved(wns::service::dll::UnicastAddress dest);

	private:
		wns::logger::Logger log;

		wns::ldk::CommandReaderInterface* ipHeaderReader;

		wns::service::dll::UnicastAddress macID;

		wns::ldk::CompoundPtr buffer;
	};
} // ip

#endif // IP_ARPRESOLVER_HPP
