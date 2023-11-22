#include "creepy_2dflute_5b1_5d.h"

namespace creepy_2dflute_5b1_5d {

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
	Phasor __m_phasor_23;
	Phasor __m_phasor_24;
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
		__m_phasor_23.reset(0);
		__m_phasor_24.reset(0);
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
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__in3 == 0) || (__in4 == 0) || (__in5 == 0) || (__in6 == 0) || (__in7 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample history_10864_next_10898 = fixdenorm(((int)1));
		samples_to_seconds = (1 / samplerate);
		t_sample history_10967_next_10977 = fixdenorm(((int)1));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			const t_sample in3 = (*(__in3++));
			const t_sample in4 = (*(__in4++));
			const t_sample in5 = (*(__in5++));
			const t_sample in6 = (*(__in6++));
			const t_sample in7 = (*(__in7++));
			t_sample min_12105 = ((in4 < ((int)0)) ? ((int)0) : in4);
			t_sample min_12442 = ((in5 < ((int)0)) ? ((int)0) : in5);
			t_sample min_12652 = ((in6 < ((int)0)) ? ((int)0) : in6);
			t_sample clamp_12651 = ((in7 <= ((int)0)) ? ((int)0) : ((in7 >= ((int)1)) ? ((int)1) : in7));
			t_sample clamp_12604 = ((clamp_12651 <= ((int)0)) ? ((int)0) : ((clamp_12651 >= ((int)1)) ? ((int)1) : clamp_12651));
			t_sample min_12557 = ((min_12652 < ((int)0)) ? ((int)0) : min_12652);
			t_sample t_10853 = exp(safediv(-6.9077552789821, min_12557));
			t_sample add_10862 = (m_history_18 + ((int)1));
			t_sample noise_10880 = noise();
			t_sample noise_10896 = noise();
			t_sample noise_10873 = noise();
			t_sample noise_10889 = noise();
			int sign_10879 = ((noise_10880 > 0) ? 1 : ((noise_10880 < 0) ? -1 : 0));
			int sign_10895 = ((noise_10896 > 0) ? 1 : ((noise_10896 < 0) ? -1 : 0));
			int sign_10872 = ((noise_10873 > 0) ? 1 : ((noise_10873 < 0) ? -1 : 0));
			int sign_10888 = ((noise_10889 > 0) ? 1 : ((noise_10889 < 0) ? -1 : 0));
			t_sample mul_10865 = (sign_10879 * ((t_sample)3.3333333333333e-05));
			t_sample add_10876 = (m_history_17 + mul_10865);
			t_sample clamp_10875 = ((add_10876 <= ((int)0)) ? ((int)0) : ((add_10876 >= ((int)1)) ? ((int)1) : add_10876));
			t_sample choice_19 = int(add_10862);
			t_sample selector_10878 = ((choice_19 >= 2) ? clamp_10875 : ((choice_19 >= 1) ? noise_10880 : 0));
			t_sample mul_10859 = (clamp_10875 * ((int)3000));
			t_sample gen_10907 = mul_10859;
			t_sample rsub_10881 = (((int)3000) - mul_10859);
			t_sample gen_10908 = rsub_10881;
			t_sample mul_10882 = (sign_10895 * ((t_sample)3.3333333333333e-05));
			t_sample add_10892 = (m_history_16 + mul_10882);
			t_sample clamp_10891 = ((add_10892 <= ((int)0)) ? ((int)0) : ((add_10892 >= ((int)1)) ? ((int)1) : add_10892));
			t_sample mul_10861 = (clamp_10891 * ((int)3000));
			t_sample gen_10903 = mul_10861;
			t_sample rsub_10897 = (((int)3000) - mul_10861);
			t_sample gen_10904 = rsub_10897;
			t_sample choice_20 = int(add_10862);
			t_sample selector_10894 = ((choice_20 >= 2) ? clamp_10891 : ((choice_20 >= 1) ? noise_10896 : 0));
			t_sample mul_10866 = (sign_10872 * ((t_sample)3.3333333333333e-05));
			t_sample add_10869 = (m_history_15 + mul_10866);
			t_sample clamp_10868 = ((add_10869 <= ((int)0)) ? ((int)0) : ((add_10869 >= ((int)1)) ? ((int)1) : add_10869));
			t_sample mul_10858 = (clamp_10868 * ((int)3000));
			t_sample gen_10909 = mul_10858;
			t_sample rsub_10874 = (((int)3000) - mul_10858);
			t_sample gen_10910 = rsub_10874;
			t_sample choice_21 = int(add_10862);
			t_sample selector_10871 = ((choice_21 >= 2) ? clamp_10868 : ((choice_21 >= 1) ? noise_10873 : 0));
			t_sample mul_10883 = (sign_10888 * ((t_sample)3.3333333333333e-05));
			t_sample add_10885 = (m_history_14 + mul_10883);
			t_sample clamp_10884 = ((add_10885 <= ((int)0)) ? ((int)0) : ((add_10885 >= ((int)1)) ? ((int)1) : add_10885));
			t_sample mul_10860 = (clamp_10884 * ((int)3000));
			t_sample gen_10905 = mul_10860;
			t_sample rsub_10890 = (((int)3000) - mul_10860);
			t_sample gen_10906 = rsub_10890;
			t_sample choice_22 = int(add_10862);
			t_sample selector_10887 = ((choice_22 >= 2) ? clamp_10884 : ((choice_22 >= 1) ? noise_10889 : 0));
			t_sample history_10877_next_10899 = fixdenorm(selector_10878);
			t_sample history_10893_next_10900 = fixdenorm(selector_10894);
			t_sample history_10870_next_10901 = fixdenorm(selector_10871);
			t_sample history_10886_next_10902 = fixdenorm(selector_10887);
			t_sample tap_11007 = m_delay_13.read_step(gen_10903);
			t_sample tap_11008 = m_delay_13.read_step(gen_10904);
			t_sample tap_10998 = m_delay_12.read_step(gen_10905);
			t_sample tap_10999 = m_delay_12.read_step(gen_10906);
			t_sample tap_10995 = m_delay_11.read_step(gen_10907);
			t_sample tap_10996 = m_delay_11.read_step(gen_10908);
			t_sample tap_10986 = m_delay_10.read_step(gen_10909);
			t_sample tap_10987 = m_delay_10.read_step(gen_10910);
			t_sample phasor_10921 = __m_phasor_23(min_12442, samples_to_seconds);
			t_sample mul_10920 = (phasor_10921 * ((t_sample)6.2831853071796));
			t_sample cos_10919 = cos(mul_10920);
			t_sample gen_10922 = cos_10919;
			t_sample mul_10917 = (cos_10919 * (-1));
			t_sample gen_10925 = mul_10917;
			t_sample sin_10918 = sin(mul_10920);
			t_sample gen_10924 = sin_10918;
			t_sample gen_10923 = sin_10918;
			t_sample mul_10911 = (min_12442 * ((t_sample)3.1415926535898));
			t_sample phasor_10912 = __m_phasor_24(mul_10911, samples_to_seconds);
			t_sample mul_10916 = (phasor_10912 * ((t_sample)6.2831853071796));
			t_sample sin_10914 = sin(mul_10916);
			t_sample gen_10927 = sin_10914;
			t_sample gen_10928 = sin_10914;
			t_sample cos_10915 = cos(mul_10916);
			t_sample gen_10926 = cos_10915;
			t_sample mul_10913 = (cos_10915 * (-1));
			t_sample gen_10929 = mul_10913;
			t_sample mul_11005 = (tap_11008 * gen_10923);
			t_sample mul_11000 = (tap_10999 * gen_10925);
			t_sample add_11002 = (mul_11005 + mul_11000);
			t_sample mul_10856 = (add_11002 * t_10853);
			t_sample mix_12838 = (mul_10856 + (clamp_12604 * (m_history_4 - mul_10856)));
			t_sample mix_10846 = mix_12838;
			t_sample dcblock_10851 = __m_dcblock_25(mix_10846);
			t_sample mul_10834 = (dcblock_10851 * safediv(1, sqrt(2)));
			t_sample mul_10992 = (tap_10995 * gen_10926);
			t_sample mul_10989 = (tap_10986 * gen_10928);
			t_sample add_10991 = (mul_10992 + mul_10989);
			t_sample mul_10855 = (add_10991 * t_10853);
			t_sample mix_12839 = (mul_10855 + (clamp_12604 * (m_history_3 - mul_10855)));
			t_sample mix_10848 = mix_12839;
			t_sample dcblock_10850 = __m_dcblock_26(mix_10848);
			t_sample mul_10835 = (dcblock_10850 * safediv(1, sqrt(2)));
			t_sample mul_10993 = (tap_10996 * gen_10927);
			t_sample mul_10988 = (tap_10987 * gen_10929);
			t_sample add_10990 = (mul_10993 + mul_10988);
			t_sample mul_10854 = (add_10990 * t_10853);
			t_sample mix_12840 = (mul_10854 + (clamp_12604 * (m_history_2 - mul_10854)));
			t_sample mix_10842 = mix_12840;
			t_sample dcblock_10849 = __m_dcblock_27(mix_10842);
			t_sample mul_10836 = (dcblock_10849 * safediv(1, sqrt(2)));
			t_sample add_10829 = (mul_10836 + mul_10835);
			t_sample add_10837 = (add_10829 + ((int)0));
			t_sample sub_10830 = (mul_10836 - mul_10835);
			t_sample add_10838 = (sub_10830 + ((int)0));
			t_sample mul_11004 = (tap_11007 * gen_10922);
			t_sample mul_11001 = (tap_10998 * gen_10924);
			t_sample add_11003 = (mul_11004 + mul_11001);
			t_sample mul_10857 = (add_11003 * t_10853);
			t_sample mix_12841 = (mul_10857 + (clamp_12604 * (m_history_1 - mul_10857)));
			t_sample mix_10844 = mix_12841;
			t_sample dcblock_10852 = __m_dcblock_28(mix_10844);
			t_sample mul_10833 = (dcblock_10852 * safediv(1, sqrt(2)));
			t_sample sub_10831 = (mul_10833 - mul_10834);
			t_sample add_10839 = (sub_10831 + ((int)0));
			t_sample add_10832 = (mul_10833 + mul_10834);
			t_sample add_10840 = (add_10832 + ((int)0));
			t_sample add_11009 = (add_10837 + ((int)0));
			t_sample add_10984 = (add_10838 + ((int)0));
			t_sample add_10983 = (add_10839 + ((int)0));
			t_sample add_10982 = (add_10840 + ((int)0));
			t_sample noise_10955 = noise();
			int not_10965 = (!m_history_5);
			__m_latch_29 = ((not_10965 != 0) ? noise_10955 : __m_latch_29);
			t_sample latch_10954 = __m_latch_29;
			t_sample mul_10962 = (add_10984 * latch_10954);
			t_sample noise_10969 = noise();
			__m_latch_30 = ((not_10965 != 0) ? noise_10969 : __m_latch_30);
			t_sample latch_10968 = __m_latch_30;
			t_sample mul_10976 = (add_11009 * latch_10968);
			t_sample noise_10944 = noise();
			__m_latch_31 = ((not_10965 != 0) ? noise_10944 : __m_latch_31);
			t_sample latch_10943 = __m_latch_31;
			t_sample mul_10951 = (add_10983 * latch_10943);
			t_sample noise_10933 = noise();
			__m_latch_32 = ((not_10965 != 0) ? noise_10933 : __m_latch_32);
			t_sample latch_10932 = __m_latch_32;
			t_sample mul_10940 = (add_10982 * latch_10932);
			t_sample noise_10953 = noise();
			__m_latch_33 = ((not_10965 != 0) ? noise_10953 : __m_latch_33);
			t_sample latch_10952 = __m_latch_33;
			t_sample mul_10956 = (latch_10952 * ((int)100));
			t_sample tap_10960 = m_delay_9.read_step(mul_10956);
			t_sample sub_10961 = (tap_10960 - mul_10962);
			t_sample mul_10957 = (sub_10961 * latch_10954);
			t_sample add_10958 = (mul_10957 + add_10984);
			t_sample noise_10964 = noise();
			__m_latch_34 = ((not_10965 != 0) ? noise_10964 : __m_latch_34);
			t_sample latch_10963 = __m_latch_34;
			t_sample mul_10970 = (latch_10963 * ((int)100));
			t_sample tap_10974 = m_delay_8.read_step(mul_10970);
			t_sample sub_10975 = (tap_10974 - mul_10976);
			t_sample mul_10971 = (sub_10975 * latch_10968);
			t_sample add_10972 = (mul_10971 + add_11009);
			t_sample noise_10942 = noise();
			__m_latch_35 = ((not_10965 != 0) ? noise_10942 : __m_latch_35);
			t_sample latch_10941 = __m_latch_35;
			t_sample mul_10945 = (latch_10941 * ((int)100));
			t_sample tap_10949 = m_delay_7.read_step(mul_10945);
			t_sample sub_10950 = (tap_10949 - mul_10951);
			t_sample mul_10946 = (sub_10950 * latch_10943);
			t_sample add_10947 = (mul_10946 + add_10983);
			t_sample noise_10931 = noise();
			__m_latch_36 = ((not_10965 != 0) ? noise_10931 : __m_latch_36);
			t_sample latch_10930 = __m_latch_36;
			t_sample mul_10934 = (latch_10930 * ((int)100));
			t_sample tap_10938 = m_delay_6.read_step(mul_10934);
			t_sample sub_10939 = (tap_10938 - mul_10940);
			t_sample mul_10935 = (sub_10939 * latch_10932);
			t_sample add_10936 = (mul_10935 + add_10982);
			t_sample history_10845_next_12609 = fixdenorm(mix_10846);
			t_sample history_10847_next_12610 = fixdenorm(mix_10848);
			t_sample history_10841_next_12611 = fixdenorm(mix_10842);
			t_sample history_10843_next_12612 = fixdenorm(mix_10844);
			t_sample add_12843 = (add_10837 + add_10840);
			t_sample mix_12842 = (((int)0) + (min_12105 * (add_12843 - ((int)0))));
			t_sample out1 = mix_12842;
			t_sample add_12845 = (add_10838 + add_10839);
			t_sample mix_12844 = (((int)0) + (min_12105 * (add_12845 - ((int)0))));
			t_sample out2 = mix_12844;
			m_history_18 = history_10864_next_10898;
			m_history_1 = history_10843_next_12612;
			m_history_2 = history_10841_next_12611;
			m_history_3 = history_10847_next_12610;
			m_history_4 = history_10845_next_12609;
			m_delay_8.write(add_10972);
			m_delay_7.write(add_10947);
			m_delay_6.write(add_10936);
			m_history_5 = history_10967_next_10977;
			m_delay_9.write(add_10958);
			m_delay_10.write(sub_10939);
			m_delay_11.write(sub_10950);
			m_delay_12.write(sub_10961);
			m_delay_13.write(sub_10975);
			m_history_17 = history_10877_next_10899;
			m_history_16 = history_10893_next_10900;
			m_history_15 = history_10870_next_10901;
			m_history_14 = history_10886_next_10902;
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

int gen_kernel_numins = 7;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 0; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2", "in3", "dry/wet", "rotate", "decay", "damping" };
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


} // creepy_2dflute_5b1_5d::
