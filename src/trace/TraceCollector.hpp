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

#ifndef IP_TRACE_TRACECOLLECTOR_HPP
#define IP_TRACE_TRACECOLLECTOR_HPP

#include <IP/trace/PacketTrace.hpp>

#include <fstream>
#include <list>

namespace ip { namespace trace {

	typedef struct pcap_hdr_s { 
		uint32_t magic_number;   /* magic number */
		uint16_t version_major;  /* major version number */
		uint16_t version_minor;  /* minor version number */
		int32_t  thiszone;       /* GMT to local correction */
		uint32_t sigfigs;        /* accuracy of timestamps */
		uint32_t snaplen;        /* max length of captured packets, in octets */
		uint32_t network;        /* data link type */
	} pcap_hdr_t;

	typedef struct packet_hdr_s {
		uint32_t timestamp;
		uint32_t microseconds;
		uint32_t includedNumOctets;
		uint32_t origNumOctets;
	} packet_hdr_t;

	typedef struct mac_hdr_s {
		uint8_t destination[6];
		uint8_t source[6];
		uint16_t type;
	} mac_hdr_t;

	typedef struct ip_hdr_s {
		uint8_t versionAndLength;
		uint8_t typeOfService;
		uint16_t totalLength;
		uint16_t identification;
		uint16_t flagsAndOffset;
		uint8_t ttl;
		uint8_t protocol;
		uint16_t checksum;
		uint32_t sourceAddress;
		uint32_t destinationAddress;
	} ip_hdr_t;

	typedef struct tcp_hdr_s {
		uint16_t source_port;
		uint16_t destination_port;
		uint32_t sequenceNumber;
		uint32_t ackNumber;
		uint16_t flags; // Header length 6 highest 4 bit
		uint16_t window;
		uint16_t checksum;
		uint16_t urgentPointer;

	} tcp_hdr_t;


	typedef std::list<PacketTrace> PacketTraceContainer;

	class TraceCollector
	{
	public:

		TraceCollector(std::string filename);

		~TraceCollector() {};

		void
		addPacketTrace(PacketTrace pt);

		bool
		hasSomethingToWrite() const;

		void
		write();

	private:

		void
		writeFileHeader(std::ofstream& theFile);

		void
		writePacket(std::ofstream& theFile, const PacketTrace& pt);

		uint16_t
		ipChecksum(ip_hdr_t ipHeader);

		uint16_t
		reverse16(const uint16_t orig);

		uint32_t
		reverse32(const uint32_t orig);

		std::string filename;

		int counter;

		bool writeHeader;

		PacketTraceContainer ptc;

	};


} // trace
} // ip

#endif // IP_TRACE_TRACECOLLECTOR_HPP
