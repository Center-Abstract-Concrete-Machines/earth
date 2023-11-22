#include "creepy_2dpizz_5b1_5d_5b1_5d.h"

namespace creepy_2dpizz_5b1_5d_5b1_5d {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_3;
	Delay m_delay_4;
	int __exception;
	int vectorsize;
	t_sample m_y_1;
	t_sample m_dampen_6;
	t_sample m_rotate_7;
	t_sample samplerate;
	t_sample m_decay_5;
	t_sample m_x_2;
	t_sample __m_slide_8;
	t_sample __m_slide_11;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = ((int)0);
		m_x_2 = ((int)0);
		m_delay_3.reset("m_delay_3", ((int)44100));
		m_delay_4.reset("m_delay_4", ((int)44100));
		m_decay_5 = ((t_sample)0.97);
		m_dampen_6 = ((t_sample)0.25);
		m_rotate_7 = ((int)0);
		__m_slide_8 = 0;
		__m_slide_11 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		const t_sample * __in3 = __ins[2];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__in3 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample mul_15 = (m_rotate_7 * ((t_sample)3.1415926535898));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			const t_sample in3 = (*(__in3++));
			t_sample rdiv_9 = safediv(samplerate, in2);
			t_sample rdiv_10 = safediv(samplerate, in2);
			t_sample clamp_610 = ((in3 <= ((int)0)) ? ((int)0) : ((in3 >= ((int)2)) ? ((int)2) : in3));
			t_sample mul_414 = (clamp_610 * samplerate);
			t_sample iup_9 = (1 / maximum(1, abs(mul_414)));
			t_sample idown_10 = (1 / maximum(1, abs(mul_414)));
			__m_slide_8 = fixdenorm((__m_slide_8 + (((rdiv_9 > __m_slide_8) ? iup_9 : idown_10) * (rdiv_9 - __m_slide_8))));
			t_sample slide_294 = __m_slide_8;
			t_sample sub_11 = (slide_294 - ((int)1));
			t_sample tap_27 = m_delay_4.read_linear(sub_11);
			t_sample iup_12 = (1 / maximum(1, abs(mul_414)));
			t_sample idown_13 = (1 / maximum(1, abs(mul_414)));
			__m_slide_11 = fixdenorm((__m_slide_11 + (((rdiv_10 > __m_slide_11) ? iup_12 : idown_13) * (rdiv_10 - __m_slide_11))));
			t_sample slide_271 = __m_slide_11;
			t_sample sub_12 = (slide_271 - ((int)1));
			t_sample tap_24 = m_delay_3.read_linear(sub_12);
			t_sample cartopol_3894 = sqrt(((tap_27 * tap_27) + (tap_24 * tap_24)));
			t_sample cartopol_3895 = atan2(tap_24, tap_27);
			t_sample radius_21 = cartopol_3894;
			t_sample angle_22 = cartopol_3895;
			t_sample add_18 = (angle_22 + mul_15);
			t_sample mul_20 = (radius_21 * m_decay_5);
			t_sample mul_13 = (mul_20 * ((int)2));
			t_sample sin_19 = sin(mul_13);
			t_sample poltocar_3896 = (sin_19 * cos(add_18));
			t_sample poltocar_3897 = (sin_19 * sin(add_18));
			t_sample x_16 = poltocar_3896;
			t_sample y_17 = poltocar_3897;
			t_sample mix_3898 = (x_16 + (m_dampen_6 * (m_x_2 - x_16)));
			t_sample mix_25 = mix_3898;
			t_sample out1 = mix_25;
			t_sample mix_3899 = (y_17 + (m_dampen_6 * (m_y_1 - y_17)));
			t_sample mix_14 = mix_3899;
			t_sample out2 = mix_14;
			t_sample x_next_689 = fixdenorm(mix_25);
			t_sample y_next_690 = fixdenorm(mix_14);
			m_delay_4.write((m_x_2 + in1));
			m_delay_3.write((in1 + m_y_1));
			m_x_2 = x_next_689;
			m_y_1 = y_next_690;
			m_delay_3.step();
			m_delay_4.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_decay(t_param _value) {
		m_decay_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_dampen(t_param _value) {
		m_dampen_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_rotate(t_param _value) {
		m_rotate_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 3;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 3; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2", "portamento" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_dampen(value); break;
		case 1: self->set_decay(value); break;
		case 2: self->set_rotate(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_dampen_6; break;
		case 1: *value = self->m_decay_5; break;
		case 2: *value = self->m_rotate_7; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(3 * sizeof(ParamInfo));
	self->__commonstate.numparams = 3;
	// initialize parameter 0 ("m_dampen_6")
	pi = self->__commonstate.params + 0;
	pi->name = "dampen";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_dampen_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_decay_5")
	pi = self->__commonstate.params + 1;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_rotate_7")
	pi = self->__commonstate.params + 2;
	pi->name = "rotate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_rotate_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // creepy_2dpizz_5b1_5d_5b1_5d::
