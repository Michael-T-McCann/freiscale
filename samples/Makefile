.PHONY : all

DIR=../dist/waves

SAMPLES= \
	square.wav \
	saw.wav \
	triangle.wav \
	dual-sine.wav \


all : \
	$(addprefix $(DIR)/,$(SAMPLES)) \

temp.waves-norm.wav : waves.wav
	#sox $< -c 1 $@ norm
	cp $< $@

$(DIR)/square.wav : temp.waves-norm.wav
	sox $< -c 1 $@ trim 0 1.9 reverse silence 1 1 '0.1%' reverse

$(DIR)/saw.wav : temp.waves-norm.wav
	sox $< -c 1 $@ trim 2 1.9 reverse silence 1 1 '0.1%' reverse

$(DIR)/triangle.wav : temp.waves-norm.wav
	sox $< -c 1 $@ trim 4 1.9 reverse silence 1 1 '0.1%' reverse

$(DIR)/dual-sine.wav : temp.waves-norm.wav
	sox $< -c 1 $@ trim 6 1.9 reverse silence 1 1 '0.1%' reverse
