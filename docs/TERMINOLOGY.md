# Public terminology

These are the spellings and expansions used in this repository. Expand a
term on first use when the definition is needed. **Altera** is the vendor,
**Arm** is the architecture vendor, and **Agilex 5** or **Agilex 3** are the
platform names in the bring-up guide. C identifiers, file names, build
variables and quoted firmware output keep their exact spelling.

The entries cite published terminology, not API support claims. A term's
presence does not imply that every device implements every associated feature.
For example, the FCS reference establishes the service name; availability still
depends on the target device and firmware described by the module guide.

| Term | Preferred expansion | Public reference |
|---|---|---|
| HPS | Hard Processor System | [Agilex 5 HPS Technical Reference Manual](https://docs.altera.com/r/docs/814346/current) |
| SDM | Secure Device Manager | [Agilex 5 HPS Technical Reference Manual](https://docs.altera.com/r/docs/814346/current) |
| CCU | Cache Coherency Unit | [Agilex 5 HPS: Cache Coherency Unit](https://docs.altera.com/r/docs/814346/26.1.1/hard-processor-system-technical-reference-manual-agilex-5-socs/cache-coherency-unit-ccu) |
| IOSSM | I/O Subsystem Manager | [Agilex 5 FPGAs: General Purpose I/Os architecture brief](https://docs.altera.com/api/khub/documents/kkXpzF2hsviPh8YTi4XAag/content) |
| FCS | FPGA Crypto Services | [FPGA Crypto Services tutorial user guide](https://altera-fpga.github.io/rel-26.1/embedded-designs/agilex-7/f-series/soc/security/crypto/cryptoservices/ug-fpga-cryptoservice-agx7-soc/) |
| GIC | Generic Interrupt Controller | [Arm: Introducing the Arm architecture](https://developer.arm.com/-/media/Arm%20Developer%20Community/PDF/Learn%20the%20Architecture/Introducing%20the%20Arm%20architecture.pdf) |
| SMMU | System Memory Management Unit | [Arm: Introducing the Arm architecture](https://developer.arm.com/-/media/Arm%20Developer%20Community/PDF/Learn%20the%20Architecture/Introducing%20the%20Arm%20architecture.pdf) |
| MMU | Memory Management Unit | [Arm: Introducing the Arm architecture](https://developer.arm.com/-/media/Arm%20Developer%20Community/PDF/Learn%20the%20Architecture/Introducing%20the%20Arm%20architecture.pdf) |
| OCRAM | On-Chip RAM | [Agilex 5 HPS Technical Reference Manual](https://docs.altera.com/r/docs/814346/current) |
| TF-A | Trusted Firmware-A | [Trusted Firmware-A documentation](https://trustedfirmware-a.readthedocs.io/en/latest/) |

The glossary in [`DOCUMENTATION.md`](../DOCUMENTATION.md#glossary) also covers
general bus, storage and C vocabulary. Add a published reference before adding
a name to this table.
