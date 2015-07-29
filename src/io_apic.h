/*
The I/O APIC spec
http://www.intel.com/design/chipsets/datashts/29056601.pdf
*/

#define IOAPIC  0xFEC00000   // Default physical address of IO APIC

#define SEL_IOAPICID    0x00  // Register index: ID
#define SEL_IOAPICVER   0x01  // Register index: version
#define SEL_TABLE  	0x10  // Redirection table base

struct IOAPICVER{
	unsigned int version 		  : 8,
		__reserved_1		  : 8,
		maximum_redirection_entry : 8,
 		__reserved_2		  : 8;
} __attribute__ ((packed));

struct IOREDTBL{
	unsigned int   vector  	:  8,
		delivery_mode   :  3,   /* 000: FIXED
                                 	 * 001: lowest prio
                                	 * 111: ExtINT
                                 	 */
		dest_mode       :  1,   /* 0: physical, 1: logical */
		delivery_status :  1,
       		polarity        :  1,
       		irr             :  1,
      	        trigger         :  1,   /* 0: edge, 1: level */
                mask            :  1,   /* 0: enabled, 1: disabled */
                __reserved_1    : 15;
	unsigned int   __reserved_2    : 24,
       	        dest            :  8;
} __attribute__ ((packed));

union ioredtbl_union{
	struct {
		unsigned int w1,w2;
	};
	struct IOREDTBL ioredtbl;
};

union ioapicver_union{
	unsigned int w1;
	struct IOAPICVER ioapicver;
};




struct IO_APIC_MMR{
	unsigned int ioregsel;
	unsigned int pad[3];
	unsigned int iowin;
};

struct IO_APIC_INFO{
	int max_redirection_entry;	
};

volatile struct IO_APIC_MMR * io_apic_mmr;
volatile struct IO_APIC_INFO io_apic_info;



void io_apic_init(void);
unsigned int io_apic_read(unsigned int address_offset);
void io_apic_write(unsigned int address_offset, unsigned int data);
void io_apic_enable(int irq);




