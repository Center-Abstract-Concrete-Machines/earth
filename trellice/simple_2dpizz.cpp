#include "simple_2dpizz.h"

namespace simple_2dpizz {

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
	Change __m_change_35;
	Delay m_delay_10;
	Delay m_delay_7;
	Delay m_delay_16;
	int __exception;
	int vectorsize;
	t_sample m_cv7_dampen_26;
	t_sample m_history_21;
	t_sample m_cv6_decay_25;
	t_sample m_cv1_pitch_23;
	t_sample m_gate_24;
	t_sample m_history_22;
	t_sample m_history_28;
	t_sample m_history_20;
	t_sample __m_latch_36;
	t_sample __m_slide_37;
	t_sample m_cv5_portamento_27;
	t_sample __m_slide_32;
	t_sample m_history_30;
	t_sample __m_latch_31;
	t_sample m_history_29;
	t_sample m_history_19;
	t_sample m_history_17;
	t_sample __m_latch_40;
	t_sample m_portamento_3;
	t_sample m_decay_4;
	t_sample m_avg_5;
	t_sample m_dampen_2;
	t_sample samplerate;
	t_sample m_pitch_1;
	t_sample m_history_18;
	t_sample m_history_6;
	t_sample m_history_9;
	t_sample m_avg_14;
	t_sample m_history_15;
	t_sample m_avg_8;
	t_sample m_history_13;
	t_sample m_history_11;
	t_sample m_history_12;
	t_sample __m_slide_41;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_pitch_1 = ((int)0);
		m_dampen_2 = ((int)0);
		m_portamento_3 = ((int)0);
		m_decay_4 = ((int)0);
		m_avg_5 = ((int)0);
		m_history_6 = ((int)0);
		m_delay_7.reset("m_delay_7", samplerate);
		m_avg_8 = ((int)0);
		m_history_9 = ((int)0);
		m_delay_10.reset("m_delay_10", samplerate);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_avg_14 = ((int)0);
		m_history_15 = ((int)0);
		m_delay_16.reset("m_delay_16", samplerate);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_history_20 = ((int)0);
		m_history_21 = ((int)0);
		m_history_22 = ((int)0);
		m_cv1_pitch_23 = ((int)0);
		m_gate_24 = ((int)0);
		m_cv6_decay_25 = 0.97;
		m_cv7_dampen_26 = ((t_sample)0.25);
		m_cv5_portamento_27 = ((int)0);
		m_history_28 = ((int)0);
		m_history_29 = ((int)0);
		m_history_30 = ((int)0);
		__m_latch_31 = 1;
		__m_slide_32 = 0;
		__m_change_35.reset(0);
		__m_latch_36 = 1;
		__m_slide_37 = 0;
		__m_latch_40 = 1;
		__m_slide_41 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample add_71 = (m_cv1_pitch_23 + ((int)0));
		t_sample add_67 = (add_71 + ((t_sample)0.25));
		t_sample fastpow_69 = fasterpow(((int)2), add_67);
		t_sample mul_70 = (fastpow_69 * ((t_sample)27.5));
		t_sample gen_73 = mul_70;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample mix_324 = (m_history_30 + (((t_sample)0.0042742627044161) * (m_cv6_decay_25 - m_history_30)));
			t_sample mix_56 = mix_324;
			t_sample mix_325 = (m_history_29 + (((t_sample)0.0042742627044161) * (mix_56 - m_history_29)));
			t_sample mix_54 = mix_325;
			t_sample mix_326 = (m_history_28 + (((t_sample)0.0042742627044161) * (mix_54 - m_history_28)));
			t_sample mix_52 = mix_326;
			t_sample gen_76 = mix_52;
			t_sample history_57_next_63 = fixdenorm(mix_56);
			t_sample history_55_next_64 = fixdenorm(mix_54);
			t_sample history_53_next_65 = fixdenorm(mix_52);
			t_sample mix_327 = (m_history_22 + (((t_sample)0.0042742627044161) * (m_cv5_portamento_27 - m_history_22)));
			t_sample mix_196 = mix_327;
			t_sample mix_328 = (m_history_21 + (((t_sample)0.0042742627044161) * (mix_196 - m_history_21)));
			t_sample mix_198 = mix_328;
			t_sample mix_329 = (m_history_20 + (((t_sample)0.0042742627044161) * (mix_198 - m_history_20)));
			t_sample mix_199 = mix_329;
			t_sample gen_78 = mix_199;
			t_sample history_57_next_200 = fixdenorm(mix_196);
			t_sample history_55_next_193 = fixdenorm(mix_198);
			t_sample history_53_next_195 = fixdenorm(mix_199);
			t_sample mix_330 = (m_history_19 + (((t_sample)0.0042742627044161) * (m_cv7_dampen_26 - m_history_19)));
			t_sample mix_210 = mix_330;
			t_sample mix_331 = (m_history_18 + (((t_sample)0.0042742627044161) * (mix_210 - m_history_18)));
			t_sample mix_206 = mix_331;
			t_sample mix_332 = (m_history_17 + (((t_sample)0.0042742627044161) * (mix_206 - m_history_17)));
			t_sample mix_213 = mix_332;
			t_sample gen_74 = mix_213;
			t_sample history_57_next_207 = fixdenorm(mix_210);
			t_sample history_55_next_208 = fixdenorm(mix_206);
			t_sample history_53_next_214 = fixdenorm(mix_213);
			t_sample expr_37 = m_dampen_2;
			t_sample expr_34 = m_pitch_1;
			t_sample expr_36 = m_portamento_3;
			t_sample expr_35 = m_decay_4;
			int gt_22 = (m_avg_14 > ((int)0));
			int gen_86 = gt_22;
			int not_18 = (!m_history_15);
			int mul_21 = (((int)0) * not_18);
			t_sample mul_25 = (expr_36 * samplerate);
			__m_latch_31 = ((mul_21 != 0) ? expr_34 : __m_latch_31);
			t_sample latch_17 = __m_latch_31;
			t_sample rdiv_28 = safediv(samplerate, latch_17);
			t_sample iup_33 = (1 / maximum(1, abs(mul_25)));
			t_sample idown_34 = (1 / maximum(1, abs(mul_25)));
			__m_slide_32 = fixdenorm((__m_slide_32 + (((rdiv_28 > __m_slide_32) ? iup_33 : idown_34) * (rdiv_28 - __m_slide_32))));
			t_sample slide_27 = __m_slide_32;
			t_sample sub_29 = (slide_27 - ((int)1));
			t_sample tap_33 = m_delay_16.read_linear(sub_29);
			t_sample mul_14 = (expr_35 * latch_17);
			t_sample t_13 = exp(safediv(-6.9077552789821, mul_14));
			t_sample mul_15 = (tap_33 * t_13);
			t_sample mix_333 = (mul_15 + (expr_37 * (m_avg_14 - mul_15)));
			t_sample mix_31 = mix_333;
			t_sample history_20_next_38 = fixdenorm(gt_22);
			t_sample avg_next_39 = fixdenorm(mix_31);
			t_sample mix_334 = (m_history_13 + (((t_sample)0.0042742627044161) * (gen_73 - m_history_13)));
			t_sample mix_221 = mix_334;
			t_sample mix_335 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_221 - m_history_12)));
			t_sample mix_222 = mix_335;
			t_sample mix_336 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_222 - m_history_11)));
			t_sample mix_226 = mix_336;
			t_sample gen_79 = mix_226;
			t_sample history_57_next_218 = fixdenorm(mix_221);
			t_sample history_55_next_219 = fixdenorm(mix_222);
			t_sample history_53_next_224 = fixdenorm(mix_226);
			int int_80 = int(in1);
			int change_81 = __m_change_35(int_80);
			int eqp_82 = ((int_80 == change_81) ? int_80 : 0);
			int gen_84 = eqp_82;
			t_sample expr_241 = m_dampen_2;
			t_sample expr_238 = m_pitch_1;
			t_sample gen_94 = m_avg_8;
			t_sample expr_248 = m_portamento_3;
			t_sample expr_236 = m_decay_4;
			int gt_231 = (m_avg_8 > ((int)0));
			t_sample mul_232 = (gen_84 * m_history_9);
			t_sample gen_90 = mul_232;
			int not_235 = (!m_history_9);
			int mul_245 = (gen_84 * not_235);
			t_sample mul_247 = (expr_248 * samplerate);
			__m_latch_36 = ((mul_245 != 0) ? expr_238 : __m_latch_36);
			t_sample latch_251 = __m_latch_36;
			t_sample rdiv_252 = safediv(samplerate, latch_251);
			t_sample iup_38 = (1 / maximum(1, abs(mul_247)));
			t_sample idown_39 = (1 / maximum(1, abs(mul_247)));
			__m_slide_37 = fixdenorm((__m_slide_37 + (((rdiv_252 > __m_slide_37) ? iup_38 : idown_39) * (rdiv_252 - __m_slide_37))));
			t_sample slide_233 = __m_slide_37;
			t_sample sub_243 = (slide_233 - ((int)1));
			t_sample tap_242 = m_delay_10.read_linear(sub_243);
			t_sample gen_92 = tap_242;
			t_sample mul_240 = (expr_236 * latch_251);
			t_sample t_254 = exp(safediv(-6.9077552789821, mul_240));
			t_sample mul_249 = (tap_242 * t_254);
			t_sample mix_337 = (mul_249 + (expr_241 * (m_avg_8 - mul_249)));
			t_sample mix_239 = mix_337;
			t_sample history_20_next_237 = fixdenorm(gt_231);
			t_sample avg_next_246 = fixdenorm(mix_239);
			t_sample out4 = gen_94;
			t_sample expr_268 = m_dampen_2;
			t_sample expr_265 = m_pitch_1;
			t_sample expr_277 = m_portamento_3;
			t_sample expr_263 = m_decay_4;
			int gt_258 = (m_avg_5 > ((int)0));
			int gen_46 = gt_258;
			int not_262 = (!m_history_6);
			t_sample mul_272 = (gen_90 * not_262);
			t_sample mul_276 = (expr_277 * samplerate);
			__m_latch_40 = ((mul_272 != 0) ? expr_265 : __m_latch_40);
			t_sample latch_279 = __m_latch_40;
			t_sample rdiv_278 = safediv(samplerate, latch_279);
			t_sample iup_42 = (1 / maximum(1, abs(mul_276)));
			t_sample idown_43 = (1 / maximum(1, abs(mul_276)));
			__m_slide_41 = fixdenorm((__m_slide_41 + (((rdiv_278 > __m_slide_41) ? iup_42 : idown_43) * (rdiv_278 - __m_slide_41))));
			t_sample slide_260 = __m_slide_41;
			t_sample sub_270 = (slide_260 - ((int)1));
			t_sample tap_269 = m_delay_7.read_linear(sub_270);
			t_sample gen_47 = tap_269;
			t_sample mul_266 = (expr_263 * latch_279);
			t_sample t_281 = exp(safediv(-6.9077552789821, mul_266));
			t_sample mul_275 = (tap_269 * t_281);
			t_sample mix_338 = (mul_275 + (expr_268 * (m_avg_5 - mul_275)));
			t_sample mix_274 = mix_338;
			t_sample history_20_next_264 = fixdenorm(gt_258);
			t_sample avg_next_273 = fixdenorm(mix_274);
			t_sample out3 = (gen_86 + gen_46);
			t_sample out2 = ((int)0);
			t_sample mul_50 = ((gen_92 + gen_47) * ((t_sample)0.25));
			t_sample out1 = mul_50;
			t_sample decay_next_285 = fixdenorm(gen_76);
			t_sample portamento_next_286 = fixdenorm(gen_78);
			t_sample dampen_next_287 = fixdenorm(gen_74);
			t_sample pitch_next_288 = fixdenorm(gen_79);
			m_history_30 = history_57_next_63;
			m_history_28 = history_53_next_65;
			m_history_29 = history_55_next_64;
			m_history_22 = history_57_next_200;
			m_history_20 = history_53_next_195;
			m_history_21 = history_55_next_193;
			m_history_19 = history_57_next_207;
			m_history_17 = history_53_next_214;
			m_history_18 = history_55_next_208;
			m_delay_16.write((((m_avg_14 + mul_21) + ((int)0)) + ((int)0)));
			m_avg_14 = avg_next_39;
			m_history_15 = history_20_next_38;
			m_history_13 = history_57_next_218;
			m_history_11 = history_53_next_224;
			m_history_12 = history_55_next_219;
			m_delay_10.write((((m_avg_8 + mul_245) + gen_84) + ((int)0)));
			m_avg_8 = avg_next_246;
			m_history_9 = history_20_next_237;
			m_delay_7.write((((m_avg_5 + mul_272) + gen_90) + ((int)0)));
			m_avg_5 = avg_next_273;
			m_history_6 = history_20_next_264;
			m_decay_4 = decay_next_285;
			m_portamento_3 = portamento_next_286;
			m_dampen_2 = dampen_next_287;
			m_pitch_1 = pitch_next_288;
			m_delay_7.step();
			m_delay_10.step();
			m_delay_16.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			
		};
		return __exception;
		
	};
	inline void set_cv1_pitch(t_param _value) {
		m_cv1_pitch_23 = (_value < 0 ? 0 : (_value > 5 ? 5 : _value));
	};
	inline void set_gate1(t_param _value) {
		m_gate_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv6_decay(t_param _value) {
		m_cv6_decay_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv7_dampen(t_param _value) {
		m_cv7_dampen_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv5_portamento(t_param _value) {
		m_cv5_portamento_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 4;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 5; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4" };

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
		case 1: self->set_cv5_portamento(value); break;
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
		case 0: *value = self->m_cv1_pitch_23; break;
		case 1: *value = self->m_cv5_portamento_27; break;
		case 2: *value = self->m_cv6_decay_25; break;
		case 3: *value = self->m_cv7_dampen_26; break;
		case 4: *value = self->m_gate_24; break;
		
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
	// initialize parameter 0 ("m_cv1_pitch_23")
	pi = self->__commonstate.params + 0;
	pi->name = "cv1_pitch";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv1_pitch_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_cv5_portamento_27")
	pi = self->__commonstate.params + 1;
	pi->name = "cv5_portamento";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv5_portamento_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_cv6_decay_25")
	pi = self->__commonstate.params + 2;
	pi->name = "cv6_decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv6_decay_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_cv7_dampen_26")
	pi = self->__commonstate.params + 3;
	pi->name = "cv7_dampen";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv7_dampen_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_gate_24")
	pi = self->__commonstate.params + 4;
	pi->name = "gate1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_24;
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


} // simple_2dpizz::
