libname = 'ip'
srcFiles = [
    'src/IPModule.cpp',
    'src/container/RoutingTable.cpp',
    'src/container/DataLink.cpp',
    'src/Component.cpp',
    'src/IPHeader.cpp',
    'src/Routing.cpp',
    'src/Forwarding.cpp',
    'src/UpperConvergence.cpp',
    'src/LowerConvergence.cpp',
    'src/VirtualDHCP.cpp',
    'src/VirtualARP.cpp',
    'src/VirtualDNS.cpp',
    'src/Resolver.cpp',
    'src/FlowIDBuilders.cpp',
    'src/ARPResolver.cpp',
    'src/iptables/Chain.cpp',
    'src/iptables/OutputChain.cpp',
    'src/iptables/InputChain.cpp',
    'src/iptables/ForwardChain.cpp',
    'src/iptables/PostroutingChain.cpp',
    'src/iptables/PreroutingChain.cpp',
    'src/iptables/filters/SourceDestinationFilter.cpp',
    'src/iptables/targets/LoggingTarget.cpp',
    'src/trace/PacketTrace.cpp',
    'src/trace/TraceCollector.cpp',
    'src/tunnel/TunnelEntryComponent.cpp',
    'src/tunnel/TunnelExitComponent.cpp',
    ]

hppFiles = [
'src/ARPResolver.hpp',
'src/Component.hpp',
'src/container/DataLink.hpp',
'src/container/RoutingTable.hpp',
'src/FlowIDBuilders.hpp',
'src/Forwarding.hpp',
'src/IPHeader.hpp',
'src/IPModule.hpp',
'src/iptables/Chain.hpp',
'src/iptables/filters/FilterInterface.hpp',
'src/iptables/filters/SourceDestinationFilter.hpp',
'src/iptables/ForwardChain.hpp',
'src/iptables/InputChain.hpp',
'src/iptables/OutputChain.hpp',
'src/iptables/PostroutingChain.hpp',
'src/iptables/PreroutingChain.hpp',
'src/iptables/targets/LoggingTarget.hpp',
'src/iptables/targets/TargetInterface.hpp',
'src/LowerConvergence.hpp',
'src/Resolver.hpp',
'src/Routing.hpp',
'src/tests/AddressingProviderStub.hpp',
'src/tests/DLLStub.hpp',
'src/trace/PacketTrace.hpp',
'src/trace/TraceCollector.hpp',
'src/tunnel/TunnelEntryComponent.hpp',
'src/tunnel/TunnelExitComponent.hpp',
'src/UpperConvergence.hpp',
'src/VirtualARP.hpp',
'src/VirtualDHCP.hpp',
'src/VirtualDNS.hpp',
]

pyconfigs = [
'ip/Chains.py',
'ip/Component.py',
'ip/VirtualDNS.py',
'ip/Tunnel.py',
'ip/IP.py',
'ip/Logger.py',
'ip/AddressResolver.py',
'ip/Address.py',
'ip/IPTables.py',
'ip/VirtualARP.py',
'ip/VirtualDHCP.py',
'ip/__init__.py',
'ip/BackboneHelpers.py',
'ip/evaluation/__init__.py',
'ip/evaluation/default.py'
]
dependencies = []
Return('libname srcFiles hppFiles pyconfigs dependencies')
