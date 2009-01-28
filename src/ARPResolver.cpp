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

#include <IP/ARPResolver.hpp>
#include <IP/container/DataLink.hpp>

using namespace ip;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	ARPResolver,
	wns::ldk::FunctionalUnit,
	"ip.arpresolver",
	wns::ldk::FUNConfigCreator);

ARPResolver::ARPResolver(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& config):
	wns::ldk::CommandTypeSpecifier<>(fun),
	wns::ldk::HasReceptor<>(),
	wns::ldk::HasConnector<>(),
	wns::ldk::HasDeliverer<>(),
	wns::Cloneable<ARPResolver>(),
	log(config.get("logger")),
	ipHeaderReader(NULL),
	macID()
{
}

void
ARPResolver::onFUNCreated()
{
 	ipHeaderReader = getFUN()->getCommandReader("ip.ipHeader");
	assure(ipHeaderReader, "No reader for the IP Header available!");
}

void
ARPResolver::doSendData(const wns::ldk::CompoundPtr& compound)
{
	assure(this->isAccepting(compound), "doSendData called although ARPResolver is not accepting");

	assure(ipHeaderReader, "No reader for the IP Header available!");

	IPCommand* ipHeader = ipHeaderReader->readCommand<IPCommand>(compound->getCommandPool());

	if (this->macID == wns::service::dll::UnicastAddress())
	{
		// Address is not resolved, we cannot accept but start address resolution
		std::string arpZone = std::string(ipHeader->local.arpZone);

		VirtualARP* arp = TheARPService::Instance().getZoneManager(arpZone);

                arp->request(*this, ipHeader->local.nextHop);

		this->buffer = compound;
	}
	else
	{
		// Address is resolved

		ipHeader->local.macID = this->macID;

		if (this->getConnector()->hasAcceptor(compound))
		{
			this->getConnector()->getAcceptor(compound)->sendData(compound);
		}
		else
		{
			throw wns::Exception("ARPResolver has no acceptor but should have!");
		}
	}
}

void
ARPResolver::doOnData(const wns::ldk::CompoundPtr& compound)
{
	if (this->getDeliverer()->getAcceptor(compound))
	{
		this->getDeliverer()->getAcceptor(compound)->onData(compound);
	}
	else
	{
		throw wns::Exception("ARPResolver does not have a acceptor");
	}
}

bool
ARPResolver::doIsAccepting(const wns::ldk::CompoundPtr& compound) const
{
	assure(compound, "sendData called with an invalid compound.");

	if (this->buffer == wns::ldk::CompoundPtr())
	{
		return getConnector()->hasAcceptor(compound);
	}
	else
	{
		return false;
	}
}

void
ARPResolver::onAddressResolved(wns::service::dll::UnicastAddress dest)
{
	// We have something to send
	assure(ipHeaderReader, "No reader for the IP Header available!");

	IPCommand* ipHeader = ipHeaderReader->readCommand<IPCommand>(this->buffer->getCommandPool());

	this->macID = dest;

	MESSAGE_BEGIN(NORMAL, log, m, "ARP Response : ");
	m << ipHeader->local.nextHop << " is at "
	  << this->macID;
	MESSAGE_END();

	if ( this-> buffer != wns::ldk::CompoundPtr())
	{

		ipHeader->local.macID = this->macID;

		if (this->getConnector()->hasAcceptor(buffer))
		{
			this->getConnector()->getAcceptor(buffer)->sendData(buffer);
			this->buffer = wns::ldk::CompoundPtr();
		}
		else
		{
			throw wns::Exception("ARPResolver has no acceptor but should have!");
		}
	}

	wakeup();
}

void
ARPResolver::doWakeup()
{
	this->getReceptor()->wakeup();
}
