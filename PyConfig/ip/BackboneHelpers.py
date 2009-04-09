###############################################################################
# This file is part of openWNS (open Wireless Network Simulator)
# _____________________________________________________________________________
#
# Copyright (C) 2004-2007
# Chair of Communication Networks (ComNets)
# Kopernikusstr. 5, D-52074 Aachen, Germany
# phone: ++49-241-80-27910,
# fax: ++49-241-80-22242
# email: info@openwns.org
# www: http://www.openwns.org
# _____________________________________________________________________________
#
# openWNS is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License version 2 as published by the
# Free Software Foundation;
#
# openWNS is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################

import openwns
from openwns.node import Node
import openwns.distribution
import ip
from ip.Component import IPv4Component
from ip.VirtualDHCP import VirtualDHCP
from ip.Address import ipv4Address
from ip.AddressResolver import FixedAddressResolver, VirtualDHCPResolver
import glue.Glue
from glue.support.Configuration import ShortCutComponent
import copper.Copper


class Station_10BaseT(Node) :
    bufferSize = 100

    linkSpeed = None

    linkError = None

    ip = None

    dll = None

    phy = None

    def __init__(self, name, _wire, _domainName, _defaultRouter, dnsZone="global") :
        super(Station_10BaseT, self).__init__(name);

        self.linkError = openwns.distribution.Fixed(0.0)
        self.linkSpeed = 10E06
        self.bufferSize = 100

        self.phy = copper.Copper.Transceiver(self, _domainName + ".phy", _wire, self.linkError, self.linkSpeed)
        self.dll = glue.support.Configuration.ShortCutComponent(self, _domainName + ".dll", self.phy.dataTransmission, self.phy.notification, self.bufferSize)
        self.ip = IPv4Component(self, name, _domainName)
        # Tell ip about new DLL and how to obtain an IP Address for this interface
        self.ip.addDLL("glue",
                       # Where to get IP Adresses
                       _addressResolver = VirtualDHCPResolver(_wire.name),
                       # Name of ARP zone
                       _arpZone = _wire.name,
                       # We can deliver locally without going to the gateway
                       _pointToPoint = False,
                       # Service names of DLL
                       _dllDataTransmission = self.dll.unicastDataTransmission,
                       _dllNotification = self.dll.unicastNotification)
        # Tell ip about the default route, routes for local delivery will be set for each interface after DHCP
        self.ip.addRoute("0.0.0.0", "0.0.0.0", _defaultRouter, "glue")

class Router_10BaseT(Node) :
    bufferSize = 100

    linkSpeed = None

    linkError = None

    ip = None

    def __init__(self, _name, _domainName) :
        super(Router_10BaseT, self).__init__(_name);
        self.ip = IPv4Component(self, _name, _domainName);
        self.ip.forwarding.config.isForwarding = True
        self.linkError = openwns.distribution.Fixed(0.0)
        self.linkSpeed = 10E06
        self.bufferSize = 100

    def plugOnWire(self, _interfaceName, _wire, _ipAddress):
        phy = copper.Copper.Transceiver(self, _interfaceName + ".phy", _wire, self.linkError, self.linkSpeed)
        dll = glue.support.Configuration.ShortCutComponent(self, _interfaceName + ".dll",
                                                           phy.dataTransmission, phy.notification, self.bufferSize)
        self.ip.addDLL(_interfaceName,
                       # Where to get my IP Address
                       FixedAddressResolver(_ipAddress, "255.255.255.0"),
                       # ARP zone
                       _wire.name,
                       # We can deliver locally
                       False,
                       # DLL service names
                       dll.unicastDataTransmission,
                       dll.unicastNotification)

    def addRoute(self, _netAddress, _netmask, _gateway, _dllName):
        self.ip.addRoute(_netAddress, _netmask, _gateway, _dllName)


