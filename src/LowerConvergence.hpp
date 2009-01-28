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

#ifndef IP_LOWERCONVERGENCE_HPP
#define IP_LOWERCONVERGENCE_HPP

#include <IP/IPHeader.hpp>
#include <IP/container/DataLink.hpp>

#include <WNS/ldk/CommandTypeSpecifier.hpp>
#include <WNS/ldk/HasReceptor.hpp>
#include <WNS/ldk/HasConnector.hpp>
#include <WNS/ldk/HasDeliverer.hpp>
#include <WNS/ldk/fun/FUN.hpp>
#include <WNS/ldk/Compound.hpp>

#include <WNS/service/dll/DataTransmission.hpp>
#include <WNS/service/dll/Handler.hpp>
#include <WNS/service/dll/Address.hpp>
#include <WNS/pyconfig/View.hpp>

namespace ip {

    /**
     * @brief Convergence to DLL
     *
     * \pyco{ip.Component.LowerConvergence}
     */
	class LowerConvergence :
		public wns::ldk::CommandTypeSpecifier<>,
		public wns::ldk::HasReceptor<>,
		public wns::ldk::HasConnector<>,
		public wns::ldk::HasDeliverer<>,
		public wns::Cloneable<LowerConvergence>,
		virtual public wns::ldk::FunctionalUnit,
		virtual public wns::service::dll::Handler
	{

	public:
		/**
		 * @brief LowerConvergence used to adapt from FUN to service::dll
		 */
		LowerConvergence(wns::ldk::fun::FUN*, const wns::pyconfig::View& pyco);

		~LowerConvergence();

		/**
		 * @brief Implementation for outgoing data flow.
		 */
		virtual void
		doSendData(const wns::ldk::CompoundPtr& compound);

		/**
		 * @brief Implementation for incoming data flow.
		 */
		virtual void
		doOnData(const wns::ldk::CompoundPtr& compound);

		/**
		 * @brief Find friends. This is currently the Routing FU.
		 */
		virtual void
		onFUNCreated();

		/**
		 * @brief Implementation of the dll::DataHandler
		 */
		void
		onData(const wns::osi::PDUPtr& pdu, wns::service::dll::FlowID dllFlowID);

		void
		setDLLs(container::DataLinkContainer dlc);

	private:
		/**
		 * @brief FU outgoing flow control.
		 */
		virtual bool
		doIsAccepting(const wns::ldk::CompoundPtr& compound) const;

		/**
		 * @brief FU outgoing flow control.
		 */
		virtual void
		doWakeup();

		/**
		 * @brief My friends. Currently dependency on the Routing FU command.
		 */

		wns::ldk::CommandReaderInterface* ipHeaderReader;


		/**
		 * @brief My configuration.
		 */
		wns::pyconfig::View pyco;

		/**
		 * @brief My logger.
		 */
		wns::logger::Logger log;

		container::DataLinkContainer dlls;
	};

} // ip
#endif // IP_NODE_COMPONENT_IPV4_LOWERCONVERGENCE_HPP
