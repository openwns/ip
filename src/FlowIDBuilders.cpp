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

#include <IP/FlowIDBuilders.hpp>
#include <IP/IPHeader.hpp>

#include <WNS/ldk/fun/FUN.hpp>

using namespace ip;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	OutputBuffersFlowIDBuilder,
	wns::ldk::KeyBuilder,
	"ip.outputBuffersFlowIDBuilder",
	wns::ldk::FUNConfigCreator);


OutputBuffersFlowIDBuilder::OutputBuffersFlowIDBuilder(wns::ldk::fun::FUN* _fun,
			     const wns::pyconfig::View& _config) :
	config(_config),
	fun(_fun)
{
}

void
OutputBuffersFlowIDBuilder::onFUNCreated()
{
 	ipHeaderReader = this->fun->getCommandReader("ip.ipHeader");
	assure(ipHeaderReader, "No reader for the IP Header available!");
}

wns::ldk::ConstKeyPtr
OutputBuffersFlowIDBuilder::operator()(const wns::ldk::CompoundPtr& _compound, int _direction) const
{
	assure(ipHeaderReader, "No reader for the IP Header available!");

	// Only outgoing packets are separated. Incoming do not get separated and
	// especially not by the local part of the peer entity. We use Address
	// 0.0.0.0 for all incoming packets

	if(_direction == 1)
	{
		// Outgoing Packets
		IPCommand* ipHeader = ipHeaderReader->readCommand<IPCommand>(_compound->getCommandPool());
		return wns::ldk::ConstKeyPtr(new IPAddressKey(ipHeader->local.nextHop));
	}
	else
	{
		// Incoming Packets
		wns::service::nl::Address dummy;
		return wns::ldk::ConstKeyPtr(new IPAddressKey(dummy));
	}
}
