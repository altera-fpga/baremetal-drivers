# CCU Driver

The NCORE CCU (Cache Coherency Unit) is a hardware coherence management system that ensure all requestors 
maintain a consistent view of shared data. The CCU is composed of the following blocks:

### Coherent Agent Interface Unit (CAIU)
The Coherent Agent Interface Unit (CAIU) is a subsystem of the DynamIQ Shared Unit (DSU) that interfaces with the CCU to maintain full coherency. All register access operations are performed via IOCTL and follow this format: `ccu_dsu_<get or set>_<register_name>_reg()`.

### Non-coherent Agent Interface Unit (NCAIU)
The system supports I/O coherency for four subsystems, identified as NCAIU0 to NCAIU3. 
All register access operations are performed via IOCTL and follow this format: `ccu_ncaiu_<get or set>_<register_name>_reg()`.
Please note that the `reg_offset` argument in the IOCTL function must be specified for the corresponding NCAIU subsystem, where x in NCAIUx represents the `reg_offset`.
The subsystems corresponding to each NCAIU block are as follows:
- NCAIU0: From the fabric via the F2SOC interface
- NCAIU1: From the Generic Interrupt Controller (GIC)
- NCAIU2: From the Translation Control Unit (TCU)
- NCAIU3: From the Peripheral Sub-System (PSS) NoC

### Distributed Coherence Engine (DCE)
A DCE implements directory structures to track the location of data. There are two DCEs to improve the directory caches.
All register access operations are performed via IOCTL and follow this format: `ccu_dce_<get or set>_<register_name>_reg()`.
Please note that the `reg_offset` argument in the IOCTL function must be specified for the corresponding DCE subsystem.

### Distributed Memory Interface (DMI)
A DMI provides an AXI master interface to normal memory for coherent and noncoherent transactions. There are two DMIs to improve throughput of the memory subsystem.
All register access operations are performed via IOCTL and follow this format: `ccu_dmi_<get or set>_<register_name>_reg()`.
Please note that the `reg_offset` argument in the IOCTL function must be specified for the corresponding DMI subsystem.

### Distributed Virtual Memory Engine (DVE)
A DVE is a virtual memory manager within the Ncore system. There is one instance of DVE.
All register access operations are performed via IOCTL and follow this format: `ccu_dve_<get or set>_<register_name>_reg()`.

### Distributed I/O Interface (DII)
A DII provides an AXI master interface to I/O devices for non-coherent requests. 
All register access operations are performed via IOCTL and follow this format: `ccu_dii_<get or set>_<register_name>_reg()`.
Please note that the `reg_offset` argument in the IOCTL function must be specified for the corresponding DII subsystem, where x in DIIx represents the `reg_offset`.

There are four DIIs for different usage:
- DII0: F2SOC access to PSS resources
- DII1: access MPFE and IO96B register space
- DII2: access the GIC register space
- DII3: access the OCRAM


More details can be found in [Register Map](https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_CCU_summary.html)