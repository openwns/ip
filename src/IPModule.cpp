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

#include <IP/IPModule.hpp>
#include <IP/Component.hpp>

#include <WNS/pyconfig/helper/Functions.hpp>
#include <WNS/node/Node.hpp>

using namespace ip;

STATIC_FACTORY_REGISTER_WITH_CREATOR(IPModule, wns::module::Base, "ip", wns::PyConfigViewCreator);

IPModule::IPModule(const wns::pyconfig::View& _pyConfigView) :
	wns::module::Module<IPModule>(_pyConfigView),
	log("IP", "IPModule")
{
}

IPModule::~IPModule()
{
}

void IPModule::configure()
{
}

void IPModule::startUp()
{
}

void IPModule::shutDown()
{
}



