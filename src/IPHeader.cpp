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

#include <IP/IPHeader.hpp>

using namespace ip;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	IPHeader,
	wns::ldk::FunctionalUnit,
	"ip.ipHeader",
	wns::ldk::FUNConfigCreator);


IPHeader::IPHeader(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& pyco):
	wns::ldk::fu::Plain<IPHeader, IPCommand>(fun),
	headerSize(pyco.get<Bit>("headerSize"))
{
}

void
IPHeader::calculateSizes(const wns::ldk::CommandPool* commandPool, Bit& commandPoolSize, Bit& dataSize) const
{
	getFUN()->calculateSizes(commandPool, commandPoolSize, dataSize, this);

	// IP header size is 20 byte
	commandPoolSize = headerSize;
}

