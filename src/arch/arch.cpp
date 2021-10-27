#include "arch.hpp"
#include "exception.hpp"

namespace maat
{
    
int Arch::bits() const
{
    return _bits;
}

int Arch::octets() const
{
    return _bits/8;
}

const std::string& Arch::reg_name(reg_t num) const 
{
    for (auto it = reg_map.begin(); it != reg_map.end(); ++it)
        if (it->second == num)
            return it->first;

    throw runtime_exception(
        Fmt() << "Arch::reg_name() got unknown reg num: "
        << num
        >> Fmt::to_str
    );
}

reg_t Arch::reg_num(const std::string& name) const 
{
    auto it = reg_map.find(name);
    if (it == reg_map.end())
        throw runtime_exception(Fmt ()
                << "Arch::reg_num() got unknown reg name: " << name
                >> Fmt::to_str
                );
    return it->second;
}

namespace X86
{
    ArchX86::ArchX86(): Arch(Arch::Type::X86, 32, X86::NB_REGS)
    {
        available_modes = {CPUMode::X86};
        reg_map =
        {
            {"eax", EAX},
            {"ebx", EBX},
            {"ecx", ECX},
            {"edx", EDX},
            {"edi", EDI},
            {"esi", ESI},
            {"ebp", EBP},
            {"esp", ESP},
            {"eip", EIP},
            {"cs", CS},
            {"ds", DS},
            {"es", ES},
            {"fs", FS},
            {"gs", GS},
            {"ss", SS},
            {"cf", CF},
            {"pf", PF},
            {"af", AF},
            {"zf", ZF},
            {"sf", SF},
            {"tf", TF},
            {"if", IF},
            {"df", DF},
            {"of", OF},
            {"iopl", IOPL},
            {"vm", VM},
            {"nt", NT},
            {"rf", RF},
            {"ac", AC},
            {"vip", VIP},
            {"vif", VIF},
            {"id", ID},
            {"tsc", TSC},
            {"mm0", MM0},
            {"mm1", MM1},
            {"mm2", MM2},
            {"mm3", MM3},
            {"mm4", MM4},
            {"mm5", MM5},
            {"mm6", MM6},
            {"mm7", MM7},
            {"zmm0", ZMM0},
            {"zmm1", ZMM1},
            {"zmm2", ZMM2},
            {"zmm3", ZMM3},
            {"zmm4", ZMM4},
            {"zmm5", ZMM5},
            {"zmm6", ZMM6},
            {"zmm7", ZMM7},
            {"xcr0", XCR0},
            {"fpucw", FPUCW},
            {"fpusw", FPUSW},
            {"fputw", FPUTW},
            {"fpuip", FPUIP},
            {"fpudp", FPUDP},
            {"fpuop", FPUOP},
            {"c0", C0},
            {"c1", C1},
            {"c2", C2},
            {"c3", C3},
            {"cr0", CR0},
            {"st0", ST0},
            {"st1", ST1},
            {"st2", ST2},
            {"st3", ST3},
            {"st4", ST4},
            {"st5", ST5},
            {"st6", ST6},
            {"st7", ST7}
        };
    }

    size_t ArchX86::reg_size(reg_t reg_num) const 
    {
        switch (reg_num)
        {
            case EAX:
            case EBX:
            case ECX:
            case EDX:
            case EDI:
            case ESI:
            case EBP:
            case ESP:
            case EIP:
            case CS:
            case DS:
            case ES:
            case FS:
            case GS:
            case SS:
                return 32;
            case CF:
            case PF:
            case AF:
            case ZF: 
            case SF:
            case TF:
            case IF:
            case DF:
            case OF:
            case IOPL:
            case VM:
            case NT:
            case RF:
            case AC:
            case VIP:
            case VIF:
            case ID: 
            case C0:
            case C1:
            case C2:
            case C3:
                return 8; // In sleigh/pcode, boolean flags are represented as bytes
            case CR0:
                return 32;
            case TSC:
            case MM0:
            case MM1:
            case MM2:
            case MM3:
            case MM4:
            case MM5:
            case MM6:
            case MM7:
                return 64;
            case ZMM0:
            case ZMM1:
            case ZMM2:
            case ZMM3:
            case ZMM4:
            case ZMM5:
            case ZMM6:
            case ZMM7:
                return 512;
            case XCR0:
                return 64;
            case FPUCW:
            case FPUSW:
            case FPUTW:
                return 16;
            case FPUDP:
            case FPUIP:
                return 32;
            case FPUOP:
                return 11;
            case ST0:
            case ST1:
            case ST2:
            case ST3:
            case ST4:
            case ST5:
            case ST6:
            case ST7:
                return 80;
            default:
                throw runtime_exception("ArchX86::reg_size(): got unsupported reg num");
        }
    }

    reg_t ArchX86::sp() const 
    {
        return X86::ESP;
    }

    reg_t ArchX86::pc() const 
    {
        return X86::EIP;
    }

    reg_t ArchX86::tsc() const 
    {
        return X86::TSC;
    }
} // namespace X86
    
    
std::unordered_map<std::string, reg_t> _x64_reg_map
{
    {"rax", X64::RAX},
    {"rbx", X64::RBX}
};

namespace X64
{
    ArchX64::ArchX64(): Arch(Arch::Type::X64, 64, X64::NB_REGS)
    {
        available_modes = {CPUMode::X64};
        reg_map =
        {
            {"rax", RAX},
            {"rbx", RBX},
            {"rcx", RCX},
            {"rdx", RDX},
            {"rdi", RDI},
            {"rsi", RSI},
            {"rbp", RBP},
            {"rsp", RSP},
            {"rip", RIP},
            {"r8", R8},
            {"r9", R9},
            {"r10", R10},
            {"r11", R11},
            {"r12", R12},
            {"r13", R13},
            {"r14", R14},
            {"r15", R15},
            {"cs", CS},
            {"ds", DS},
            {"es", ES},
            {"fs", FS},
            {"gs", GS},
            {"ss", SS},
            {"cf", CF},
            {"pf", PF},
            {"af", AF},
            {"zf", ZF},
            {"sf", SF},
            {"tf", TF},
            {"if", IF},
            {"df", DF},
            {"of", OF},
            {"iopl", IOPL},
            {"vm", VM},
            {"nt", NT},
            {"rf", RF},
            {"ac", AC},
            {"vip", VIP},
            {"vif", VIF},
            {"id", ID},
            {"tsc", TSC},
            {"mm0", MM0},
            {"mm1", MM1},
            {"mm2", MM2},
            {"mm3", MM3},
            {"mm4", MM4},
            {"mm5", MM5},
            {"mm6", MM6},
            {"mm7", MM7},
            {"zmm0", ZMM0},
            {"zmm1", ZMM1},
            {"zmm2", ZMM2},
            {"zmm3", ZMM3},
            {"zmm4", ZMM4},
            {"zmm5", ZMM5},
            {"zmm6", ZMM6},
            {"zmm7", ZMM7},
            {"xcr0", XCR0},
            {"fpucw", FPUCW},
            {"fpusw", FPUSW},
            {"fputw", FPUTW},
            {"fpuip", FPUIP},
            {"fpudp", FPUDP},
            {"fpuop", FPUOP},
            {"c0", C0},
            {"c1", C1},
            {"c2", C2},
            {"c3", C3},
            {"cr0", CR0},
            {"st0", ST0},
            {"st1", ST1},
            {"st2", ST2},
            {"st3", ST3},
            {"st4", ST4},
            {"st5", ST5},
            {"st6", ST6},
            {"st7", ST7},
            {"mxcsr", MXCSR}
        };
    }

    size_t ArchX64::reg_size(reg_t reg_num) const 
    {
        switch (reg_num)
        {
            case RAX:
            case RBX:
            case RCX:
            case RDX:
            case RDI:
            case RSI:
            case RBP:
            case RSP:
            case SSP:
            case RIP:
            case R8:
            case R9:
            case R10:
            case R11:
            case R12:
            case R13:
            case R14:
            case R15:
            case CS:
            case DS:
            case ES:
            case FS:
            case GS:
            case SS:
                return 64;
            case CF:
            case PF:
            case AF:
            case ZF: 
            case SF:
            case TF:
            case IF:
            case DF:
            case OF:
            case IOPL:
            case VM:
            case NT:
            case RF:
            case AC:
            case VIP:
            case VIF:
            case ID: 
            case C0:
            case C1:
            case C2:
            case C3:
                return 8; // In sleigh/pcode, boolean flags are represented as bytes
            case CR0:
                return 64;
            case TSC:
            case MM0:
            case MM1:
            case MM2:
            case MM3:
            case MM4:
            case MM5:
            case MM6:
            case MM7:
                return 64;
            case ZMM0:
            case ZMM1:
            case ZMM2:
            case ZMM3:
            case ZMM4:
            case ZMM5:
            case ZMM6:
            case ZMM7:
                return 512;
            case XCR0:
                return 64;
            case FPUCW:
            case FPUSW:
            case FPUTW:
                return 16;
            case FPUDP:
            case FPUIP:
                return 64;
            case FPUOP:
                return 11;
            case MXCSR:
                return 32;
            case ST0:
            case ST1:
            case ST2:
            case ST3:
            case ST4:
            case ST5:
            case ST6:
            case ST7:
                return 80;
            default:
                throw runtime_exception("ArchX64::reg_size(): got unsupported reg num");
        }
    }

    reg_t ArchX64::sp() const 
    {
        return X64::RSP;
    }

    reg_t ArchX64::pc() const 
    {
        return X64::RIP;
    }

    reg_t ArchX64::tsc() const 
    {
        return X64::TSC;
    }
} // namespace X64
    
} // namespace maat

