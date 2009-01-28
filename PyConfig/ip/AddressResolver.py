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

class VirtualDHCPResolver:

    nameInResolverFactory = "ip.resolver.vdhcp"

    vdhcpZone = None

    def __init__(self, vdhcpZone):
        """ DHCPZone is a simple string to group stations on the same subnet to be server by one VDHCPServer"""
        self.vdhcpZone = vdhcpZone

class FixedAddressResolver:

    nameInResolverFactory = "ip.resolver.fixed"

    address = None

    subnetMask = None

    def __init__(self, address, subnetMask):
        self.address = address
        self.subnetMask = subnetMask
