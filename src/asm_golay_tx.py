#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: GFSK AztechSat-1
# Author: MLG
# GNU Radio version: 3.7.13.4
##################################################

from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import iio
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import pmt


class asm_golay_tx(gr.top_block):

    def __init__(self, file_tx='/home/sun/gs/ground/src/beacon_tx_upaep', freq=435400000):
        gr.top_block.__init__(self, "GFSK AztechSat-1")

        ##################################################
        # Parameters
        ##################################################
        self.file_tx = file_tx
        self.freq = freq

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 1996800

        ##################################################
        # Blocks
        ##################################################
        self.pluto_sink_0 = iio.pluto_sink('192.168.3.1', int(freq), int(samp_rate), int(1000000), 0x8000, False, 1, '', True)
        self.digital_gfsk_mod_0 = digital.gfsk_mod(
        	samples_per_symbol=samp_rate/9600,
        	sensitivity=0.009,
        	bt=0.350,
        	verbose=False,
        	log=False,
        )
        self.blocks_multiply_const_vxx_1 = blocks.multiply_const_vcc((1, ))
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, file_tx, False)
        self.blocks_file_source_0.set_begin_tag(pmt.PMT_NIL)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_file_source_0, 0), (self.digital_gfsk_mod_0, 0))
        self.connect((self.blocks_multiply_const_vxx_1, 0), (self.pluto_sink_0, 0))
        self.connect((self.digital_gfsk_mod_0, 0), (self.blocks_multiply_const_vxx_1, 0))

    def get_file_tx(self):
        return self.file_tx

    def set_file_tx(self, file_tx):
        self.file_tx = file_tx
        self.blocks_file_source_0.open(self.file_tx, False)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self.pluto_sink_0.set_params(int(self.freq), int(self.samp_rate), int(1000000), 1, '', True)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.pluto_sink_0.set_params(int(self.freq), int(self.samp_rate), int(1000000), 1, '', True)


def argument_parser():
    parser = OptionParser(usage="%prog: [options]", option_class=eng_option)
    parser.add_option(
        "", "--file-tx", dest="file_tx", type="string", default='/home/sun/gs/ground/src/beacon_tx_upaep',
        help="Set /home/sun/gs/ground/src/beacon_tx_upaep [default=%default]")
    parser.add_option(
        "", "--freq", dest="freq", type="eng_float", default=eng_notation.num_to_str(435400000),
        help="Set freq [default=%default]")
    return parser


def main(top_block_cls=asm_golay_tx, options=None):
    if options is None:
        options, _ = argument_parser().parse_args()

    tb = top_block_cls(file_tx=options.file_tx, freq=options.freq)
    tb.start()
    tb.wait()


if __name__ == '__main__':
    main()
