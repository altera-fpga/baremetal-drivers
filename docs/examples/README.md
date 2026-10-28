# Public-header examples

These small C functions demonstrate GIC registration, an SDM mailbox request,
ECC polling, SEU monitoring and bridge route metadata. Each includes its module's public
header. The module README describes the sequence and prerequisites.

They are integration helpers, not automatically registered CLI commands. Call
them from an application after satisfying the module's hardware, firmware and
memory-placement requirements. Check returns before using outputs. They do
not inject faults or write flash; GIC changes interrupt state, ECC updates
counters and clears pending status without invoking the registered callback,
SEU initialization writes its scratch buffers, and queue reads
consume entries. The bridge
helper records software route metadata and does not enable a bridge or access memory.

Integrate and link these sources through the normal CMake build for the
final application. That build checks that each file compiles with the public
headers. It does not by itself validate hardware.
