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

from openwns.evaluation import *

def installEvaluation(sim, maxPacketDelay, maxPacketSize, maxBitThroughput, maxPacketThroughput, resolution=1000):

    for dist in ['hop', 'endToEnd']:
        sourceName = 'ip.%s.packet.incoming.delay' % dist
        node = openwns.evaluation.createSourceNode(sim, sourceName )
        node.appendChildren(PDF(name = sourceName,
                                description = 'Incoming packet delay [s]',
                                maxXValue = maxPacketDelay,
                                resolution = resolution,
                                minXValue = 0.0))

        sourceName = 'ip.%s.packet.outgoing.delay' % dist
        node = openwns.evaluation.createSourceNode(sim, sourceName )
        node.appendChildren(PDF(name = sourceName,
                                description = 'Outgoing packet delay [s]',
                                maxXValue = maxPacketDelay,
                                resolution = resolution,
                                minXValue = 0.0))

        sourceName = 'ip.%s.packet.incoming.size' % dist
        node = openwns.evaluation.createSourceNode(sim, sourceName )
        node.appendChildren(PDF(name = sourceName,
                                description = 'Incoming packet size [Bit]',
                                maxXValue = maxPacketSize,
                                resolution = resolution,
                                minXValue = 0.0))

        sourceName = 'ip.%s.packet.outgoing.size' % dist
        node = openwns.evaluation.createSourceNode(sim, sourceName )
        node.appendChildren(PDF(name = sourceName,
                                description = 'Outgoing packet size [Bit]',
                                maxXValue = maxPacketSize,
                                resolution = resolution,
                                minXValue = 0.0))

        for direction in ['incoming', 'outgoing', 'aggregated']:

            sourceName = 'ip.%s.window.%s.bitThroughput' % (dist, direction)
            node = openwns.evaluation.createSourceNode(sim, sourceName )
            node.appendChildren(PDF(name = sourceName,
                                    description = '%s throughput [Bit/s]' % direction.capitalize(),
                                    maxXValue = maxBitThroughput,
                                    resolution = resolution,
                                    minXValue = 0.0))

            sourceName = 'ip.%s.window.%s.compoundThroughput' % (dist, direction)
            node = openwns.evaluation.createSourceNode(sim, sourceName )
            node.appendChildren(PDF(name = sourceName,
                                    description = '%s throughput [Packet/s]' % direction.capitalize(),
                                    maxXValue = maxPacketThroughput,
                                    resolution = resolution,
                                    minXValue = 0.0))

