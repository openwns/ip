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

import wns
from Logger import Logger

class SourceAddressFilter:

    def __init__(self, subnetIdentifier, dllDataTransmission, addressResolver, parentLogger):
        self.subnetIdentifier = subnetIdentifier
        self.logger = Logger("SAF", True, parentLogger)
        self.dllDataTransmission = dllDataTransmission
        self.addressResolver = addressResolver

class RoutingFilter:
    def __init__(self, dllDataTransmission, subnetIdentifier, parentLogger):
        self.logger = Logger("RAF", True, parentLogger)
        self.subnetIdentifier = subnetIdentifier
        self.dllDataTransmission = dllDataTransmission

class Chain:

    sourceAddressResolver = None

    def __init__(self, name, parentLogger):
        self.logger = Logger(name, True, parentLogger)
        self.filters = []

    def addFilter(self, filter):
        self.filters.append(filter)
