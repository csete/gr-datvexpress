/* -*- c++ -*- */

#define DATVEXPRESS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "datvexpress_swig_doc.i"

%{
#include "datvexpress/sink_c.h"
%}


%include "datvexpress/sink_c.h"
GR_SWIG_BLOCK_MAGIC2(datvexpress, sink_c);
