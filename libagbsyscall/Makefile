PREFIX := arm-none-eabi-
AS := $(PREFIX)as
AR := $(PREFIX)ar

ASFLAGS := -mcpu=arm7tdmi
ARFLAGS := rc

SYSCALLS := IntrWait \
            RegisterRamReset \
            Sqrt \
            MusicPlayerOpen \
            SoundBiasReset \
            SoundDriverVSyncOn \
            Mod \
            VBlankIntrWait \
            MusicPlayerStart \
            SoundDriverVSyncOff \
            HuffUnComp \
            SoftResetExram \
            MusicPlayerFadeOut \
            LZ77UnCompWram \
            SoundDriverMain \
            SoundBiasChange \
            LZ77UnCompVram \
            ArcTan2 \
            MusicPlayerStop \
            DivArm \
            ModArm \
            SoundDriverVSync \
            SoundDriverInit \
            BgAffineSet \
            Diff8bitUnFilterWram \
            MultiBoot \
            MidiKey2Freq \
            Div \
            Diff8bitUnFilterVram \
            ArcTan \
            ObjAffineSet \
            SoftResetRom \
            SoundDriverMode \
            RLUnCompWram \
            BitUnPack \
            SoundChannelClear \
            CpuFastSet \
            CpuSet \
            Diff16bitUnFilter \
            SoundBiasSet \
            MusicPlayerContinue \
            SoftReset \
            RLUnCompVram

ASM_SRCS := libagbsyscall.s
ASM_OBJS := $(foreach syscall, $(SYSCALLS), $(syscall).o)

LIB := libagbsyscall.a

.PHONY: all clean

all: $(LIB)
	@:

clean:
	rm -f $(LIB) $(ASM_OBJS)

$(LIB): $(ASM_OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(ASM_OBJS): libagbsyscall.s
	$(AS) $(ASFLAGS) --defsym L_$(*F)=1 -o $@ $<
