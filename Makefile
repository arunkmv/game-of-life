default: all

ifeq (,$(vcd))
STDERR_VCD =
VERILATOR_TRACE =
else
STDERR_VCD = 2> $$@.vcd
VERILATOR_TRACE = --trace
endif

VERILATOR = verilator $(VERILATOR_TRACE)

VERILATOR_CFLAGS = -std=c++11 -Icsrc/

sims = \
blinker \
pulsar \

define sim_template

sim-$(1)/Sim_$(2).v: src/main/scala/*.scala
	sbt "run $(2) -td sim-$(1)"

sim-$(1)/dut.mk: sim-$(1)/Sim_$(2).v csrc/sim-gol.cpp csrc/$(1).h
	$(VERILATOR) -cc --prefix dut --Mdir sim-$(1) -CFLAGS "$(VERILATOR_CFLAGS) -include ../csrc/$(1).h" sim-$(1)/Sim_$(2).v --exe csrc/sim-gol.cpp

sim-$(1)/dut: sim-$(1)/dut.mk
	cd sim-$(1) && make -f dut.mk dut

sim-$(1): sim-$(1)/dut
	./$$<

.PHONY: sim-$(1)

endef

$(eval $(call sim_template,blinker,3x3))
$(eval $(call sim_template,pulsar,15x15))

all: $(addprefix sim-, $(sims))

clean:
	rm -rf sim-*

.PHONY: all clean