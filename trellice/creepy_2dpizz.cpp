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
	Change __m_change_41;
	DCBlock __m_dcblock_55;
	DCBlock __m_dcblock_56;
	DCBlock __m_dcblock_54;
	DCBlock __m_dcblock_57;
	Delay m_delay_6;
	Delay m_delay_10;
	Delay m_delay_11;
	Delay m_delay_12;
	Delay m_delay_9;
	Delay m_delay_8;
	Delay m_delay_7;
	Delay m_delay_21;
	Delay m_delay_22;
	Delay m_delay_13;
	Phasor __m_phasor_48;
	Phasor __m_phasor_49;
	int __exception;
	int vectorsize;
	t_sample m_cv1_pitch_39;
	t_sample m_cv6_decay_40;
	t_sample __m_latch_58;
	t_sample m_knob_38;
	t_sample m_gate_36;
	t_sample m_cv3_rotate_37;
	t_sample m_cv2_fluctuate_35;
	t_sample m_cv5_port_34;
	t_sample __m_slide_42;
	t_sample __m_latch_63;
	t_sample __m_latch_60;
	t_sample __m_latch_59;
	t_sample __m_slide_45;
	t_sample __m_latch_61;
	t_sample __m_latch_62;
	t_sample samples_to_seconds;
	t_sample m_cv8_decay_33;
	t_sample m_history_28;
	t_sample m_history_31;
	t_sample m_history_14;
	t_sample m_history_5;
	t_sample m_history_15;
	t_sample m_history_16;
	t_sample m_history_17;
	t_sample m_history_4;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample m_cv7_dampen_32;
	t_sample m_history_18;
	t_sample m_x_20;
	t_sample __m_latch_64;
	t_sample m_history_29;
	t_sample m_history_30;
	t_sample m_y_19;
	t_sample m_history_27;
	t_sample m_history_25;
	t_sample m_history_26;
	t_sample m_history_23;
	t_sample m_history_24;
	t_sample __m_latch_65;
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
		m_y_19 = ((int)0);
		m_x_20 = ((int)0);
		m_delay_21.reset("m_delay_21", ((int)44100));
		m_delay_22.reset("m_delay_22", ((int)44100));
		m_history_23 = ((int)0);
		m_history_24 = ((int)0);
		m_history_25 = ((int)0);
		m_history_26 = ((int)0);
		m_history_27 = ((int)0);
		m_history_28 = ((int)0);
		m_history_29 = ((int)0);
		m_history_30 = ((int)0);
		m_history_31 = ((int)0);
		m_cv7_dampen_32 = ((t_sample)0.25);
		m_cv8_decay_33 = 100;
		m_cv5_port_34 = ((int)0);
		m_cv2_fluctuate_35 = 0.1;
		m_gate_36 = ((int)0);
		m_cv3_rotate_37 = ((int)0);
		m_knob_38 = 0.5;
		m_cv1_pitch_39 = ((int)0);
		m_cv6_decay_40 = ((t_sample)0.97);
		__m_change_41.reset(0);
		__m_slide_42 = 0;
		__m_slide_45 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_48.reset(0);
		__m_phasor_49.reset(0);
		__m_dcblock_54.reset();
		__m_dcblock_55.reset();
		__m_dcblock_56.reset();
		__m_dcblock_57.reset();
		__m_latch_58 = 0;
		__m_latch_59 = 0;
		__m_latch_60 = 0;
		__m_latch_61 = 0;
		__m_latch_62 = 0;
		__m_latch_63 = 0;
		__m_latch_64 = 0;
		__m_latch_65 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		const t_sample * __in3 = __ins[2];
		const t_sample * __in4 = __ins[3];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__in3 == 0) || (__in4 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int int_234 = int(m_gate_36);
		t_sample rdiv_783 = safediv(samplerate, m_cv1_pitch_39);
		t_sample rdiv_784 = safediv(samplerate, m_cv1_pitch_39);
		t_sample clamp_53 = ((m_knob_38 <= ((int)0)) ? ((int)0) : ((m_knob_38 >= ((int)1)) ? ((int)1) : m_knob_38));
		t_sample min_71 = ((m_cv8_decay_33 < ((int)0)) ? ((int)0) : m_cv8_decay_33);
		t_sample t_66 = exp(safediv(-6.9077552789821, min_71));
		samples_to_seconds = (1 / samplerate);
		t_sample mul_125 = (m_cv3_rotate_37 * ((t_sample)3.1415926535898));
		t_sample div_81 = (m_cv2_fluctuate_35 * ((t_sample)0.00033333333333333));
		t_sample history_78_next_112 = fixdenorm(((int)1));
		t_sample history_181_next_191 = fixdenorm(((int)1));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			const t_sample in3 = (*(__in3++));
			const t_sample in4 = (*(__in4++));
			t_sample min_839 = ((in4 < ((int)0)) ? ((int)0) : in4);
			int change_235 = __m_change_41(int_234);
			int eqp_236 = ((int_234 == change_235) ? int_234 : 0);
			t_sample mix_5363 = (m_history_31 + (((t_sample)0.80901699437495) * (m_cv5_port_34 - m_history_31)));
			t_sample mix_250 = mix_5363;
			t_sample mix_5364 = (m_history_30 + (((t_sample)0.80901699437495) * (mix_250 - m_history_30)));
			t_sample mix_248 = mix_5364;
			t_sample mix_5365 = (m_history_29 + (((t_sample)0.80901699437495) * (mix_248 - m_history_29)));
			t_sample mix_246 = mix_5365;
			t_sample gen_1516 = mix_246;
			t_sample history_251_next_253 = fixdenorm(mix_250);
			t_sample history_249_next_254 = fixdenorm(mix_248);
			t_sample history_247_next_255 = fixdenorm(mix_246);
			t_sample mix_5366 = (m_history_28 + (((t_sample)0.80901699437495) * (m_cv6_decay_40 - m_history_28)));
			t_sample mix_5243 = mix_5366;
			t_sample mix_5367 = (m_history_27 + (((t_sample)0.80901699437495) * (mix_5243 - m_history_27)));
			t_sample mix_5247 = mix_5367;
			t_sample mix_5368 = (m_history_26 + (((t_sample)0.80901699437495) * (mix_5247 - m_history_26)));
			t_sample mix_5246 = mix_5368;
			t_sample gen_1615 = mix_5246;
			t_sample history_251_next_5245 = fixdenorm(mix_5243);
			t_sample history_249_next_5244 = fixdenorm(mix_5247);
			t_sample history_247_next_5248 = fixdenorm(mix_5246);
			t_sample mix_5369 = (m_history_25 + (((t_sample)0.80901699437495) * (m_cv7_dampen_32 - m_history_25)));
			t_sample mix_5261 = mix_5369;
			t_sample mix_5370 = (m_history_24 + (((t_sample)0.80901699437495) * (mix_5261 - m_history_24)));
			t_sample mix_5255 = mix_5370;
			t_sample mix_5371 = (m_history_23 + (((t_sample)0.80901699437495) * (mix_5255 - m_history_23)));
			t_sample mix_5257 = mix_5371;
			t_sample gen_1739 = mix_5257;
			t_sample history_251_next_5256 = fixdenorm(mix_5261);
			t_sample history_249_next_5260 = fixdenorm(mix_5255);
			t_sample history_247_next_5258 = fixdenorm(mix_5257);
			t_sample clamp_1095 = ((gen_1739 <= ((int)0)) ? ((int)0) : ((gen_1739 >= ((int)1)) ? ((int)1) : gen_1739));
			t_sample clamp_826 = ((gen_1615 <= ((int)0)) ? ((int)0) : ((gen_1615 >= ((int)1)) ? ((int)1) : gen_1615));
			t_sample clamp_780 = ((gen_1516 <= ((int)0)) ? ((int)0) : ((gen_1516 >= ((int)2)) ? ((int)2) : gen_1516));
			t_sample mul_779 = (clamp_780 * samplerate);
			t_sample iup_43 = (1 / maximum(1, abs(mul_779)));
			t_sample idown_44 = (1 / maximum(1, abs(mul_779)));
			__m_slide_42 = fixdenorm((__m_slide_42 + (((rdiv_783 > __m_slide_42) ? iup_43 : idown_44) * (rdiv_783 - __m_slide_42))));
			t_sample slide_781 = __m_slide_42;
			t_sample sub_785 = (slide_781 - ((int)1));
			t_sample tap_801 = m_delay_22.read_linear(sub_785);
			t_sample iup_46 = (1 / maximum(1, abs(mul_779)));
			t_sample idown_47 = (1 / maximum(1, abs(mul_779)));
			__m_slide_45 = fixdenorm((__m_slide_45 + (((rdiv_784 > __m_slide_45) ? iup_46 : idown_47) * (rdiv_784 - __m_slide_45))));
			t_sample slide_782 = __m_slide_45;
			t_sample sub_786 = (slide_782 - ((int)1));
			t_sample tap_798 = m_delay_21.read_linear(sub_786);
			t_sample cartopol_5372 = sqrt(((tap_801 * tap_801) + (tap_798 * tap_798)));
			t_sample cartopol_5373 = atan2(tap_798, tap_801);
			t_sample radius_795 = cartopol_5372;
			t_sample angle_796 = cartopol_5373;
			t_sample add_792 = (angle_796 + ((int)0));
			t_sample mul_845 = (radius_795 * clamp_826);
			t_sample mul_787 = (mul_845 * ((int)2));
			t_sample sin_793 = sin(mul_787);
			t_sample poltocar_5374 = (sin_793 * cos(add_792));
			t_sample poltocar_5375 = (sin_793 * sin(add_792));
			t_sample x_790 = poltocar_5374;
			t_sample y_791 = poltocar_5375;
			t_sample mix_5376 = (x_790 + (clamp_1095 * (m_x_20 - x_790)));
			t_sample mix_799 = mix_5376;
			t_sample gen_1100 = mix_799;
			t_sample mix_5377 = (y_791 + (clamp_1095 * (m_y_19 - y_791)));
			t_sample mix_788 = mix_5377;
			t_sample gen_1101 = mix_788;
			t_sample x_next_1098 = fixdenorm(mix_799);
			t_sample y_next_1099 = fixdenorm(mix_788);
			t_sample phasor_135 = __m_phasor_48(m_cv3_rotate_37, samples_to_seconds);
			t_sample mul_134 = (phasor_135 * ((t_sample)6.2831853071796));
			t_sample cos_133 = cos(mul_134);
			t_sample gen_136 = cos_133;
			t_sample mul_131 = (cos_133 * (-1));
			t_sample gen_139 = mul_131;
			t_sample sin_132 = sin(mul_134);
			t_sample gen_138 = sin_132;
			t_sample gen_137 = sin_132;
			t_sample phasor_126 = __m_phasor_49(mul_125, samples_to_seconds);
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
			t_sample mul_79 = (sign_93 * div_81);
			t_sample add_90 = (m_history_17 + mul_79);
			t_sample clamp_89 = ((add_90 <= ((int)0)) ? ((int)0) : ((add_90 >= ((int)1)) ? ((int)1) : add_90));
			t_sample mul_73 = (clamp_89 * ((int)3000));
			t_sample gen_121 = mul_73;
			t_sample rsub_95 = (((int)3000) - mul_73);
			t_sample gen_122 = rsub_95;
			t_sample choice_50 = int(add_76);
			t_sample selector_92 = ((choice_50 >= 2) ? clamp_89 : ((choice_50 >= 1) ? noise_94 : 0));
			t_sample mul_80 = (sign_86 * div_81);
			t_sample add_83 = (m_history_16 + mul_80);
			t_sample clamp_82 = ((add_83 <= ((int)0)) ? ((int)0) : ((add_83 >= ((int)1)) ? ((int)1) : add_83));
			t_sample mul_72 = (clamp_82 * ((int)3000));
			t_sample gen_123 = mul_72;
			t_sample rsub_88 = (((int)3000) - mul_72);
			t_sample gen_124 = rsub_88;
			t_sample choice_51 = int(add_76);
			t_sample selector_85 = ((choice_51 >= 2) ? clamp_82 : ((choice_51 >= 1) ? noise_87 : 0));
			t_sample mul_97 = (sign_102 * div_81);
			t_sample add_99 = (m_history_15 + mul_97);
			t_sample clamp_98 = ((add_99 <= ((int)0)) ? ((int)0) : ((add_99 >= ((int)1)) ? ((int)1) : add_99));
			t_sample mul_74 = (clamp_98 * ((int)3000));
			t_sample gen_119 = mul_74;
			t_sample rsub_104 = (((int)3000) - mul_74);
			t_sample gen_120 = rsub_104;
			t_sample choice_52 = int(add_76);
			t_sample selector_101 = ((choice_52 >= 2) ? clamp_98 : ((choice_52 >= 1) ? noise_103 : 0));
			t_sample mul_96 = (sign_109 * div_81);
			t_sample add_106 = (m_history_14 + mul_96);
			t_sample clamp_105 = ((add_106 <= ((int)0)) ? ((int)0) : ((add_106 >= ((int)1)) ? ((int)1) : add_106));
			t_sample mul_75 = (clamp_105 * ((int)3000));
			t_sample gen_117 = mul_75;
			t_sample rsub_111 = (((int)3000) - mul_75);
			t_sample gen_118 = rsub_111;
			t_sample choice_53 = int(add_76);
			t_sample selector_108 = ((choice_53 >= 2) ? clamp_105 : ((choice_53 >= 1) ? noise_110 : 0));
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
			t_sample mix_5378 = (mul_70 + (clamp_53 * (m_history_4 - mul_70)));
			t_sample mix_57 = mix_5378;
			t_sample dcblock_65 = __m_dcblock_54(mix_57);
			t_sample mul_45 = (dcblock_65 * safediv(1, sqrt(2)));
			t_sample mul_214 = (tap_213 * gen_139);
			t_sample add_216 = (mul_219 + mul_214);
			t_sample mul_69 = (add_216 * t_66);
			t_sample mix_5379 = (mul_69 + (clamp_53 * (m_history_3 - mul_69)));
			t_sample mix_59 = mix_5379;
			t_sample dcblock_64 = __m_dcblock_55(mix_59);
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
			t_sample mix_5380 = (mul_68 + (clamp_53 * (m_history_2 - mul_68)));
			t_sample mix_61 = mix_5380;
			t_sample dcblock_63 = __m_dcblock_56(mix_61);
			t_sample mul_47 = (dcblock_63 * safediv(1, sqrt(2)));
			t_sample mul_202 = (tap_201 * gen_143);
			t_sample add_204 = (mul_207 + mul_202);
			t_sample mul_67 = (add_204 * t_66);
			t_sample mix_5381 = (mul_67 + (clamp_53 * (m_history_1 - mul_67)));
			t_sample mix_55 = mix_5381;
			t_sample dcblock_62 = __m_dcblock_57(mix_55);
			t_sample mul_48 = (dcblock_62 * safediv(1, sqrt(2)));
			t_sample add_41 = (mul_48 + mul_47);
			t_sample add_49 = (add_41 + ((int)0));
			t_sample sub_42 = (mul_48 - mul_47);
			t_sample add_50 = (sub_42 + ((int)0));
			t_sample add_223 = (add_49 + gen_1100);
			t_sample add_198 = (add_50 + gen_1101);
			t_sample add_197 = (add_51 + gen_1100);
			t_sample add_196 = (add_52 + gen_1101);
			t_sample noise_169 = noise();
			int not_179 = (!m_history_5);
			__m_latch_58 = ((not_179 != 0) ? noise_169 : __m_latch_58);
			t_sample latch_168 = __m_latch_58;
			t_sample mul_176 = (add_198 * latch_168);
			t_sample noise_183 = noise();
			__m_latch_59 = ((not_179 != 0) ? noise_183 : __m_latch_59);
			t_sample latch_182 = __m_latch_59;
			t_sample mul_190 = (add_223 * latch_182);
			t_sample noise_158 = noise();
			__m_latch_60 = ((not_179 != 0) ? noise_158 : __m_latch_60);
			t_sample latch_157 = __m_latch_60;
			t_sample mul_165 = (add_197 * latch_157);
			t_sample noise_147 = noise();
			__m_latch_61 = ((not_179 != 0) ? noise_147 : __m_latch_61);
			t_sample latch_146 = __m_latch_61;
			t_sample mul_154 = (add_196 * latch_146);
			t_sample noise_167 = noise();
			__m_latch_62 = ((not_179 != 0) ? noise_167 : __m_latch_62);
			t_sample latch_166 = __m_latch_62;
			t_sample mul_170 = (latch_166 * ((int)100));
			t_sample tap_174 = m_delay_9.read_step(mul_170);
			t_sample sub_175 = (tap_174 - mul_176);
			t_sample mul_171 = (sub_175 * latch_168);
			t_sample add_172 = (mul_171 + add_198);
			t_sample noise_178 = noise();
			__m_latch_63 = ((not_179 != 0) ? noise_178 : __m_latch_63);
			t_sample latch_177 = __m_latch_63;
			t_sample mul_184 = (latch_177 * ((int)100));
			t_sample tap_188 = m_delay_8.read_step(mul_184);
			t_sample sub_189 = (tap_188 - mul_190);
			t_sample mul_185 = (sub_189 * latch_182);
			t_sample add_186 = (mul_185 + add_223);
			t_sample noise_156 = noise();
			__m_latch_64 = ((not_179 != 0) ? noise_156 : __m_latch_64);
			t_sample latch_155 = __m_latch_64;
			t_sample mul_159 = (latch_155 * ((int)100));
			t_sample tap_163 = m_delay_7.read_step(mul_159);
			t_sample sub_164 = (tap_163 - mul_165);
			t_sample mul_160 = (sub_164 * latch_157);
			t_sample add_161 = (mul_160 + add_197);
			t_sample noise_145 = noise();
			__m_latch_65 = ((not_179 != 0) ? noise_145 : __m_latch_65);
			t_sample latch_144 = __m_latch_65;
			t_sample mul_148 = (latch_144 * ((int)100));
			t_sample tap_152 = m_delay_6.read_step(mul_148);
			t_sample sub_153 = (tap_152 - mul_154);
			t_sample mul_149 = (sub_153 * latch_146);
			t_sample add_150 = (mul_149 + add_196);
			t_sample history_56_next_224 = fixdenorm(mix_57);
			t_sample history_58_next_225 = fixdenorm(mix_59);
			t_sample history_60_next_226 = fixdenorm(mix_61);
			t_sample history_54_next_227 = fixdenorm(mix_55);
			t_sample add_5383 = (add_52 + add_49);
			t_sample mix_5382 = (gen_1100 + (min_839 * (add_5383 - gen_1100)));
			t_sample out1 = mix_5382;
			t_sample add_5385 = (add_51 + add_50);
			t_sample mix_5384 = (gen_1101 + (min_839 * (add_5385 - gen_1101)));
			t_sample out2 = mix_5384;
			m_history_31 = history_251_next_253;
			m_history_29 = history_247_next_255;
			m_history_30 = history_249_next_254;
			m_history_28 = history_251_next_5245;
			m_history_26 = history_247_next_5248;
			m_history_27 = history_249_next_5244;
			m_history_25 = history_251_next_5256;
			m_history_23 = history_247_next_5258;
			m_history_24 = history_249_next_5260;
			m_delay_22.write((m_x_20 + eqp_236));
			m_y_19 = y_next_1099;
			m_x_20 = x_next_1098;
			m_delay_21.write((eqp_236 + m_y_19));
			m_history_18 = history_78_next_112;
			m_history_1 = history_54_next_227;
			m_history_2 = history_60_next_226;
			m_history_3 = history_58_next_225;
			m_history_4 = history_56_next_224;
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
			m_delay_21.step();
			m_delay_22.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_cv7_dampen(t_param _value) {
		m_cv7_dampen_32 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv8_decay(t_param _value) {
		m_cv8_decay_33 = (_value < 0 ? 0 : (_value > 48000 ? 48000 : _value));
	};
	inline void set_cv5_port(t_param _value) {
		m_cv5_port_34 = (_value < 0 ? 0 : (_value > 2 ? 2 : _value));
	};
	inline void set_cv2_fluctuate(t_param _value) {
		m_cv2_fluctuate_35 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_gate1(t_param _value) {
		m_gate_36 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv3_rotate(t_param _value) {
		m_cv3_rotate_37 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5(t_param _value) {
		m_knob_38 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv1_pitch(t_param _value) {
		m_cv1_pitch_39 = (_value < 0 ? 0 : (_value > 127 ? 127 : _value));
	};
	inline void set_cv6_decay(t_param _value) {
		m_cv6_decay_40 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 4;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 9; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2", "in3", "dry/wet" };
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
		case 1: self->set_cv2_fluctuate(value); break;
		case 2: self->set_cv3_rotate(value); break;
		case 3: self->set_cv5_port(value); break;
		case 4: self->set_cv6_decay(value); break;
		case 5: self->set_cv7_dampen(value); break;
		case 6: self->set_cv8_decay(value); break;
		case 7: self->set_gate1(value); break;
		case 8: self->set_knob5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_cv1_pitch_39; break;
		case 1: *value = self->m_cv2_fluctuate_35; break;
		case 2: *value = self->m_cv3_rotate_37; break;
		case 3: *value = self->m_cv5_port_34; break;
		case 4: *value = self->m_cv6_decay_40; break;
		case 5: *value = self->m_cv7_dampen_32; break;
		case 6: *value = self->m_cv8_decay_33; break;
		case 7: *value = self->m_gate_36; break;
		case 8: *value = self->m_knob_38; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(9 * sizeof(ParamInfo));
	self->__commonstate.numparams = 9;
	// initialize parameter 0 ("m_cv1_pitch_39")
	pi = self->__commonstate.params + 0;
	pi->name = "cv1_pitch";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv1_pitch_39;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 127;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_cv2_fluctuate_35")
	pi = self->__commonstate.params + 1;
	pi->name = "cv2_fluctuate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv2_fluctuate_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_cv3_rotate_37")
	pi = self->__commonstate.params + 2;
	pi->name = "cv3_rotate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv3_rotate_37;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_cv5_port_34")
	pi = self->__commonstate.params + 3;
	pi->name = "cv5_port";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv5_port_34;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_cv6_decay_40")
	pi = self->__commonstate.params + 4;
	pi->name = "cv6_decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv6_decay_40;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_cv7_dampen_32")
	pi = self->__commonstate.params + 5;
	pi->name = "cv7_dampen";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv7_dampen_32;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_cv8_decay_33")
	pi = self->__commonstate.params + 6;
	pi->name = "cv8_decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv8_decay_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 48000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_gate_36")
	pi = self->__commonstate.params + 7;
	pi->name = "gate1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_36;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_knob_38")
	pi = self->__commonstate.params + 8;
	pi->name = "knob5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_38;
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
