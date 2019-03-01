#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Transmitter
# Generated: Wed Feb 27 16:06:31 2019
##################################################


from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import iio
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser


class transmitter(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Transmitter")

        ##################################################
        # Blocks
        ##################################################
        self.pluto_source_0 = iio.pluto_source('192.168.3.1', int(435400000), int(1996800), int(20000000), 0x8000, True, True, True, "manual", 64.0, '', True)
        self.pluto_sink_0 = iio.pluto_sink('192.168.3.1', int(435400000), int(1996800), int(20000000), 0x8000, False, 0, '', True)
        self.digital_gfsk_mod_0 = digital.gfsk_mod(
        	samples_per_symbol=208,
        	sensitivity=0.0105,
        	bt=0.5,
        	verbose=False,
        	log=False,
        )
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vcc((0, ))
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, '/home/miguel/gnuradio/intento_22.02.19/send_data.txt', True)
        self.blocks_add_xx_1 = blocks.add_vcc(1)
        self.blks2_packet_encoder_0 = grc_blks2.packet_mod_b(grc_blks2.packet_encoder(
        		samples_per_symbol=208,
        		bits_per_symbol=1,
        		preamble='{:b}'.format(0x930b51de),
        		access_code='0111110',
        		pad_for_usrp=False,
        	),
        	payload_length=5,
        )

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blks2_packet_encoder_0, 0), (self.digital_gfsk_mod_0, 0))
        self.connect((self.blocks_add_xx_1, 0), (self.pluto_sink_0, 0))
        self.connect((self.blocks_file_source_0, 0), (self.blks2_packet_encoder_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.blocks_add_xx_1, 0))
        self.connect((self.digital_gfsk_mod_0, 0), (self.blocks_add_xx_1, 1))
        self.connect((self.pluto_source_0, 0), (self.blocks_multiply_const_vxx_0, 0))


def main(top_block_cls=transmitter, options=None):

    tb = top_block_cls()
    tb.start()
    tb.wait()


if __name__ == '__main__':
    main()
