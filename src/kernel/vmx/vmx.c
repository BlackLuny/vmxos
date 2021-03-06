#include "vmx.h"

unsigned long long vmxon_ptr;
unsigned long long vmcs_ptr;
SEGMENT_SELECTOR gdtr;

char* vmx_instruction_errors[] = 
{
	"0 No errors",
	"1 VMCALL executed in VMX root operation",
	"2 VMCLEAR with invalid physical address",
	"3 VMCLEAR with VMXON pointer",
	"4 VMLAUNCH with non-clear VMCS",
	"5 VMRESUME with non-launched VMCS",
	"6 VMRESUME after VMXOFF (VMXOFF and VMXON between VMLAUNCH and VMRESUME)",
	"7 VM entry with invalid control field(s)",
	"8 VM entry with invalid host-state field(s)",
	"9 VMPTRLD with invalid physical address",
	"10 VMPTRLD with VMXON pointer",
	"11 VMPTRLD with incorrect VMCS revision identifier",
	"12 VMREAD/VMWRITE from/to unsupported VMCS component",
	"13 VMWRITE to read-only VMCS component",
	"14 unknown",
	"15 VMXON executed in VMX root operation",
	"16 VM entry with invalid executive-VMCS pointer",
	"17 VM entry with non-launched executive VMCS2",
	"18 VM entry with executive-VMCS pointer not VMXON pointer (when attempting to deactivate the dual-monitor treatment of SMIs and SMM)",
	"19 VMCALL with non-clear VMCS (when attempting to activate the dual-monitor treatment of SMIs and SMM)",
	"20 VMCALL with invalid VM-exit control fields",
	"21 unknown",
	"22 VMCALL with incorrect MSEG revision identifier (when attempting to activate the dualmonitor treatment of SMIs and SMM)",
	"23 VMXOFF under dual-monitor treatment of SMIs and SMM",
	"24 VMCALL with invalid SMM-monitor features (when attempting to activate the dualmonitor treatment of SMIs and SMM)",
	"25 VM entry with invalid VM-execution control fields in executive VMCS (when attempting to return from SMM)",
	"26 VM entry with events blocked by MOV SS.",
	"27 unknown",
	"28 Invalid operand to INVEPT/INVVPID."
};

char* vmx_exit_reasons[] =
{
	"0 Exception or non-maskable interrupt (NMI)",
	"1 External interrupt",
	"2 Triple fault",
	"3 INIT signal",
	"4 Start-up IPI (SIPI)",
	"5 I/O system-management interrupt (SMI)",
	"6 Other SMI",
	"7 Interrupt window",
	"8 NMI window",
	"9 Task switch",
	"10 CPUID",
	"11 GETSEC",
	"12 HLT",
	"13 INVD",
	"14 INVLPG",
	"15 RDPMC",
	"16 RDTSC",
	"17 RSM",
	"18 VMCALL",
	"19 VMCLEAR",
	"20 VMLAUNCH",
	"21 VMPTRLD",
	"22 VMPTRST",
	"23 VMREAD",
	"24 VMRESUME",
	"25 VMWRITE",
	"26 VMXOFF",
	"27 VMXON",
	"28 Control-register accesses",
	"29 MOV DR",
	"30 I/O instruction",
	"31 RDMSR",
	"32 WRMSR",
	"33 VM-entry failure due to invalid guest state",
	"34 VM-entry failure due to MSR loading",
	"34 unknown",
	"36 MWAIT",
	"37 Monitor trap flag",
	"38 unknown",
	"39 MONITOR",
	"40 PAUSE",
	"41 VM-entry failure due to machine check",
	"42 unknown",
	"43 TPR below threshold",
	"44 APIC access",
	"45 unknown",
	"46 Access to GDTR or IDTR",
	"47 Access to LDTR or TR",
	"48 EPT violation",
	"49 EPT misconfiguration",
	"50 INVEPT",
	"51 RDTSCP",
	"52 VMX-preemption timer expired",
	"53 INVVPID",
	"54 WBINVD",
	"55 XSETBV"
};
