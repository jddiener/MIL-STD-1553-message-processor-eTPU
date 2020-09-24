This simulation of an MPC5777C demonstrates the functionality of the MIL-STD-1553 eTPU
drivers and their host API code.  The demo instantiates a single node of a BC terminal on
eTPU-A, a single node of an RT terminal on eTPU-B, and a single node of an MT terminal on
eTPU-C.

For simulation purposes, the BC and RT are directly connected digitally - BC transmit lines 
to RT receive lines, and RT transmit lines to BC receive lines.  The MT receive lines see 
the logical-OR of the BC and RT transmit lines.

The software initializes the eTPU modules and the 3 MIL-STD-1553 nodes (each half of a 
dual-redundant terminal).  It then issues a series of messages of all possible types 
except RT-RT, since the demo only has one RT.

Executing and stepping through this simulation is by far the easiest way for users to 
familiarize themselves with how the MIL-STD-1553 eTPU drivers work.
 