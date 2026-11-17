// Hooks for default.xbe. A strong definition replaces the recompiled function at that address.
#include "xdk/hle.h"

using namespace kernel;

// XDK 3911 shows a frame with D3DDevice_Present(source, dest, window, dirty region), which later XDKs replaced with
// D3DDevice_Swap(flags); the runtime's Swap does it. Present's four arguments become Swap's one (0).
X86_EXTERN_FUNC(GUEST(D3DDevice_Swap));
X86_FUNC(sub_0036AFA0) {
    uint32_t ret = R32(ctx.esp);
    ctx.esp += 12;
    W32(ctx.esp, ret);
    W32(ctx.esp + 4, 0);
    GUEST(D3DDevice_Swap)(ctx, base);
}

// DirectSound 3D cone and mode calls the runtime has no part for: their library code reads the voice of a stream or
// buffer the runtime made (it has none), so they succeed doing nothing. Address, stack bytes popped.
#define OBI_STUB(addr, pops)          \
    X86_FUNC(sub_##addr) {            \
        (void)base;                   \
        ctx.eax = 0;                  \
        ctx.esp += 4 + (pops);        \
    }
OBI_STUB(003AAE4E, 0xC)   // IDirectSoundBuffer_* (this, value, apply) via 0x3AA? -0x1C thunk
OBI_STUB(003AAE6E, 0x10)  // IDirectSoundBuffer_SetConeAngles
OBI_STUB(003AAE92, 0x14)  // IDirectSoundBuffer_SetConeOrientation
OBI_STUB(003AAB85, 0xC)   // CDirectSoundStream (this, value, apply), reached from IDirectSoundStream 0x3AB069
OBI_STUB(003AAB9D, 0x10)  // CDirectSoundStream_SetConeAngles
OBI_STUB(003AABE6, 0xC)   // CDirectSoundStream_SetConeOutsideVolume or SetMode: stores a value at the voice's +0x4C
OBI_STUB(003AB073, 0x14)  // IDirectSoundStream_SetConeOrientation
// The IDirectSoundStream entries the game calls jump into the CDirectSoundStream ones above; the jump skips their
// overrides, so the entries are stubbed too.
OBI_STUB(003AB069, 0xC)   // IDirectSoundStream_SetMixBinVolumes (3911: this, bin mask, LONG volumes[]) -> 0x3AAB85; TODO volumes
OBI_STUB(003AB06E, 0x10)  // IDirectSoundStream_SetConeAngles -> 0x3AAB9D
OBI_STUB(003AB09C, 0xC)   // -> 0x3AABE6

// A safety net: D3D_RecordStateBlock 0x36763C adds a reference to everything bound, and a junk resource there (once
// 0xFFAAAAAA, from render states written with the wrong numbering) crashed. The AddRef it uses (0x36CE20, stdcall
// resource) skips addresses no resource can have: the 0xF0000000 and up range is the hardware's registers.
X86_EXTERN_FUNC(__imp__sub_0036CE20);
X86_FUNC(sub_0036CE20) {
    uint32_t res = R32(ctx.esp + 4);
    if (res >= 0xF0000000u || res < 0x10000u) {
        LOG_FIRST(8, "obi: AddRef of junk resource %08X from %08X skipped", res, R32(ctx.esp));
        ctx.eax = 0;
        ctx.esp += 8;
        return;
    }
    __imp__sub_0036CE20(ctx, base);
}
