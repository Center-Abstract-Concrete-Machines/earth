#include "simple_2dpitch.h"

namespace simple_2dpitch {

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
	Phasor __m_phasor_14;
	Phasor __m_phasor_18;
	Phasor __m_phasor_26;
	Phasor __m_phasor_22;
	Phasor __m_phasor_10;
	Phasor __m_phasor_30;
	PlusEquals __m_pluseq_20;
	PlusEquals __m_pluseq_12;
	PlusEquals __m_pluseq_16;
	PlusEquals __m_pluseq_28;
	PlusEquals __m_pluseq_24;
	PlusEquals __m_pluseq_32;
	int __exception;
	int vectorsize;
	t_sample __m_latch_23;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample __m_latch_25;
	t_sample m_env_shape_1;
	t_sample __m_latch_27;
	t_sample __m_latch_21;
	t_sample __m_latch_29;
	t_sample samplerate;
	t_sample __m_latch_9;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample m_history_7;
	t_sample __m_latch_11;
	t_sample m_pitch_8;
	t_sample __m_latch_19;
	t_sample __m_latch_13;
	t_sample __m_latch_15;
	t_sample __m_latch_31;
	t_sample __m_latch_17;
	t_sample m_history_6;
	t_sample samples_to_seconds;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_env_shape_1 = (-1);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_pitch_8 = ((int)0);
		__m_latch_9 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_10.reset(0);
		__m_latch_11 = 1;
		__m_pluseq_12.reset(0);
		__m_latch_13 = 0;
		__m_phasor_14.reset(0);
		__m_latch_15 = 1;
		__m_pluseq_16.reset(0);
		__m_latch_17 = 0;
		__m_phasor_18.reset(0);
		__m_latch_19 = 1;
		__m_pluseq_20.reset(0);
		__m_latch_21 = 0;
		__m_phasor_22.reset(0);
		__m_latch_23 = 1;
		__m_pluseq_24.reset(0);
		__m_latch_25 = 0;
		__m_phasor_26.reset(0);
		__m_latch_27 = 1;
		__m_pluseq_28.reset(0);
		__m_latch_29 = 0;
		__m_phasor_30.reset(0);
		__m_latch_31 = 1;
		__m_pluseq_32.reset(0);
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
		samples_to_seconds = (1 / samplerate);
		t_sample exp_6366 = exp(m_env_shape_1);
		int sign_6356 = ((exp_6366 > 0) ? 1 : ((exp_6366 < 0) ? -1 : 0));
		t_sample abs_6357 = fabs(exp_6366);
		t_sample exp_7035 = exp(m_env_shape_1);
		int sign_7013 = ((exp_7035 > 0) ? 1 : ((exp_7035 < 0) ? -1 : 0));
		t_sample abs_7017 = fabs(exp_7035);
		t_sample exp_7049 = exp(m_env_shape_1);
		int sign_7039 = ((exp_7049 > 0) ? 1 : ((exp_7049 < 0) ? -1 : 0));
		t_sample abs_7041 = fabs(exp_7049);
		t_sample exp_7086 = exp(m_env_shape_1);
		int sign_7082 = ((exp_7086 > 0) ? 1 : ((exp_7086 < 0) ? -1 : 0));
		t_sample abs_7088 = fabs(exp_7086);
		t_sample exp_7115 = exp(m_env_shape_1);
		int sign_7111 = ((exp_7115 > 0) ? 1 : ((exp_7115 < 0) ? -1 : 0));
		t_sample abs_7117 = fabs(exp_7115);
		t_sample exp_7146 = exp(m_env_shape_1);
		int sign_7142 = ((exp_7146 > 0) ? 1 : ((exp_7146 < 0) ? -1 : 0));
		t_sample abs_7125 = fabs(exp_7146);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			const t_sample in3 = (*(__in3++));
			t_sample mtof_6384 = mtof(in2, ((int)440));
			t_sample expr_6373 = m_pitch_8;
			t_sample mul_6369 = (in1 * m_history_2);
			t_sample gen_7006 = mul_6369;
			int not_6368 = (!m_history_2);
			t_sample mul_6371 = (in1 * not_6368);
			__m_latch_9 = ((mul_6371 != 0) ? expr_6373 : __m_latch_9);
			t_sample latch_6346 = __m_latch_9;
			t_sample phasor_6372 = __m_phasor_10(latch_6346, samples_to_seconds);
			t_sample mul_6350 = (in3 * samplerate);
			t_sample rdiv_6351 = safediv(((int)1), mul_6350);
			__m_latch_11 = ((mul_6371 != 0) ? rdiv_6351 : __m_latch_11);
			t_sample latch_6352 = __m_latch_11;
			t_sample plusequals_6354 = __m_pluseq_12.post(latch_6352, mul_6371, 0);
			int lt_6348 = (plusequals_6354 < ((int)1));
			int gen_7008 = lt_6348;
			t_sample min_6353 = ((((int)1) < plusequals_6354) ? ((int)1) : plusequals_6354);
			t_sample sub_6359 = (min_6353 - ((t_sample)0.5));
			t_sample mul_6360 = (sub_6359 * sub_6359);
			t_sample mul_6361 = (mul_6360 * (-6.2831853071796));
			t_sample exp_6362 = exp(mul_6361);
			t_sample pow_6365 = safepow(min_6353, abs_6357);
			t_sample mul_6355 = (pow_6365 * sign_6356);
			t_sample mul_6364 = (mul_6355 * ((t_sample)3.1415926535898));
			t_sample sin_6363 = sin(mul_6364);
			t_sample mul_6358 = (exp_6362 * sin_6363);
			t_sample mul_6349 = (phasor_6372 * mul_6358);
			t_sample history_6370_next_6374 = fixdenorm(lt_6348);
			t_sample expr_7030 = m_pitch_8;
			t_sample mul_7012 = (gen_7006 * m_history_3);
			t_sample gen_6389 = mul_7012;
			int not_7009 = (!m_history_3);
			t_sample mul_7029 = (gen_7006 * not_7009);
			__m_latch_13 = ((mul_7029 != 0) ? expr_7030 : __m_latch_13);
			t_sample latch_7025 = __m_latch_13;
			t_sample phasor_7036 = __m_phasor_14(latch_7025, samples_to_seconds);
			t_sample mul_7024 = (in3 * samplerate);
			t_sample rdiv_7026 = safediv(((int)1), mul_7024);
			__m_latch_15 = ((mul_7029 != 0) ? rdiv_7026 : __m_latch_15);
			t_sample latch_7022 = __m_latch_15;
			t_sample plusequals_7033 = __m_pluseq_16.post(latch_7022, mul_7029, 0);
			int lt_7032 = (plusequals_7033 < ((int)1));
			int gen_6391 = lt_7032;
			t_sample min_7027 = ((((int)1) < plusequals_7033) ? ((int)1) : plusequals_7033);
			t_sample sub_7028 = (min_7027 - ((t_sample)0.5));
			t_sample mul_7034 = (sub_7028 * sub_7028);
			t_sample mul_7023 = (mul_7034 * (-6.2831853071796));
			t_sample exp_7031 = exp(mul_7023);
			t_sample pow_7020 = safepow(min_7027, abs_7017);
			t_sample mul_7019 = (pow_7020 * sign_7013);
			t_sample mul_7018 = (mul_7019 * ((t_sample)3.1415926535898));
			t_sample sin_7016 = sin(mul_7018);
			t_sample mul_7015 = (exp_7031 * sin_7016);
			t_sample mul_7021 = (phasor_7036 * mul_7015);
			t_sample history_6370_next_7010 = fixdenorm(lt_7032);
			t_sample expr_7065 = m_pitch_8;
			t_sample mul_7051 = (gen_6389 * m_history_4);
			t_sample gen_6386 = mul_7051;
			int not_7038 = (!m_history_4);
			t_sample mul_7045 = (gen_6389 * not_7038);
			__m_latch_17 = ((mul_7045 != 0) ? expr_7065 : __m_latch_17);
			t_sample latch_7063 = __m_latch_17;
			t_sample phasor_7050 = __m_phasor_18(latch_7063, samples_to_seconds);
			t_sample mul_7064 = (in3 * samplerate);
			t_sample rdiv_7043 = safediv(((int)1), mul_7064);
			__m_latch_19 = ((mul_7045 != 0) ? rdiv_7043 : __m_latch_19);
			t_sample latch_7057 = __m_latch_19;
			t_sample plusequals_7062 = __m_pluseq_20.post(latch_7057, mul_7045, 0);
			int lt_7046 = (plusequals_7062 < ((int)1));
			int gen_6388 = lt_7046;
			t_sample min_7056 = ((((int)1) < plusequals_7062) ? ((int)1) : plusequals_7062);
			t_sample sub_7058 = (min_7056 - ((t_sample)0.5));
			t_sample mul_7048 = (sub_7058 * sub_7058);
			t_sample mul_7055 = (mul_7048 * (-6.2831853071796));
			t_sample exp_7047 = exp(mul_7055);
			t_sample pow_7054 = safepow(min_7056, abs_7041);
			t_sample mul_7059 = (pow_7054 * sign_7039);
			t_sample mul_7042 = (mul_7059 * ((t_sample)3.1415926535898));
			t_sample sin_7060 = sin(mul_7042);
			t_sample mul_7061 = (exp_7047 * sin_7060);
			t_sample mul_7053 = (phasor_7050 * mul_7061);
			t_sample history_6370_next_7044 = fixdenorm(lt_7046);
			t_sample expr_7073 = m_pitch_8;
			t_sample mul_7087 = (gen_6386 * m_history_5);
			t_sample gen_6381 = mul_7087;
			int not_7067 = (!m_history_5);
			t_sample mul_7072 = (gen_6386 * not_7067);
			__m_latch_21 = ((mul_7072 != 0) ? expr_7073 : __m_latch_21);
			t_sample latch_7090 = __m_latch_21;
			t_sample phasor_7075 = __m_phasor_22(latch_7090, samples_to_seconds);
			t_sample mul_7091 = (in3 * samplerate);
			t_sample rdiv_7071 = safediv(((int)1), mul_7091);
			__m_latch_23 = ((mul_7072 != 0) ? rdiv_7071 : __m_latch_23);
			t_sample latch_7092 = __m_latch_23;
			t_sample plusequals_7093 = __m_pluseq_24.post(latch_7092, mul_7072, 0);
			int lt_7084 = (plusequals_7093 < ((int)1));
			int gen_6383 = lt_7084;
			t_sample min_7089 = ((((int)1) < plusequals_7093) ? ((int)1) : plusequals_7093);
			t_sample sub_7079 = (min_7089 - ((t_sample)0.5));
			t_sample mul_7074 = (sub_7079 * sub_7079);
			t_sample mul_7078 = (mul_7074 * (-6.2831853071796));
			t_sample exp_7085 = exp(mul_7078);
			t_sample pow_7083 = safepow(min_7089, abs_7088);
			t_sample mul_7080 = (pow_7083 * sign_7082);
			t_sample mul_7070 = (mul_7080 * ((t_sample)3.1415926535898));
			t_sample sin_7081 = sin(mul_7070);
			t_sample mul_7094 = (exp_7085 * sin_7081);
			t_sample mul_7077 = (phasor_7075 * mul_7094);
			t_sample history_6370_next_7069 = fixdenorm(lt_7084);
			t_sample expr_7102 = m_pitch_8;
			t_sample mul_7116 = (gen_6381 * m_history_6);
			t_sample gen_6378 = mul_7116;
			int not_7096 = (!m_history_6);
			t_sample mul_7101 = (gen_6381 * not_7096);
			__m_latch_25 = ((mul_7101 != 0) ? expr_7102 : __m_latch_25);
			t_sample latch_7120 = __m_latch_25;
			t_sample phasor_7104 = __m_phasor_26(latch_7120, samples_to_seconds);
			t_sample mul_7122 = (in3 * samplerate);
			t_sample rdiv_7100 = safediv(((int)1), mul_7122);
			__m_latch_27 = ((mul_7101 != 0) ? rdiv_7100 : __m_latch_27);
			t_sample latch_7121 = __m_latch_27;
			t_sample plusequals_7123 = __m_pluseq_28.post(latch_7121, mul_7101, 0);
			int lt_7113 = (plusequals_7123 < ((int)1));
			int gen_6380 = lt_7113;
			t_sample min_7119 = ((((int)1) < plusequals_7123) ? ((int)1) : plusequals_7123);
			t_sample sub_7108 = (min_7119 - ((t_sample)0.5));
			t_sample mul_7103 = (sub_7108 * sub_7108);
			t_sample mul_7107 = (mul_7103 * (-6.2831853071796));
			t_sample exp_7114 = exp(mul_7107);
			t_sample pow_7112 = safepow(min_7119, abs_7117);
			t_sample mul_7109 = (pow_7112 * sign_7111);
			t_sample mul_7099 = (mul_7109 * ((t_sample)3.1415926535898));
			t_sample sin_7110 = sin(mul_7099);
			t_sample mul_7118 = (exp_7114 * sin_7110);
			t_sample mul_7106 = (phasor_7104 * mul_7118);
			t_sample history_6370_next_7098 = fixdenorm(lt_7113);
			t_sample expr_7128 = m_pitch_8;
			int not_7143 = (!m_history_7);
			t_sample mul_7127 = (gen_6378 * not_7143);
			__m_latch_29 = ((mul_7127 != 0) ? expr_7128 : __m_latch_29);
			t_sample latch_7136 = __m_latch_29;
			t_sample phasor_7139 = __m_phasor_30(latch_7136, samples_to_seconds);
			t_sample mul_7145 = (in3 * samplerate);
			t_sample rdiv_7148 = safediv(((int)1), mul_7145);
			__m_latch_31 = ((mul_7127 != 0) ? rdiv_7148 : __m_latch_31);
			t_sample latch_7151 = __m_latch_31;
			t_sample plusequals_7137 = __m_pluseq_32.post(latch_7151, mul_7127, 0);
			int lt_7144 = (plusequals_7137 < ((int)1));
			int gen_6377 = lt_7144;
			t_sample min_7150 = ((((int)1) < plusequals_7137) ? ((int)1) : plusequals_7137);
			t_sample sub_7140 = (min_7150 - ((t_sample)0.5));
			t_sample mul_7149 = (sub_7140 * sub_7140);
			t_sample mul_7131 = (mul_7149 * (-6.2831853071796));
			t_sample exp_7134 = exp(mul_7131);
			t_sample pow_7133 = safepow(min_7150, abs_7125);
			t_sample mul_7132 = (pow_7133 * sign_7142);
			t_sample mul_7126 = (mul_7132 * ((t_sample)3.1415926535898));
			t_sample sin_7141 = sin(mul_7126);
			t_sample mul_7152 = (exp_7134 * sin_7141);
			t_sample mul_7130 = (phasor_7139 * mul_7152);
			t_sample history_6370_next_7147 = fixdenorm(lt_7144);
			t_sample out2 = (((((gen_6383 + gen_6380) + gen_6377) + gen_7008) + gen_6388) + gen_6391);
			t_sample mul_6385 = ((((((mul_7130 + mul_7106) + mul_7077) + mul_6349) + mul_7053) + mul_7021) * ((t_sample)0.25));
			t_sample out1 = mul_6385;
			t_sample pitch_next_7154 = fixdenorm(mtof_6384);
			m_history_2 = history_6370_next_6374;
			m_pitch_8 = pitch_next_7154;
			m_history_7 = history_6370_next_7147;
			m_history_6 = history_6370_next_7098;
			m_history_5 = history_6370_next_7069;
			m_history_4 = history_6370_next_7044;
			m_history_3 = history_6370_next_7010;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_env_shape(t_param _value) {
		m_env_shape_1 = (_value < -3 ? -3 : (_value > 3 ? 3 : _value));
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
int num_params() { return 1; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2", "in3" };
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
		case 0: self->set_env_shape(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_env_shape_1; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(1 * sizeof(ParamInfo));
	self->__commonstate.numparams = 1;
	// initialize parameter 0 ("m_env_shape_1")
	pi = self->__commonstate.params + 0;
	pi->name = "env_shape";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_env_shape_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -3;
	pi->outputmax = 3;
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


} // simple_2dpitch::
