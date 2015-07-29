#include "io_apic.h"

void io_apic_init(void){
	int i = 0;	
	union ioapicver_union icu;
	union ioredtbl_union itu;	
	io_apic_mmr =  (volatile struct IO_APIC_MMR*)IOAPIC;	
	icu.w1 = io_apic_read(SEL_IOAPICVER);
	io_apic_info.max_redirection_entry = icu.ioapicver.maximum_redirection_entry;
	/* 
	Mark all interrupts edge-triggered, disabled,
  	and not routed to any CPUs.
	*/
	itu.ioredtbl.trigger = 0;	
	itu.ioredtbl.mask = 1;
	itu.ioredtbl.dest = 0;
	for(i = 0 ; i <= io_apic_info.max_redirection_entry; i++){
		io_apic_write(SEL_TABLE+2*i,itu.w1);
		io_apic_write(SEL_TABLE+2*i+1,itu.w2);	
	}

}

unsigned int io_apic_read(unsigned int address_offset){
	io_apic_mmr->ioregsel = address_offset;
	return io_apic_mmr->iowin;
}
void io_apic_write(unsigned int address_offset, unsigned int data)
{
  	io_apic_mmr->ioregsel = address_offset;
 	io_apic_mmr->iowin = data;
}
void io_apic_enable(int irq){
	union ioredtbl_union itu;
	itu.ioredtbl.mask = 0;
	io_apic_write(SEL_TABLE+2*irq,itu.w1);	
}

