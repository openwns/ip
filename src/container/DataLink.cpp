/*******************************************************************************
 * This file is part of openWNS (open Wireless Network Simulator)
 * _____________________________________________________________________________
 *
 * Copyright (C) 2004-2007
 * Chair of Communication Networks (ComNets)
 * Kopernikusstr. 5, D-52074 Aachen, Germany
 * phone: ++49-241-80-27910,
 * fax: ++49-241-80-22242
 * email: info@openwns.org
 * www: http://www.openwns.org
 * _____________________________________________________________________________
 *
 * openWNS is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License version 2 as published by the
 * Free Software Foundation;
 *
 * openWNS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include <IP/container/DataLink.hpp>

using namespace ip::container;

DataLink::DataLink():
  name(""),
  dts(NULL),
  resolver(NULL)
{}

DataLink::DataLink(
    wns::ldk::fun::Main* fun_,
    std::string _name,
    wns::service::dll::UnicastDataTransmission* _dts,
    std::string _arpZone,
    ip::resolver::ResolverInterface* _resolver,
    bool _pointToPoint,
    bool _traceEnabled,
    trace::TraceCollector* _traceCollector
    )
{
  fun = fun_;
  name = _name;
  dts = _dts;
  arpZone = _arpZone;
  resolver = _resolver;
  pointToPoint = _pointToPoint;
  traceEnabled = _traceEnabled;
  assure(_traceCollector, "No valid Tracecollector given!");
  traceCollector = _traceCollector;
  handler = NULL;
  ipHeaderReader = fun->getCommandReader("ip.ipHeader");
  assure(ipHeaderReader, "No reader for the IP Header available!");
}


void
DataLink::sendData(const wns::service::dll::UnicastAddress& macAddress,
                   const wns::osi::PDUPtr& data,
                   wns::service::dll::protocolNumber protocol)
{
    if (traceEnabled == true)
    {
        this->traceCompound(data);
    }

    this->dts->sendData(macAddress, data, protocol);
}


wns::service::dll::UnicastAddress
DataLink::getMACAddress() const
{
    return this->dts->getMACAddress();
}

void
DataLink::onData(const wns::osi::PDUPtr& _pdu)
{
    assure(this->handler!=NULL, "No handler set!");

    if (traceEnabled == true)
    {
        this->traceCompound(_pdu);
    }

    handler->onData(_pdu);
}


void
DataLink::registerHandler(wns::service::dll::protocolNumber,
                          wns::service::dll::Handler* handler)
{
    this->handler = handler;
}

void
DataLink::traceCompound(const wns::osi::PDUPtr& data)
{
    wns::ldk::CompoundPtr compound = wns::staticCast<wns::ldk::Compound>(data);

    assure(ipHeaderReader, "No reader for the IP Header available!");
    IPCommand* ipHeader = ipHeaderReader->readCommand<IPCommand>(compound->getCommandPool());

    trace::PacketTrace pt(wns::simulator::getEventScheduler()->getTime(),
                          ipHeader->local.macID,
                          getMACAddress(),
                          ipHeader->peer.source,
                          ipHeader->peer.destination,
                          ipHeader->peer.TTL,
                          ipHeader->peer.protocol,
                          compound->getData()->getLengthInBits());

    wns::service::tl::ITCPHeader* tcpHeader = NULL;
    wns::service::tl::IUDPHeader* udpHeader = NULL;
    wns::ldk::Compound* sdu = dynamic_cast<wns::ldk::Compound*>(compound->getUserData());

    if (sdu != NULL)
    {
        if (ipHeader->peer.protocol == wns::service::nl::TCP)
        {
            tcpHeader = fun->getProxy()->
                getCommand<wns::service::tl::ITCPHeader>(sdu->getCommandPool(), "tcp.tcpHeader");
            pt.addTCPHeader(tcpHeader);
            if (sdu->getData() != NULL)
            {
                pt.updatePayloadSize(sdu->getData()->getLengthInBits());
            }
            else
            {
                pt.updatePayloadSize(0);
            }

        }

        if (ipHeader->peer.protocol == wns::service::nl::UDP)
        {
            udpHeader = fun->getProxy()->
                getCommand<wns::service::tl::IUDPHeader>(sdu->getCommandPool(), "tcp.tcpHeader");
            pt.addUDPHeader(tcpHeader);
            if (sdu->getData() != NULL)
            {
                pt.updatePayloadSize(sdu->getData()->getLengthInBits());
            }
            else
            {
                pt.updatePayloadSize(0);
            }
        }
    }

    assure(traceCollector, "No TraceCollector given in DataLink structure");
    traceCollector->addPacketTrace(pt);
}
