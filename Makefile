ARDUINO      ?= arduino-cli
ARDUINOFLAGS ?= --verify

SSD_FQBN ?= arduino:avr:uno
SSD_SRC  ?= seven-seg-driver


.PHONY: all
all:
	$(ARDUINO) compile $(ARDUINOFLAGS) --fqbn $(SSD_FQBN) $(SSD_SRC)

.PHONY: flash
flash:
	$(ARDUINO) upload $(ARDUINOFLAGS) --fqbn $(SSD_FQBN) --port $(PORT) $(SSD_SRC)
