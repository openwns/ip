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

#include <IP/iptables/targets/LoggingTarget.hpp>

using namespace ip::iptables::targets;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	LoggingTarget,
	TargetInterface,
	"loggingTarget",
	wns::PyConfigViewCreator);

LoggingTarget::LoggingTarget(const wns::pyconfig::View& _pyco):
	log(_pyco.get("logger"))
{
}

LoggingTarget::~LoggingTarget()
{
}

TargetResult
LoggingTarget::mangle(ip::IPCommand* ipHeader)
{
	MESSAGE_BEGIN(NORMAL, log, m, "");
	m << *ipHeader;
	MESSAGE_END();

	return CONT;
}

TargetResult
LoggingTarget::mangle(ip::IPCommand* ipHeader, wns::service::tl::ITCPHeader* tcpHeader)
{
	MESSAGE_BEGIN(NORMAL, log, m, "");
	m << *ipHeader;
    m << " TCP : " << tcpHeader->getFlowID();
    if (tcpHeader->getUrgentFlag())
    {
        m << " URG";
    }

    if (tcpHeader->getAckFlag())
    {
        m << " ACK";
    }
    if (tcpHeader->getPushFlag())
    {
        m << " PSH";
    }
    if (tcpHeader->getSynFlag())
    {
        m << " SYN";
    }
    if (tcpHeader->getFinFlag())
    {
        m << " FIN";
    }

	MESSAGE_END();

	return CONT;
}

TargetResult
LoggingTarget::mangle(ip::IPCommand* ipHeader, wns::service::tl::IUDPHeader* udpHeader)
{
	MESSAGE_BEGIN(NORMAL, log, m, "");
	m << *ipHeader;
    m << " UDP : " << udpHeader->getFlowID();
	MESSAGE_END();

	return CONT;
}
