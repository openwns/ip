##############################################################################
# IPModule   Internet Protocol Implementation                                #
# __________________________________________________________________________ #
#                                                                            #
# Copyright (C) 2005                                                         #
# Lehrstuhl fuer Kommunikationsnetze (ComNets)                               #
# Kopernikusstr. 16, D-52074 Aachen, Germany                                 #
# phone: ++49-241-80-27910 (phone), fax: ++49-241-80-22242                   #
# email: wns@comnetsrwth-aachen.de, www: http://wns.comnets.rwth-aachen.de/  #
##############################################################################

from Logger import Logger
from wns.Node import Node
from wns.Node import Component


class VirtualDNS(Component):

    nameInComponentFactory = "ip.VDNS"

    zoneIdentifier = None

    logger = None

    def __init__(self, node, zoneIdentifier):
        super(VirtualDNS, self).__init__(node, zoneIdentifier)
        self.zoneIdentifier = zoneIdentifier
        self.logger = Logger(self.zoneIdentifier, True, node.logger)


class VirtualDNSServer(Node):
    def __init__(self, name, zoneIdentifier):
        super(VirtualDNSServer, self).__init__(name)
        vdns = VirtualDNS(self, zoneIdentifier)

