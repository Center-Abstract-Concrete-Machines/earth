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
	t_sample m_cv1_pitch_25;
	t_sample m_gate_23;
	t_sample m_cv5_portamento_24;
	t_sample m_history_22;
	t_sample m_history_28;
	t_sample m_history_20;
	t_sample __m_latch_36;
	t_sample __m_slide_37;
	t_sample m_cv6_decay_27;
	t_sample __m_slide_32;
	t_sample m_history_30;
	t_sample __m_latch_31;
	t_sample m_history_29;
	t_sample m_history_19;
	t_sample m_history_17;
	t_sample __m_latch_40;
	t_sample m_dampen_3;
	t_sample m_decay_4;
	t_sample m_avg_5;
	t_sample m_portamento_2;
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
		m_portamento_2 = ((int)0);
		m_dampen_3 = ((int)0);
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
		m_gate_23 = ((int)0);
		m_cv5_portamento_24 = ((int)0);
		m_cv1_pitch_25 = ((int)0);
		m_cv7_dampen_26 = ((t_sample)0.25);
		m_cv6_decay_27 = 0.97;
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
		t_sample add_7209 = (m_cv1_pitch_25 + ((int)0));
		t_sample add_7205 = (add_7209 + ((t_sample)0.25));
		t_sample fastpow_7207 = fasterpow(((int)2), add_7205);
		t_sample mul_7208 = (fastpow_7207 * ((t_sample)27.5));
		t_sample gen_7210 = mul_7208;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample mix_7848 = (m_history_30 + (((t_sample)0.0042742627044161) * (m_cv6_decay_27 - m_history_30)));
			t_sample mix_7198 = mix_7848;
			t_sample mix_7849 = (m_history_29 + (((t_sample)0.0042742627044161) * (mix_7198 - m_history_29)));
			t_sample mix_7196 = mix_7849;
			t_sample mix_7850 = (m_history_28 + (((t_sample)0.0042742627044161) * (mix_7196 - m_history_28)));
			t_sample mix_7194 = mix_7850;
			t_sample gen_7212 = mix_7194;
			t_sample history_7199_next_7201 = fixdenorm(mix_7198);
			t_sample history_7197_next_7202 = fixdenorm(mix_7196);
			t_sample history_7195_next_7203 = fixdenorm(mix_7194);
			t_sample mix_7851 = (m_history_22 + (((t_sample)0.0042742627044161) * (m_cv7_dampen_26 - m_history_22)));
			t_sample mix_7767 = mix_7851;
			t_sample mix_7852 = (m_history_21 + (((t_sample)0.0042742627044161) * (mix_7767 - m_history_21)));
			t_sample mix_7768 = mix_7852;
			t_sample mix_7853 = (m_history_20 + (((t_sample)0.0042742627044161) * (mix_7768 - m_history_20)));
			t_sample mix_7766 = mix_7853;
			t_sample gen_7211 = mix_7766;
			t_sample history_7199_next_7759 = fixdenorm(mix_7767);
			t_sample history_7197_next_7764 = fixdenorm(mix_7768);
			t_sample history_7195_next_7761 = fixdenorm(mix_7766);
			t_sample mix_7854 = (m_history_19 + (((t_sample)0.0042742627044161) * (m_cv5_portamento_24 - m_history_19)));
			t_sample mix_7773 = mix_7854;
			t_sample mix_7855 = (m_history_18 + (((t_sample)0.0042742627044161) * (mix_7773 - m_history_18)));
			t_sample mix_7780 = mix_7855;
			t_sample mix_7856 = (m_history_17 + (((t_sample)0.0042742627044161) * (mix_7780 - m_history_17)));
			t_sample mix_7776 = mix_7856;
			t_sample gen_7213 = mix_7776;
			t_sample history_7199_next_7772 = fixdenorm(mix_7773);
			t_sample history_7197_next_7774 = fixdenorm(mix_7780);
			t_sample history_7195_next_7775 = fixdenorm(mix_7776);
			t_sample expr_7583 = m_decay_4;
			t_sample expr_7582 = m_pitch_1;
			t_sample expr_7585 = m_dampen_3;
			t_sample expr_7584 = m_portamento_2;
			int gt_7351 = (m_avg_14 > ((int)0));
			int gen_7590 = gt_7351;
			int not_7347 = (!m_history_15);
			int mul_7350 = (((int)0) * not_7347);
			t_sample mul_7354 = (expr_7584 * samplerate);
			__m_latch_31 = ((mul_7350 != 0) ? expr_7582 : __m_latch_31);
			t_sample latch_7346 = __m_latch_31;
			t_sample mul_7343 = (expr_7583 * latch_7346);
			t_sample t_7342 = exp(safediv(-6.9077552789821, mul_7343));
			t_sample rdiv_7357 = safediv(samplerate, latch_7346);
			t_sample iup_33 = (1 / maximum(1, abs(mul_7354)));
			t_sample idown_34 = (1 / maximum(1, abs(mul_7354)));
			__m_slide_32 = fixdenorm((__m_slide_32 + (((rdiv_7357 > __m_slide_32) ? iup_33 : idown_34) * (rdiv_7357 - __m_slide_32))));
			t_sample slide_7356 = __m_slide_32;
			t_sample sub_7358 = (slide_7356 - ((int)1));
			t_sample tap_7362 = m_delay_16.read_linear(sub_7358);
			t_sample mul_7344 = (tap_7362 * t_7342);
			t_sample mix_7857 = (mul_7344 + (expr_7585 * (m_avg_14 - mul_7344)));
			t_sample mix_7360 = mix_7857;
			t_sample history_7349_next_7587 = fixdenorm(gt_7351);
			t_sample avg_next_7588 = fixdenorm(mix_7360);
			t_sample mix_7858 = (m_history_13 + (((t_sample)0.0042742627044161) * (gen_7210 - m_history_13)));
			t_sample mix_7794 = mix_7858;
			t_sample mix_7859 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_7794 - m_history_12)));
			t_sample mix_7786 = mix_7859;
			t_sample mix_7860 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_7786 - m_history_11)));
			t_sample mix_7793 = mix_7860;
			t_sample gen_7204 = mix_7793;
			t_sample history_7199_next_7785 = fixdenorm(mix_7794);
			t_sample history_7197_next_7792 = fixdenorm(mix_7786);
			t_sample history_7195_next_7790 = fixdenorm(mix_7793);
			int int_7214 = int(in1);
			int change_7215 = __m_change_35(int_7214);
			int eqp_7216 = ((int_7214 == change_7215) ? int_7214 : 0);
			int gen_7217 = eqp_7216;
			t_sample expr_7178 = m_portamento_2;
			t_sample gen_7227 = m_avg_8;
			t_sample expr_7179 = m_dampen_3;
			t_sample expr_7177 = m_decay_4;
			t_sample expr_7176 = m_pitch_1;
			int gt_7164 = (m_avg_8 > ((int)0));
			t_sample mul_7161 = (gen_7217 * m_history_9);
			t_sample gen_7223 = mul_7161;
			int not_7160 = (!m_history_9);
			int mul_7163 = (gen_7217 * not_7160);
			t_sample mul_7167 = (expr_7178 * samplerate);
			__m_latch_36 = ((mul_7163 != 0) ? expr_7176 : __m_latch_36);
			t_sample latch_7159 = __m_latch_36;
			t_sample rdiv_7170 = safediv(samplerate, latch_7159);
			t_sample iup_38 = (1 / maximum(1, abs(mul_7167)));
			t_sample idown_39 = (1 / maximum(1, abs(mul_7167)));
			__m_slide_37 = fixdenorm((__m_slide_37 + (((rdiv_7170 > __m_slide_37) ? iup_38 : idown_39) * (rdiv_7170 - __m_slide_37))));
			t_sample slide_7169 = __m_slide_37;
			t_sample sub_7171 = (slide_7169 - ((int)1));
			t_sample tap_7175 = m_delay_10.read_linear(sub_7171);
			t_sample gen_7225 = tap_7175;
			t_sample mul_7156 = (expr_7177 * latch_7159);
			t_sample t_7155 = exp(safediv(-6.9077552789821, mul_7156));
			t_sample mul_7157 = (tap_7175 * t_7155);
			t_sample mix_7861 = (mul_7157 + (expr_7179 * (m_avg_8 - mul_7157)));
			t_sample mix_7173 = mix_7861;
			t_sample history_7162_next_7180 = fixdenorm(gt_7164);
			t_sample avg_next_7181 = fixdenorm(mix_7173);
			t_sample out4 = gen_7227;
			t_sample expr_7819 = m_portamento_2;
			t_sample expr_7818 = m_dampen_3;
			t_sample expr_7821 = m_decay_4;
			t_sample expr_7823 = m_pitch_1;
			int gt_7803 = (m_avg_5 > ((int)0));
			int gen_7188 = gt_7803;
			int not_7815 = (!m_history_6);
			t_sample mul_7800 = (gen_7223 * not_7815);
			t_sample mul_7814 = (expr_7819 * samplerate);
			__m_latch_40 = ((mul_7800 != 0) ? expr_7823 : __m_latch_40);
			t_sample latch_7813 = __m_latch_40;
			t_sample rdiv_7816 = safediv(samplerate, latch_7813);
			t_sample iup_42 = (1 / maximum(1, abs(mul_7814)));
			t_sample idown_43 = (1 / maximum(1, abs(mul_7814)));
			__m_slide_41 = fixdenorm((__m_slide_41 + (((rdiv_7816 > __m_slide_41) ? iup_42 : idown_43) * (rdiv_7816 - __m_slide_41))));
			t_sample slide_7811 = __m_slide_41;
			t_sample sub_7810 = (slide_7811 - ((int)1));
			t_sample tap_7801 = m_delay_7.read_linear(sub_7810);
			t_sample gen_7189 = tap_7801;
			t_sample mul_7802 = (expr_7821 * latch_7813);
			t_sample t_7809 = exp(safediv(-6.9077552789821, mul_7802));
			t_sample mul_7808 = (tap_7801 * t_7809);
			t_sample mix_7862 = (mul_7808 + (expr_7818 * (m_avg_5 - mul_7808)));
			t_sample mix_7806 = mix_7862;
			t_sample history_7162_next_7805 = fixdenorm(gt_7803);
			t_sample avg_next_7804 = fixdenorm(mix_7806);
			t_sample out3 = (gen_7590 + gen_7188);
			t_sample out2 = ((int)0);
			t_sample mul_7192 = ((gen_7225 + gen_7189) * ((t_sample)0.25));
			t_sample out1 = mul_7192;
			t_sample decay_next_7827 = fixdenorm(gen_7212);
			t_sample dampen_next_7828 = fixdenorm(gen_7211);
			t_sample portamento_next_7829 = fixdenorm(gen_7213);
			t_sample pitch_next_7830 = fixdenorm(gen_7204);
			m_history_30 = history_7199_next_7201;
			m_history_28 = history_7195_next_7203;
			m_history_29 = history_7197_next_7202;
			m_history_22 = history_7199_next_7759;
			m_history_20 = history_7195_next_7761;
			m_history_21 = history_7197_next_7764;
			m_history_19 = history_7199_next_7772;
			m_history_17 = history_7195_next_7775;
			m_history_18 = history_7197_next_7774;
			m_delay_16.write((m_avg_14 + mul_7350));
			m_avg_14 = avg_next_7588;
			m_history_15 = history_7349_next_7587;
			m_history_13 = history_7199_next_7785;
			m_history_11 = history_7195_next_7790;
			m_history_12 = history_7197_next_7792;
			m_delay_10.write((((m_avg_8 + mul_7163) + gen_7217) + ((int)0)));
			m_avg_8 = avg_next_7181;
			m_history_9 = history_7162_next_7180;
			m_delay_7.write((((m_avg_5 + mul_7800) + gen_7223) + ((int)0)));
			m_avg_5 = avg_next_7804;
			m_history_6 = history_7162_next_7805;
			m_decay_4 = decay_next_7827;
			m_dampen_3 = dampen_next_7828;
			m_portamento_2 = portamento_next_7829;
			m_pitch_1 = pitch_next_7830;
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
	inline void set_gate1(t_param _value) {
		m_gate_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv5_portamento(t_param _value) {
		m_cv5_portamento_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv1_pitch(t_param _value) {
		m_cv1_pitch_25 = (_value < 0 ? 0 : (_value > 5 ? 5 : _value));
	};
	inline void set_cv7_dampen(t_param _value) {
		m_cv7_dampen_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv6_decay(t_param _value) {
		m_cv6_decay_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: *value = self->m_cv1_pitch_25; break;
		case 1: *value = self->m_cv5_portamento_24; break;
		case 2: *value = self->m_cv6_decay_27; break;
		case 3: *value = self->m_cv7_dampen_26; break;
		case 4: *value = self->m_gate_23; break;
		
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
	// initialize parameter 0 ("m_cv1_pitch_25")
	pi = self->__commonstate.params + 0;
	pi->name = "cv1_pitch";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv1_pitch_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_cv5_portamento_24")
	pi = self->__commonstate.params + 1;
	pi->name = "cv5_portamento";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv5_portamento_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_cv6_decay_27")
	pi = self->__commonstate.params + 2;
	pi->name = "cv6_decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv6_decay_27;
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
	// initialize parameter 4 ("m_gate_23")
	pi = self->__commonstate.params + 4;
	pi->name = "gate1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_23;
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
