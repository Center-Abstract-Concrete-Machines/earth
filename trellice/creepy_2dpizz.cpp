#include "creepy_2dpizz.h"

namespace creepy_2dpizz {

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
	Change __m_change_19;
	Delay m_delay_3;
	Delay m_delay_4;
	int __exception;
	int vectorsize;
	t_sample m_gate_17;
	t_sample m_cv7_dampen_14;
	t_sample m_history_13;
	t_sample m_cv5_port_18;
	t_sample m_cv1_pitch_15;
	t_sample m_history_12;
	t_sample m_cv6_decay_16;
	t_sample m_history_11;
	t_sample m_history_9;
	t_sample __m_slide_20;
	t_sample m_x_2;
	t_sample m_y_1;
	t_sample samplerate;
	t_sample m_history_10;
	t_sample m_history_5;
	t_sample m_history_7;
	t_sample m_history_6;
	t_sample m_history_8;
	t_sample __m_slide_23;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = ((int)0);
		m_x_2 = ((int)0);
		m_delay_3.reset("m_delay_3", ((int)44100));
		m_delay_4.reset("m_delay_4", ((int)44100));
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_cv7_dampen_14 = ((t_sample)0.25);
		m_cv1_pitch_15 = ((int)0);
		m_cv6_decay_16 = ((t_sample)0.97);
		m_gate_17 = ((int)0);
		m_cv5_port_18 = ((int)0);
		__m_change_19.reset(0);
		__m_slide_20 = 0;
		__m_slide_23 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int int_20 = int(m_gate_17);
		t_sample add_5 = (m_cv1_pitch_15 + ((int)0));
		t_sample add_1 = (add_5 + ((t_sample)0.25));
		t_sample fastpow_3 = fasterpow(((int)2), add_1);
		t_sample mul_4 = (fastpow_3 * ((t_sample)27.5));
		t_sample gen_6 = mul_4;
		t_sample rdiv_223 = safediv(samplerate, gen_6);
		t_sample rdiv_224 = safediv(samplerate, gen_6);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			int change_21 = __m_change_19(int_20);
			int eqp_22 = ((int_20 == change_21) ? int_20 : 0);
			t_sample mix_2199 = (m_history_13 + (((t_sample)0.0042742627044161) * (m_cv5_port_18 - m_history_13)));
			t_sample mix_11 = mix_2199;
			t_sample mix_2200 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_11 - m_history_12)));
			t_sample mix_9 = mix_2200;
			t_sample mix_2201 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_9 - m_history_11)));
			t_sample mix_7 = mix_2201;
			t_sample gen_19 = mix_7;
			t_sample history_12_next_14 = fixdenorm(mix_11);
			t_sample history_10_next_15 = fixdenorm(mix_9);
			t_sample history_8_next_16 = fixdenorm(mix_7);
			t_sample mix_2202 = (m_history_10 + (((t_sample)0.0042742627044161) * (m_cv6_decay_16 - m_history_10)));
			t_sample mix_2158 = mix_2202;
			t_sample mix_2203 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_2158 - m_history_9)));
			t_sample mix_2160 = mix_2203;
			t_sample mix_2204 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_2160 - m_history_8)));
			t_sample mix_2166 = mix_2204;
			t_sample gen_18 = mix_2166;
			t_sample history_12_next_2159 = fixdenorm(mix_2158);
			t_sample history_10_next_2165 = fixdenorm(mix_2160);
			t_sample history_8_next_2163 = fixdenorm(mix_2166);
			t_sample mix_2205 = (m_history_7 + (((t_sample)0.0042742627044161) * (m_cv7_dampen_14 - m_history_7)));
			t_sample mix_2171 = mix_2205;
			t_sample mix_2206 = (m_history_6 + (((t_sample)0.0042742627044161) * (mix_2171 - m_history_6)));
			t_sample mix_2173 = mix_2206;
			t_sample mix_2207 = (m_history_5 + (((t_sample)0.0042742627044161) * (mix_2173 - m_history_5)));
			t_sample mix_2178 = mix_2207;
			t_sample gen_17 = mix_2178;
			t_sample history_12_next_2172 = fixdenorm(mix_2171);
			t_sample history_10_next_2176 = fixdenorm(mix_2173);
			t_sample history_8_next_2175 = fixdenorm(mix_2178);
			t_sample clamp_232 = ((gen_17 <= ((int)0)) ? ((int)0) : ((gen_17 >= ((int)1)) ? ((int)1) : gen_17));
			t_sample clamp_218 = ((gen_18 <= ((int)0)) ? ((int)0) : ((gen_18 >= ((int)1)) ? ((int)1) : gen_18));
			t_sample clamp_220 = ((gen_19 <= ((int)0)) ? ((int)0) : ((gen_19 >= ((int)2)) ? ((int)2) : gen_19));
			t_sample mul_219 = (clamp_220 * samplerate);
			t_sample iup_21 = (1 / maximum(1, abs(mul_219)));
			t_sample idown_22 = (1 / maximum(1, abs(mul_219)));
			__m_slide_20 = fixdenorm((__m_slide_20 + (((rdiv_223 > __m_slide_20) ? iup_21 : idown_22) * (rdiv_223 - __m_slide_20))));
			t_sample slide_221 = __m_slide_20;
			t_sample sub_225 = (slide_221 - ((int)1));
			t_sample tap_242 = m_delay_4.read_linear(sub_225);
			t_sample iup_24 = (1 / maximum(1, abs(mul_219)));
			t_sample idown_25 = (1 / maximum(1, abs(mul_219)));
			__m_slide_23 = fixdenorm((__m_slide_23 + (((rdiv_224 > __m_slide_23) ? iup_24 : idown_25) * (rdiv_224 - __m_slide_23))));
			t_sample slide_222 = __m_slide_23;
			t_sample sub_226 = (slide_222 - ((int)1));
			t_sample tap_239 = m_delay_3.read_linear(sub_226);
			t_sample cartopol_2208 = sqrt(((tap_242 * tap_242) + (tap_239 * tap_239)));
			t_sample cartopol_2209 = atan2(tap_239, tap_242);
			t_sample radius_236 = cartopol_2208;
			t_sample angle_237 = cartopol_2209;
			t_sample add_233 = (angle_237 + ((int)0));
			t_sample mul_235 = (radius_236 * clamp_218);
			t_sample mul_227 = (mul_235 * ((int)2));
			t_sample sin_234 = sin(mul_227);
			t_sample poltocar_2210 = (sin_234 * cos(add_233));
			t_sample poltocar_2211 = (sin_234 * sin(add_233));
			t_sample x_230 = poltocar_2210;
			t_sample y_231 = poltocar_2211;
			t_sample mix_2212 = (x_230 + (clamp_232 * (m_x_2 - x_230)));
			t_sample mix_240 = mix_2212;
			t_sample gen_245 = mix_240;
			t_sample mix_2213 = (y_231 + (clamp_232 * (m_y_1 - y_231)));
			t_sample mix_228 = mix_2213;
			t_sample gen_246 = mix_228;
			t_sample x_next_243 = fixdenorm(mix_240);
			t_sample y_next_244 = fixdenorm(mix_228);
			t_sample out1 = gen_245;
			t_sample out2 = gen_246;
			m_history_13 = history_12_next_14;
			m_history_11 = history_8_next_16;
			m_history_12 = history_10_next_15;
			m_history_10 = history_12_next_2159;
			m_history_8 = history_8_next_2163;
			m_history_9 = history_10_next_2165;
			m_history_7 = history_12_next_2172;
			m_history_5 = history_8_next_2175;
			m_history_6 = history_10_next_2176;
			m_delay_4.write((m_x_2 + eqp_22));
			m_y_1 = y_next_244;
			m_x_2 = x_next_243;
			m_delay_3.write((eqp_22 + m_y_1));
			m_delay_3.step();
			m_delay_4.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_cv7_dampen(t_param _value) {
		m_cv7_dampen_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv1_pitch(t_param _value) {
		m_cv1_pitch_15 = (_value < 0 ? 0 : (_value > 5 ? 5 : _value));
	};
	inline void set_cv6_decay(t_param _value) {
		m_cv6_decay_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_gate1(t_param _value) {
		m_gate_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv5_port(t_param _value) {
		m_cv5_port_18 = (_value < 0 ? 0 : (_value > 2 ? 2 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 5; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
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
		case 0: self->set_cv1_pitch(value); break;
		case 1: self->set_cv5_port(value); break;
		case 2: self->set_cv6_decay(value); break;
		case 3: self->set_cv7_dampen(value); break;
		case 4: self->set_gate1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_cv1_pitch_15; break;
		case 1: *value = self->m_cv5_port_18; break;
		case 2: *value = self->m_cv6_decay_16; break;
		case 3: *value = self->m_cv7_dampen_14; break;
		case 4: *value = self->m_gate_17; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(5 * sizeof(ParamInfo));
	self->__commonstate.numparams = 5;
	// initialize parameter 0 ("m_cv1_pitch_15")
	pi = self->__commonstate.params + 0;
	pi->name = "cv1_pitch";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv1_pitch_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_cv5_port_18")
	pi = self->__commonstate.params + 1;
	pi->name = "cv5_port";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv5_port_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_cv6_decay_16")
	pi = self->__commonstate.params + 2;
	pi->name = "cv6_decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv6_decay_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_cv7_dampen_14")
	pi = self->__commonstate.params + 3;
	pi->name = "cv7_dampen";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv7_dampen_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_gate_17")
	pi = self->__commonstate.params + 4;
	pi->name = "gate1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_17;
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


} // creepy_2dpizz::
