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

#include <IP/UpperConvergence.hpp>

#include <WNS/module/Base.hpp>
#include <WNS/Assure.hpp>

#include <iomanip>

using namespace ip;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	UpperConvergence,
	wns::ldk::FunctionalUnit,
	"ip.upperConvergence",
	wns::ldk::FUNConfigCreator);

UpperConvergence::UpperConvergence(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco) :
	wns::ldk::CommandTypeSpecifier<>(fun),
	wns::ldk::HasReceptor<>(),
	wns::ldk::HasConnector<>(),
	wns::ldk::HasDeliverer<>(),
	wns::ldk::Forwarding<UpperConvergence>(),
	wns::Cloneable<UpperConvergence>(),
	pyco(_pyco),
	//log("IP", "IP.UpperConvergence", wns::module::Base::getService<wns::logger::Master>("W-NS-MSG")),
	log(_pyco.get("logger")),
    ipHeaderReader(NULL),
    ipHeaderFU(NULL)
{
	MESSAGE_SINGLE(VERBOSE, log, "UpperConvergence started.");
}

void
UpperConvergence::onFUNCreated()
{
 	ipHeaderFU = getFUN()->findFriend<IPHeader*>("ip.ipHeader");
	assure(ipHeaderFU, "No FU for the IP Header available!");
 	ipHeaderReader = getFUN()->getCommandReader("ip.ipHeader");
	assure(ipHeaderReader, "No reader for the IP Header available!");
} // onFUNCreated

void
UpperConvergence::sendData(
	const wns::service::nl::Address& sourceAddress,
	const wns::service::nl::Address& peerAddress,
	const wns::osi::PDUPtr& sdu,
	wns::service::nl::protocolNumber protocol,
	wns::service::dll::FlowID dllFlowID)
{
	Bit payloadSize = sdu->getLengthInBits();

	MESSAGE_BEGIN(NORMAL, log, m, "OUT : " << std::setw(18) << sourceAddress);
	m << " -> " << std::setw(18) << peerAddress;
	m << " (" << payloadSize/8 << " bytes)";
	MESSAGE_END()

	wns::ldk::CompoundPtr compound(new wns::ldk::Compound(getFUN()->getProxy()->createCommandPool(), sdu));

	assure(ipHeaderFU, "No FU for the IP Header available!");
	ipHeaderFU->activateCommand(compound->getCommandPool());

	assure(ipHeaderReader, "No reader for the IP Header available!");
	IPCommand* ipHeader = ipHeaderReader->readCommand<IPCommand>(compound->getCommandPool());

	ipHeader->peer.destination = peerAddress;
	ipHeader->peer.source = sourceAddress;
	ipHeader->peer.protocol = protocol;
	ipHeader->local.dllFlowID = dllFlowID;

	if(this->isAccepting(compound)) {
		wns::ldk::Forwarding<UpperConvergence>::doSendData(compound);
	} else {
		// do nothing (throw away compound)
	}
}

void
UpperConvergence::processIncoming(const wns::ldk::CompoundPtr& compound)
{
	assure(ipHeaderReader, "No reader for the IP Header available!");
	IPCommand* ipHeader = ipHeaderReader->readCommand<IPCommand>(compound->getCommandPool());

	assure(handlerRegistry.knows(ipHeader->peer.protocol), "No DataHandler for protocol ");

	MESSAGE_BEGIN(NORMAL, log, m, "IN  : " << std::setw(18) << ipHeader->peer.destination);
	m << " <- " << std::setw(18) << ipHeader->peer.source;
	m << " (" << compound->getData()->getLengthInBits()/8 << " bytes)";
	MESSAGE_END()

	handlerRegistry.find(ipHeader->peer.protocol)->onData(ipHeader->peer.source, compound->getData());
}

void
UpperConvergence::registerHandler(wns::service::nl::protocolNumber  protocol, wns::service::nl::DataHandler* _dh)
{
	assure(_dh, "No valid Handler!");

	this->handlerRegistry.insert(protocol, _dh);
}

const wns::service::nl::Address&
UpperConvergence::getAddress() const
{
	return sourceAddress;
}

void
UpperConvergence::setSourceAddress(wns::service::nl::Address src)
{
	sourceAddress = src;
}
