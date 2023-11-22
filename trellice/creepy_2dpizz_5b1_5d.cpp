#include "creepy_2dpizz_5b1_5d.h"

namespace creepy_2dpizz_5b1_5d {

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
	DCBlock __m_dcblock_27;
	DCBlock __m_dcblock_25;
	DCBlock __m_dcblock_26;
	DCBlock __m_dcblock_28;
	Delay m_delay_7;
	Delay m_delay_8;
	Delay m_delay_6;
	Delay m_delay_11;
	Delay m_delay_13;
	Delay m_delay_10;
	Delay m_delay_12;
	Delay m_delay_9;
	Phasor __m_phasor_19;
	Phasor __m_phasor_20;
	int vectorsize;
	int __exception;
	t_sample __m_latch_34;
	t_sample __m_latch_33;
	t_sample __m_latch_31;
	t_sample __m_latch_32;
	t_sample __m_latch_30;
	t_sample __m_latch_29;
	t_sample m_history_15;
	t_sample m_history_18;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample samples_to_seconds;
	t_sample m_history_4;
	t_sample m_history_14;
	t_sample m_history_17;
	t_sample m_history_5;
	t_sample m_history_16;
	t_sample __m_latch_35;
	t_sample __m_latch_36;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_delay_6.reset("m_delay_6", ((int)100));
		m_delay_7.reset("m_delay_7", ((int)100));
		m_delay_8.reset("m_delay_8", ((int)100));
		m_delay_9.reset("m_delay_9", ((int)100));
		m_delay_10.reset("m_delay_10", ((int)3000));
		m_delay_11.reset("m_delay_11", ((int)3000));
		m_delay_12.reset("m_delay_12", ((int)3000));
		m_delay_13.reset("m_delay_13", ((int)3000));
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_19.reset(0);
		__m_phasor_20.reset(0);
		__m_dcblock_25.reset();
		__m_dcblock_26.reset();
		__m_dcblock_27.reset();
		__m_dcblock_28.reset();
		__m_latch_29 = 0;
		__m_latch_30 = 0;
		__m_latch_31 = 0;
		__m_latch_32 = 0;
		__m_latch_33 = 0;
		__m_latch_34 = 0;
		__m_latch_35 = 0;
		__m_latch_36 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		const t_sample * __in3 = __ins[2];
		const t_sample * __in4 = __ins[3];
		const t_sample * __in5 = __ins[4];
		const t_sample * __in6 = __ins[5];
		const t_sample * __in7 = __ins[6];
		const t_sample * __in8 = __ins[7];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__in3 == 0) || (__in4 == 0) || (__in5 == 0) || (__in6 == 0) || (__in7 == 0) || (__in8 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		samples_to_seconds = (1 / samplerate);
		t_sample history_78_next_112 = fixdenorm(((int)1));
		t_sample history_181_next_191 = fixdenorm(((int)1));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			const t_sample in3 = (*(__in3++));
			const t_sample in4 = (*(__in4++));
			const t_sample in5 = (*(__in5++));
			const t_sample in6 = (*(__in6++));
			const t_sample in7 = (*(__in7++));
			const t_sample in8 = (*(__in8++));
			t_sample min_38 = ((in4 < ((int)0)) ? ((int)0) : in4);
			t_sample min_35 = ((in5 < ((int)0)) ? ((int)0) : in5);
			t_sample min_34 = ((in6 < ((int)0)) ? ((int)0) : in6);
			t_sample clamp_33 = ((in7 <= ((int)0)) ? ((int)0) : ((in7 >= ((int)1)) ? ((int)1) : in7));
			t_sample clamp_32 = ((in8 <= ((int)0)) ? ((int)0) : ((in8 >= ((int)1)) ? ((int)1) : in8));
			t_sample clamp_53 = ((clamp_33 <= ((int)0)) ? ((int)0) : ((clamp_33 >= ((int)1)) ? ((int)1) : clamp_33));
			t_sample min_71 = ((min_34 < ((int)0)) ? ((int)0) : min_34);
			t_sample t_66 = exp(safediv(-6.9077552789821, min_71));
			t_sample phasor_135 = __m_phasor_19(min_35, samples_to_seconds);
			t_sample mul_134 = (phasor_135 * ((t_sample)6.2831853071796));
			t_sample cos_133 = cos(mul_134);
			t_sample gen_136 = cos_133;
			t_sample mul_131 = (cos_133 * (-1));
			t_sample gen_139 = mul_131;
			t_sample sin_132 = sin(mul_134);
			t_sample gen_138 = sin_132;
			t_sample gen_137 = sin_132;
			t_sample mul_125 = (min_35 * ((t_sample)3.1415926535898));
			t_sample phasor_126 = __m_phasor_20(mul_125, samples_to_seconds);
			t_sample mul_130 = (phasor_126 * ((t_sample)6.2831853071796));
			t_sample cos_129 = cos(mul_130);
			t_sample gen_140 = cos_129;
			t_sample mul_127 = (cos_129 * (-1));
			t_sample gen_143 = mul_127;
			t_sample sin_128 = sin(mul_130);
			t_sample gen_141 = sin_128;
			t_sample gen_142 = sin_128;
			t_sample add_76 = (m_history_18 + ((int)1));
			t_sample noise_110 = noise();
			t_sample noise_87 = noise();
			t_sample noise_103 = noise();
			t_sample noise_94 = noise();
			int sign_93 = ((noise_94 > 0) ? 1 : ((noise_94 < 0) ? -1 : 0));
			int sign_86 = ((noise_87 > 0) ? 1 : ((noise_87 < 0) ? -1 : 0));
			int sign_102 = ((noise_103 > 0) ? 1 : ((noise_103 < 0) ? -1 : 0));
			int sign_109 = ((noise_110 > 0) ? 1 : ((noise_110 < 0) ? -1 : 0));
			t_sample div_81 = (clamp_32 * ((t_sample)0.00033333333333333));
			t_sample mul_79 = (sign_93 * div_81);
			t_sample add_90 = (m_history_17 + mul_79);
			t_sample clamp_89 = ((add_90 <= ((int)0)) ? ((int)0) : ((add_90 >= ((int)1)) ? ((int)1) : add_90));
			t_sample mul_73 = (clamp_89 * ((int)3000));
			t_sample gen_121 = mul_73;
			t_sample rsub_95 = (((int)3000) - mul_73);
			t_sample gen_122 = rsub_95;
			t_sample choice_21 = int(add_76);
			t_sample selector_92 = ((choice_21 >= 2) ? clamp_89 : ((choice_21 >= 1) ? noise_94 : 0));
			t_sample mul_80 = (sign_86 * div_81);
			t_sample add_83 = (m_history_16 + mul_80);
			t_sample clamp_82 = ((add_83 <= ((int)0)) ? ((int)0) : ((add_83 >= ((int)1)) ? ((int)1) : add_83));
			t_sample mul_72 = (clamp_82 * ((int)3000));
			t_sample gen_123 = mul_72;
			t_sample rsub_88 = (((int)3000) - mul_72);
			t_sample gen_124 = rsub_88;
			t_sample choice_22 = int(add_76);
			t_sample selector_85 = ((choice_22 >= 2) ? clamp_82 : ((choice_22 >= 1) ? noise_87 : 0));
			t_sample mul_97 = (sign_102 * div_81);
			t_sample add_99 = (m_history_15 + mul_97);
			t_sample clamp_98 = ((add_99 <= ((int)0)) ? ((int)0) : ((add_99 >= ((int)1)) ? ((int)1) : add_99));
			t_sample mul_74 = (clamp_98 * ((int)3000));
			t_sample gen_119 = mul_74;
			t_sample rsub_104 = (((int)3000) - mul_74);
			t_sample gen_120 = rsub_104;
			t_sample choice_23 = int(add_76);
			t_sample selector_101 = ((choice_23 >= 2) ? clamp_98 : ((choice_23 >= 1) ? noise_103 : 0));
			t_sample mul_96 = (sign_109 * div_81);
			t_sample add_106 = (m_history_14 + mul_96);
			t_sample clamp_105 = ((add_106 <= ((int)0)) ? ((int)0) : ((add_106 >= ((int)1)) ? ((int)1) : add_106));
			t_sample mul_75 = (clamp_105 * ((int)3000));
			t_sample gen_117 = mul_75;
			t_sample rsub_111 = (((int)3000) - mul_75);
			t_sample gen_118 = rsub_111;
			t_sample choice_24 = int(add_76);
			t_sample selector_108 = ((choice_24 >= 2) ? clamp_105 : ((choice_24 >= 1) ? noise_110 : 0));
			t_sample history_91_next_113 = fixdenorm(selector_92);
			t_sample history_84_next_114 = fixdenorm(selector_85);
			t_sample history_100_next_115 = fixdenorm(selector_101);
			t_sample history_107_next_116 = fixdenorm(selector_108);
			t_sample tap_221 = m_delay_13.read_step(gen_117);
			t_sample tap_222 = m_delay_13.read_step(gen_118);
			t_sample mul_218 = (tap_221 * gen_136);
			t_sample mul_219 = (tap_222 * gen_137);
			t_sample tap_212 = m_delay_12.read_step(gen_119);
			t_sample tap_213 = m_delay_12.read_step(gen_120);
			t_sample mul_215 = (tap_212 * gen_138);
			t_sample add_217 = (mul_218 + mul_215);
			t_sample mul_70 = (add_217 * t_66);
			t_sample mix_3872 = (mul_70 + (clamp_53 * (m_history_4 - mul_70)));
			t_sample mix_57 = mix_3872;
			t_sample dcblock_65 = __m_dcblock_25(mix_57);
			t_sample mul_45 = (dcblock_65 * safediv(1, sqrt(2)));
			t_sample mul_214 = (tap_213 * gen_139);
			t_sample add_216 = (mul_219 + mul_214);
			t_sample mul_69 = (add_216 * t_66);
			t_sample mix_3873 = (mul_69 + (clamp_53 * (m_history_3 - mul_69)));
			t_sample mix_59 = mix_3873;
			t_sample dcblock_64 = __m_dcblock_26(mix_59);
			t_sample mul_46 = (dcblock_64 * safediv(1, sqrt(2)));
			t_sample add_44 = (mul_45 + mul_46);
			t_sample add_52 = (add_44 + ((int)0));
			t_sample sub_43 = (mul_45 - mul_46);
			t_sample add_51 = (sub_43 + ((int)0));
			t_sample tap_209 = m_delay_11.read_step(gen_121);
			t_sample tap_210 = m_delay_11.read_step(gen_122);
			t_sample mul_206 = (tap_209 * gen_140);
			t_sample mul_207 = (tap_210 * gen_141);
			t_sample tap_200 = m_delay_10.read_step(gen_123);
			t_sample tap_201 = m_delay_10.read_step(gen_124);
			t_sample mul_203 = (tap_200 * gen_142);
			t_sample add_205 = (mul_206 + mul_203);
			t_sample mul_68 = (add_205 * t_66);
			t_sample mix_3874 = (mul_68 + (clamp_53 * (m_history_2 - mul_68)));
			t_sample mix_61 = mix_3874;
			t_sample dcblock_63 = __m_dcblock_27(mix_61);
			t_sample mul_47 = (dcblock_63 * safediv(1, sqrt(2)));
			t_sample mul_202 = (tap_201 * gen_143);
			t_sample add_204 = (mul_207 + mul_202);
			t_sample mul_67 = (add_204 * t_66);
			t_sample mix_3875 = (mul_67 + (clamp_53 * (m_history_1 - mul_67)));
			t_sample mix_55 = mix_3875;
			t_sample dcblock_62 = __m_dcblock_28(mix_55);
			t_sample mul_48 = (dcblock_62 * safediv(1, sqrt(2)));
			t_sample add_41 = (mul_48 + mul_47);
			t_sample add_49 = (add_41 + ((int)0));
			t_sample sub_42 = (mul_48 - mul_47);
			t_sample add_50 = (sub_42 + ((int)0));
			t_sample add_223 = (add_49 + in1);
			t_sample add_198 = (add_50 + in1);
			t_sample add_197 = (add_51 + in1);
			t_sample add_196 = (add_52 + in1);
			t_sample noise_169 = noise();
			int not_179 = (!m_history_5);
			__m_latch_29 = ((not_179 != 0) ? noise_169 : __m_latch_29);
			t_sample latch_168 = __m_latch_29;
			t_sample mul_176 = (add_198 * latch_168);
			t_sample noise_183 = noise();
			__m_latch_30 = ((not_179 != 0) ? noise_183 : __m_latch_30);
			t_sample latch_182 = __m_latch_30;
			t_sample mul_190 = (add_223 * latch_182);
			t_sample noise_158 = noise();
			__m_latch_31 = ((not_179 != 0) ? noise_158 : __m_latch_31);
			t_sample latch_157 = __m_latch_31;
			t_sample mul_165 = (add_197 * latch_157);
			t_sample noise_147 = noise();
			__m_latch_32 = ((not_179 != 0) ? noise_147 : __m_latch_32);
			t_sample latch_146 = __m_latch_32;
			t_sample mul_154 = (add_196 * latch_146);
			t_sample noise_167 = noise();
			__m_latch_33 = ((not_179 != 0) ? noise_167 : __m_latch_33);
			t_sample latch_166 = __m_latch_33;
			t_sample mul_170 = (latch_166 * ((int)100));
			t_sample tap_174 = m_delay_9.read_step(mul_170);
			t_sample sub_175 = (tap_174 - mul_176);
			t_sample mul_171 = (sub_175 * latch_168);
			t_sample add_172 = (mul_171 + add_198);
			t_sample noise_178 = noise();
			__m_latch_34 = ((not_179 != 0) ? noise_178 : __m_latch_34);
			t_sample latch_177 = __m_latch_34;
			t_sample mul_184 = (latch_177 * ((int)100));
			t_sample tap_188 = m_delay_8.read_step(mul_184);
			t_sample sub_189 = (tap_188 - mul_190);
			t_sample mul_185 = (sub_189 * latch_182);
			t_sample add_186 = (mul_185 + add_223);
			t_sample noise_156 = noise();
			__m_latch_35 = ((not_179 != 0) ? noise_156 : __m_latch_35);
			t_sample latch_155 = __m_latch_35;
			t_sample mul_159 = (latch_155 * ((int)100));
			t_sample tap_163 = m_delay_7.read_step(mul_159);
			t_sample sub_164 = (tap_163 - mul_165);
			t_sample mul_160 = (sub_164 * latch_157);
			t_sample add_161 = (mul_160 + add_197);
			t_sample noise_145 = noise();
			__m_latch_36 = ((not_179 != 0) ? noise_145 : __m_latch_36);
			t_sample latch_144 = __m_latch_36;
			t_sample mul_148 = (latch_144 * ((int)100));
			t_sample tap_152 = m_delay_6.read_step(mul_148);
			t_sample sub_153 = (tap_152 - mul_154);
			t_sample mul_149 = (sub_153 * latch_146);
			t_sample add_150 = (mul_149 + add_196);
			t_sample history_56_next_2729 = fixdenorm(mix_57);
			t_sample history_58_next_2730 = fixdenorm(mix_59);
			t_sample history_60_next_2731 = fixdenorm(mix_61);
			t_sample history_54_next_2732 = fixdenorm(mix_55);
			t_sample add_3877 = (add_49 + add_52);
			t_sample mix_3876 = (((int)0) + (min_38 * (add_3877 - ((int)0))));
			t_sample out1 = mix_3876;
			t_sample add_3879 = (add_50 + add_51);
			t_sample mix_3878 = (((int)0) + (min_38 * (add_3879 - ((int)0))));
			t_sample out2 = mix_3878;
			m_history_18 = history_78_next_112;
			m_history_1 = history_54_next_2732;
			m_history_2 = history_60_next_2731;
			m_history_3 = history_58_next_2730;
			m_history_4 = history_56_next_2729;
			m_delay_8.write(add_186);
			m_delay_7.write(add_161);
			m_delay_6.write(add_150);
			m_history_5 = history_181_next_191;
			m_delay_9.write(add_172);
			m_delay_10.write(sub_153);
			m_delay_11.write(sub_164);
			m_delay_12.write(sub_175);
			m_delay_13.write(sub_189);
			m_history_17 = history_91_next_113;
			m_history_16 = history_84_next_114;
			m_history_15 = history_100_next_115;
			m_history_14 = history_107_next_116;
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_11.step();
			m_delay_12.step();
			m_delay_13.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 8;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 0; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2", "in3", "dry/wet", "rotate", "decay", "damping", "fluctuate" };
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
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		
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
	self->__commonstate.params = 0;
	self->__commonstate.numparams = 0;
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	
	delete self;
}


} // creepy_2dpizz_5b1_5d::
