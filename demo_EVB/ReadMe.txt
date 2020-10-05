This MPC5777C S32DS project demonstrates the functionality of the MIL-STD-1553 eTPU drivers 
and their host API code.  The demo instantiates a single node of a BC terminal on
eTPU-A, a single node of an RT terminal on eTPU-B, and a single node of an MT terminal on
eTPU-C.  The terminal nodes use the following eTPU channels/pads:

BC:
	ETPUA0	- BC_RX_P
	ETPUA1	- BC_RX_N
	ETPUA2	- BC_TX_P
	ETPUA3	- BC_TX_N

RT:
	ETPUB0	- RT_RX_P
	ETPUB1	- RT_RX_N
	ETPUB2	- RT_TX_P
	ETPUB3	- RT_TX_N

MT:
	ETPUC0	- MT_RX_P
	ETPUC1	- MT_RX_N

For basic testing purposes, all the connections were kept in the digital domain, but the 
setup could also be connected to a true 1553 bus via additional hardware.  The basic digital 
connections are as follows, with EVB port numbers listed:

1553_P <- ETPUA2/BC_TX_P/PN3 + ETPUB2/RT_TX_P/PR3 ('OR'd together)
1553_N <- ETPUA3/BC_TX_N/PN2 + ETPUB3/RT_TX_N/PR2 ('OR'd together)

ETPUA0/BC_RX_P/PN1 <-1553_P
ETPUA1/BC_RX_N/PN0 <-1553_N

ETPUB0/RT_RX_P/PR1 <-1553_P
ETPUB1/RT_RX_N/PR0 <-1553_N

ETPUC0/MT_RX_P/PV1 <-1553_P
ETPUC1/MT_RX_N/PV0 <-1553_N

1553_P / 1553_N are a digital representation of the 1553 bus.

                                                 1553 BUS
------                                               |
|    |  -------------------------------->            |
| BC |                                    OR ------> |
|    |  <-----                     |---->            |
------       |                     |                 |
             |                     |                 |
------       \                     |                 |
|    |  ------|--------------------|                 |
| RT |       /                                       |
|    |  <-----                                       |
------       |                                       |
             |                                       |
------       |                                       |
|    |       |                                       |
| MT |       |                                       |
|    |  <----|---------------------------------------|
------                                               |


After initializing the eTPU modules, the demo software loops continually doing the following:
- initializes the 3 nodes
- BC waits for bus idle and then a series of messages are issued (all types except RT-RT)
- after each message, the status of each node is checked to ensure it is as expected
- shutdown the 3 nodes and pause for a short time (approx. 10ms)
