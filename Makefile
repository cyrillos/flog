__nmk_dir=scripts/nmk/scripts/
export __nmk_dir

PROGRAM := flog

include $(__nmk_dir)include.mk
include $(__nmk_dir)macro.mk

$(eval $(call gen-built-in,src))

$(PROGRAM): src/built-in.o
	$(call msg-gen, $@)
	$(Q) $(CC) -lffi -o $@ $^

all: src $(PROGRAM)
	@true
.PHONY: all

clean:
	$(call msg-gen, $@)
	$(Q) $(MAKE) $(build)=src clean
	$(Q) $(RM) $(PROGRAM)
.PHONY: clean

.DEFAULT_GOAL := all
