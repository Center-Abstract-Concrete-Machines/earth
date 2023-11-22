#include "pulsar_2ddemo.h"

namespace pulsar_2ddemo {

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
	Change __m_change_28;
	DCBlock __m_dcblock_58;
	DCBlock __m_dcblock_27;
	DCBlock __m_dcblock_49;
	PlusEquals __m_pluseq_34;
	int __exception;
	int vectorsize;
	t_sample __m_latch_42;
	t_sample __m_latch_41;
	t_sample m_history_4;
	t_sample __m_latch_43;
	t_sample __m_latch_44;
	t_sample __m_carry_38;
	t_sample __m_latch_35;
	t_sample __m_count_36;
	t_sample __m_carry_31;
	t_sample samplerate;
	t_sample __m_latch_45;
	t_sample __m_latch_46;
	t_sample __m_latch_47;
	t_sample __m_latch_54;
	t_sample __m_latch_55;
	t_sample __m_latch_56;
	t_sample __m_count_29;
	t_sample __m_latch_53;
	t_sample __m_latch_51;
	t_sample __m_latch_52;
	t_sample __m_latch_48;
	t_sample __m_latch_50;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample m_history_26;
	t_sample m_history_11;
	t_sample m_history_10;
	t_sample m_history_12;
	t_sample m_history_13;
	t_sample m_history_14;
	t_sample m_history_9;
	t_sample m_history_7;
	t_sample m_history_8;
	t_sample m_history_5;
	t_sample m_history_6;
	t_sample m_history_2;
	t_sample m_history_15;
	t_sample m_history_17;
	t_sample m_cv_23;
	t_sample m_history_24;
	t_sample __m_latch_57;
	t_sample m_history_16;
	t_sample m_cv_22;
	t_sample m_history_20;
	t_sample m_cv_21;
	t_sample m_history_18;
	t_sample m_history_19;
	t_sample m_history_25;
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
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_history_20 = ((int)0);
		m_cv_21 = ((int)0);
		m_cv_22 = ((int)10);
		m_cv_23 = ((t_sample)0.5);
		m_history_24 = ((int)0);
		m_history_25 = ((int)0);
		m_history_26 = ((int)0);
		__m_dcblock_27.reset();
		__m_change_28.reset(0);
		__m_count_29 = 0;
		__m_carry_31 = 0;
		__m_pluseq_34.reset(0);
		__m_latch_35 = 480;
		__m_count_36 = 0;
		__m_carry_38 = 0;
		__m_latch_41 = 1;
		__m_latch_42 = 1;
		__m_latch_43 = 1;
		__m_latch_44 = 1;
		__m_latch_45 = 1;
		__m_latch_46 = 1;
		__m_latch_47 = 1;
		__m_latch_48 = 1;
		__m_dcblock_49.reset();
		__m_latch_50 = 1;
		__m_latch_51 = 1;
		__m_latch_52 = 1;
		__m_latch_53 = 1;
		__m_latch_54 = 1;
		__m_latch_55 = 1;
		__m_latch_56 = 1;
		__m_latch_57 = 1;
		__m_dcblock_58.reset();
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
		t_sample * __out5 = __outs[4];
		t_sample * __out6 = __outs[5];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample mix_6528 = (m_history_26 + (((t_sample)0.0042742627044161) * (m_cv_23 - m_history_26)));
			t_sample mix_5795 = mix_6528;
			t_sample mix_6529 = (m_history_25 + (((t_sample)0.0042742627044161) * (mix_5795 - m_history_25)));
			t_sample mix_5793 = mix_6529;
			t_sample mix_6530 = (m_history_24 + (((t_sample)0.0042742627044161) * (mix_5793 - m_history_24)));
			t_sample mix_5791 = mix_6530;
			t_sample gen_5833 = mix_5791;
			t_sample history_5796_next_5798 = fixdenorm(mix_5795);
			t_sample history_5794_next_5799 = fixdenorm(mix_5793);
			t_sample history_5792_next_5800 = fixdenorm(mix_5791);
			t_sample dcblock_5832 = __m_dcblock_27(in1);
			int gt_5831 = (dcblock_5832 > ((int)0));
			int change_5838 = __m_change_28(gt_5831);
			int gt_5824 = (change_5838 > ((int)0));
			__m_count_29 = (((int)0) ? 0 : (fixdenorm(__m_count_29 + gt_5824)));
			int carry_30 = 0;
			if ((((int)0) != 0)) {
				__m_count_29 = 0;
				__m_carry_31 = 0;
				
			} else if (((((int)4) > 0) && (__m_count_29 >= ((int)4)))) {
				int wraps_32 = (__m_count_29 / ((int)4));
				__m_carry_31 = (__m_carry_31 + wraps_32);
				__m_count_29 = (__m_count_29 - (wraps_32 * ((int)4)));
				carry_30 = 1;
				
			};
			int counter_5819 = __m_count_29;
			int counter_5820 = carry_30;
			int counter_5821 = __m_carry_31;
			int add_5814 = (counter_5819 + ((int)1));
			t_sample div_5802 = (add_5814 * ((t_sample)0.25));
			t_sample out5 = div_5802;
			int choice_33 = add_5814;
			int gate_5815 = (((choice_33 >= 1) && (choice_33 < 2)) ? gt_5824 : 0);
			int gate_5816 = (((choice_33 >= 2) && (choice_33 < 3)) ? gt_5824 : 0);
			int gate_5817 = (((choice_33 >= 3) && (choice_33 < 4)) ? gt_5824 : 0);
			int gate_5818 = ((choice_33 >= 4) ? gt_5824 : 0);
			int plusequals_5828 = __m_pluseq_34.pre(((int)1), gt_5824, 0);
			__m_latch_35 = ((gt_5824 != 0) ? m_history_20 : __m_latch_35);
			t_sample latch_5826 = __m_latch_35;
			t_sample gen_5830 = latch_5826;
			t_sample history_5827_next_5829 = fixdenorm(plusequals_5828);
			t_sample mul_5823 = (gen_5830 * m_cv_21);
			int lt_5822 = (change_5838 < ((int)0));
			__m_count_36 = (((int)0) ? 0 : (fixdenorm(__m_count_36 + lt_5822)));
			int carry_37 = 0;
			if ((((int)0) != 0)) {
				__m_count_36 = 0;
				__m_carry_38 = 0;
				
			} else if (((((int)4) > 0) && (__m_count_36 >= ((int)4)))) {
				int wraps_39 = (__m_count_36 / ((int)4));
				__m_carry_38 = (__m_carry_38 + wraps_39);
				__m_count_36 = (__m_count_36 - (wraps_39 * ((int)4)));
				carry_37 = 1;
				
			};
			int counter_5809 = __m_count_36;
			int counter_5810 = carry_37;
			int counter_5811 = __m_carry_38;
			int add_5804 = (counter_5809 + ((int)1));
			t_sample div_5803 = (add_5804 * ((t_sample)0.25));
			t_sample out6 = div_5803;
			int choice_40 = add_5804;
			int gate_5805 = (((choice_40 >= 1) && (choice_40 < 2)) ? lt_5822 : 0);
			int gate_5806 = (((choice_40 >= 2) && (choice_40 < 3)) ? lt_5822 : 0);
			int gate_5807 = (((choice_40 >= 3) && (choice_40 < 4)) ? lt_5822 : 0);
			int gate_5808 = ((choice_40 >= 4) ? lt_5822 : 0);
			t_sample mix_6531 = (m_history_19 + (((t_sample)0.0042742627044161) * (m_cv_22 - m_history_19)));
			t_sample mix_6475 = mix_6531;
			t_sample mix_6532 = (m_history_18 + (((t_sample)0.0042742627044161) * (mix_6475 - m_history_18)));
			t_sample mix_6469 = mix_6532;
			t_sample mix_6533 = (m_history_17 + (((t_sample)0.0042742627044161) * (mix_6469 - m_history_17)));
			t_sample mix_6472 = mix_6533;
			t_sample gen_5801 = mix_6472;
			t_sample history_5796_next_6477 = fixdenorm(mix_6475);
			t_sample history_5794_next_6476 = fixdenorm(mix_6469);
			t_sample history_5792_next_6473 = fixdenorm(mix_6472);
			t_sample mul_5790 = (gen_5801 * gen_5801);
			t_sample mul_5789 = (mul_5790 * ((int)1000));
			t_sample max_5825 = ((mul_5789 < ((int)3)) ? ((int)3) : mul_5789);
			t_sample add_5527 = (m_history_16 + ((int)1));
			int gt_5532 = (m_history_15 > ((int)1));
			int mul_5537 = (gate_5808 * gt_5532);
			__m_latch_41 = ((mul_5537 != 0) ? mul_5823 : __m_latch_41);
			t_sample latch_5534 = __m_latch_41;
			t_sample noise_5526 = noise();
			t_sample abs_5525 = fabs(noise_5526);
			t_sample switch_5529 = (mul_5537 ? abs_5525 : add_5527);
			t_sample div_5540 = safediv(switch_5529, latch_5534);
			t_sample min_5533 = ((((int)1) < div_5540) ? ((int)1) : div_5540);
			t_sample sub_6537 = (min_5533 - ((int)0));
			t_sample scale_6534 = ((safepow((sub_6537 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample mul_5531 = (scale_6534 * ((t_sample)1.5707963267949));
			t_sample cos_5530 = cos(mul_5531);
			__m_latch_42 = ((mul_5537 != 0) ? max_5825 : __m_latch_42);
			t_sample latch_5538 = __m_latch_42;
			t_sample fract_5554 = fract(latch_5538);
			int int_5552 = int(latch_5538);
			t_sample mul_5551 = (scale_6534 * int_5552);
			int eq_5546 = (mul_5551 == ((int)0));
			t_sample sin_5549 = sin(mul_5551);
			t_sample div_5548 = safediv(sin_5549, mul_5551);
			t_sample switch_5547 = (eq_5546 ? ((int)1) : div_5548);
			int add_5553 = (int_5552 + ((int)1));
			t_sample mul_5550 = (scale_6534 * add_5553);
			int eq_5542 = (mul_5550 == ((int)0));
			t_sample sin_5545 = sin(mul_5550);
			t_sample div_5544 = safediv(sin_5545, mul_5550);
			t_sample switch_5543 = (eq_5542 ? ((int)1) : div_5544);
			t_sample mix_6538 = (switch_5547 + (fract_5554 * (switch_5543 - switch_5547)));
			t_sample mul_5535 = (cos_5530 * mix_6538);
			t_sample history_5528_next_5555 = fixdenorm(switch_5529);
			t_sample history_5536_next_5556 = fixdenorm(div_5540);
			t_sample add_5560 = (m_history_14 + ((int)1));
			int gt_5565 = (m_history_13 > ((int)1));
			int mul_5570 = (gate_5807 * gt_5565);
			__m_latch_43 = ((mul_5570 != 0) ? mul_5823 : __m_latch_43);
			t_sample latch_5567 = __m_latch_43;
			t_sample noise_5559 = noise();
			t_sample abs_5558 = fabs(noise_5559);
			t_sample switch_5562 = (mul_5570 ? abs_5558 : add_5560);
			t_sample div_5573 = safediv(switch_5562, latch_5567);
			t_sample min_5566 = ((((int)1) < div_5573) ? ((int)1) : div_5573);
			t_sample sub_6542 = (min_5566 - ((int)0));
			t_sample scale_6539 = ((safepow((sub_6542 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample mul_5564 = (scale_6539 * ((t_sample)1.5707963267949));
			t_sample cos_5563 = cos(mul_5564);
			__m_latch_44 = ((mul_5570 != 0) ? max_5825 : __m_latch_44);
			t_sample latch_5571 = __m_latch_44;
			t_sample fract_5587 = fract(latch_5571);
			int int_5585 = int(latch_5571);
			t_sample mul_5584 = (scale_6539 * int_5585);
			int eq_5579 = (mul_5584 == ((int)0));
			t_sample sin_5582 = sin(mul_5584);
			t_sample div_5581 = safediv(sin_5582, mul_5584);
			t_sample switch_5580 = (eq_5579 ? ((int)1) : div_5581);
			int add_5586 = (int_5585 + ((int)1));
			t_sample mul_5583 = (scale_6539 * add_5586);
			int eq_5575 = (mul_5583 == ((int)0));
			t_sample sin_5578 = sin(mul_5583);
			t_sample div_5577 = safediv(sin_5578, mul_5583);
			t_sample switch_5576 = (eq_5575 ? ((int)1) : div_5577);
			t_sample mix_6543 = (switch_5580 + (fract_5587 * (switch_5576 - switch_5580)));
			t_sample mul_5568 = (cos_5563 * mix_6543);
			t_sample history_5561_next_5588 = fixdenorm(switch_5562);
			t_sample history_5569_next_5589 = fixdenorm(div_5573);
			t_sample add_5593 = (m_history_12 + ((int)1));
			int gt_5598 = (m_history_11 > ((int)1));
			int mul_5603 = (gate_5806 * gt_5598);
			__m_latch_45 = ((mul_5603 != 0) ? mul_5823 : __m_latch_45);
			t_sample latch_5600 = __m_latch_45;
			t_sample noise_5592 = noise();
			t_sample abs_5591 = fabs(noise_5592);
			t_sample switch_5595 = (mul_5603 ? abs_5591 : add_5593);
			t_sample div_5606 = safediv(switch_5595, latch_5600);
			t_sample min_5599 = ((((int)1) < div_5606) ? ((int)1) : div_5606);
			t_sample sub_6547 = (min_5599 - ((int)0));
			t_sample scale_6544 = ((safepow((sub_6547 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample mul_5597 = (scale_6544 * ((t_sample)1.5707963267949));
			t_sample cos_5596 = cos(mul_5597);
			__m_latch_46 = ((mul_5603 != 0) ? max_5825 : __m_latch_46);
			t_sample latch_5604 = __m_latch_46;
			t_sample fract_5620 = fract(latch_5604);
			int int_5618 = int(latch_5604);
			t_sample mul_5617 = (scale_6544 * int_5618);
			int eq_5612 = (mul_5617 == ((int)0));
			t_sample sin_5615 = sin(mul_5617);
			t_sample div_5614 = safediv(sin_5615, mul_5617);
			t_sample switch_5613 = (eq_5612 ? ((int)1) : div_5614);
			int add_5619 = (int_5618 + ((int)1));
			t_sample mul_5616 = (scale_6544 * add_5619);
			int eq_5608 = (mul_5616 == ((int)0));
			t_sample sin_5611 = sin(mul_5616);
			t_sample div_5610 = safediv(sin_5611, mul_5616);
			t_sample switch_5609 = (eq_5608 ? ((int)1) : div_5610);
			t_sample mix_6548 = (switch_5613 + (fract_5620 * (switch_5609 - switch_5613)));
			t_sample mul_5601 = (cos_5596 * mix_6548);
			t_sample history_5594_next_5621 = fixdenorm(switch_5595);
			t_sample history_5602_next_5622 = fixdenorm(div_5606);
			t_sample add_5626 = (m_history_10 + ((int)1));
			int gt_5631 = (m_history_9 > ((int)1));
			int mul_5636 = (gate_5805 * gt_5631);
			t_sample noise_5625 = noise();
			t_sample abs_5624 = fabs(noise_5625);
			t_sample switch_5628 = (mul_5636 ? abs_5624 : add_5626);
			__m_latch_47 = ((mul_5636 != 0) ? mul_5823 : __m_latch_47);
			t_sample latch_5633 = __m_latch_47;
			t_sample div_5639 = safediv(switch_5628, latch_5633);
			t_sample min_5632 = ((((int)1) < div_5639) ? ((int)1) : div_5639);
			t_sample sub_6552 = (min_5632 - ((int)0));
			t_sample scale_6549 = ((safepow((sub_6552 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample mul_5630 = (scale_6549 * ((t_sample)1.5707963267949));
			t_sample cos_5629 = cos(mul_5630);
			__m_latch_48 = ((mul_5636 != 0) ? max_5825 : __m_latch_48);
			t_sample latch_5637 = __m_latch_48;
			t_sample fract_5653 = fract(latch_5637);
			int int_5651 = int(latch_5637);
			t_sample mul_5650 = (scale_6549 * int_5651);
			int eq_5645 = (mul_5650 == ((int)0));
			t_sample sin_5648 = sin(mul_5650);
			t_sample div_5647 = safediv(sin_5648, mul_5650);
			t_sample switch_5646 = (eq_5645 ? ((int)1) : div_5647);
			int add_5652 = (int_5651 + ((int)1));
			t_sample mul_5649 = (scale_6549 * add_5652);
			int eq_5641 = (mul_5649 == ((int)0));
			t_sample sin_5644 = sin(mul_5649);
			t_sample div_5643 = safediv(sin_5644, mul_5649);
			t_sample switch_5642 = (eq_5641 ? ((int)1) : div_5643);
			t_sample mix_6553 = (switch_5646 + (fract_5653 * (switch_5642 - switch_5646)));
			t_sample mul_5634 = (cos_5629 * mix_6553);
			t_sample history_5627_next_5654 = fixdenorm(switch_5628);
			t_sample history_5635_next_5655 = fixdenorm(div_5639);
			t_sample mul_5812 = ((((mul_5634 + mul_5601) + mul_5568) + mul_5535) * (-1));
			t_sample dcblock_5836 = __m_dcblock_49(mul_5812);
			t_sample mul_5834 = (dcblock_5836 * gen_5833);
			t_sample out2 = mul_5834;
			t_sample add_5758 = (m_history_8 + ((int)1));
			int gt_5763 = (m_history_7 > ((int)1));
			int mul_5768 = (gate_5815 * gt_5763);
			t_sample noise_5757 = noise();
			t_sample abs_5756 = fabs(noise_5757);
			t_sample switch_5760 = (mul_5768 ? abs_5756 : add_5758);
			__m_latch_50 = ((mul_5768 != 0) ? mul_5823 : __m_latch_50);
			t_sample latch_5765 = __m_latch_50;
			t_sample div_5771 = safediv(switch_5760, latch_5765);
			t_sample min_5764 = ((((int)1) < div_5771) ? ((int)1) : div_5771);
			t_sample sub_6557 = (min_5764 - ((int)0));
			t_sample scale_6554 = ((safepow((sub_6557 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample mul_5762 = (scale_6554 * ((t_sample)1.5707963267949));
			t_sample cos_5761 = cos(mul_5762);
			__m_latch_51 = ((mul_5768 != 0) ? max_5825 : __m_latch_51);
			t_sample latch_5769 = __m_latch_51;
			t_sample fract_5785 = fract(latch_5769);
			int int_5783 = int(latch_5769);
			t_sample mul_5782 = (scale_6554 * int_5783);
			int eq_5777 = (mul_5782 == ((int)0));
			t_sample sin_5780 = sin(mul_5782);
			t_sample div_5779 = safediv(sin_5780, mul_5782);
			t_sample switch_5778 = (eq_5777 ? ((int)1) : div_5779);
			int add_5784 = (int_5783 + ((int)1));
			t_sample mul_5781 = (scale_6554 * add_5784);
			int eq_5773 = (mul_5781 == ((int)0));
			t_sample sin_5776 = sin(mul_5781);
			t_sample div_5775 = safediv(sin_5776, mul_5781);
			t_sample switch_5774 = (eq_5773 ? ((int)1) : div_5775);
			t_sample mix_6558 = (switch_5778 + (fract_5785 * (switch_5774 - switch_5778)));
			t_sample mul_5766 = (cos_5761 * mix_6558);
			t_sample history_5759_next_5786 = fixdenorm(switch_5760);
			t_sample history_5767_next_5787 = fixdenorm(div_5771);
			t_sample add_5725 = (m_history_6 + ((int)1));
			int gt_5730 = (m_history_5 > ((int)1));
			int mul_5735 = (gate_5816 * gt_5730);
			__m_latch_52 = ((mul_5735 != 0) ? mul_5823 : __m_latch_52);
			t_sample latch_5732 = __m_latch_52;
			t_sample noise_5724 = noise();
			t_sample abs_5723 = fabs(noise_5724);
			t_sample switch_5727 = (mul_5735 ? abs_5723 : add_5725);
			t_sample div_5738 = safediv(switch_5727, latch_5732);
			t_sample min_5731 = ((((int)1) < div_5738) ? ((int)1) : div_5738);
			t_sample sub_6562 = (min_5731 - ((int)0));
			t_sample scale_6559 = ((safepow((sub_6562 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample mul_5729 = (scale_6559 * ((t_sample)1.5707963267949));
			t_sample cos_5728 = cos(mul_5729);
			__m_latch_53 = ((mul_5735 != 0) ? max_5825 : __m_latch_53);
			t_sample latch_5736 = __m_latch_53;
			t_sample fract_5752 = fract(latch_5736);
			int int_5750 = int(latch_5736);
			t_sample mul_5749 = (scale_6559 * int_5750);
			int eq_5744 = (mul_5749 == ((int)0));
			t_sample sin_5747 = sin(mul_5749);
			t_sample div_5746 = safediv(sin_5747, mul_5749);
			t_sample switch_5745 = (eq_5744 ? ((int)1) : div_5746);
			int add_5751 = (int_5750 + ((int)1));
			t_sample mul_5748 = (scale_6559 * add_5751);
			int eq_5740 = (mul_5748 == ((int)0));
			t_sample sin_5743 = sin(mul_5748);
			t_sample div_5742 = safediv(sin_5743, mul_5748);
			t_sample switch_5741 = (eq_5740 ? ((int)1) : div_5742);
			t_sample mix_6563 = (switch_5745 + (fract_5752 * (switch_5741 - switch_5745)));
			t_sample mul_5733 = (cos_5728 * mix_6563);
			t_sample history_5726_next_5753 = fixdenorm(switch_5727);
			t_sample history_5734_next_5754 = fixdenorm(div_5738);
			t_sample add_5659 = (m_history_4 + ((int)1));
			int gt_5664 = (m_history_3 > ((int)1));
			int mul_5669 = (gate_5818 * gt_5664);
			t_sample noise_5658 = noise();
			t_sample abs_5657 = fabs(noise_5658);
			t_sample switch_5661 = (mul_5669 ? abs_5657 : add_5659);
			__m_latch_54 = ((mul_5669 != 0) ? mul_5823 : __m_latch_54);
			t_sample latch_5666 = __m_latch_54;
			t_sample div_5672 = safediv(switch_5661, latch_5666);
			t_sample min_5665 = ((((int)1) < div_5672) ? ((int)1) : div_5672);
			t_sample sub_6567 = (min_5665 - ((int)0));
			t_sample scale_6564 = ((safepow((sub_6567 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample mul_5663 = (scale_6564 * ((t_sample)1.5707963267949));
			t_sample cos_5662 = cos(mul_5663);
			__m_latch_55 = ((mul_5669 != 0) ? max_5825 : __m_latch_55);
			t_sample latch_5670 = __m_latch_55;
			t_sample fract_5686 = fract(latch_5670);
			int int_5684 = int(latch_5670);
			t_sample mul_5683 = (scale_6564 * int_5684);
			int eq_5678 = (mul_5683 == ((int)0));
			t_sample sin_5681 = sin(mul_5683);
			t_sample div_5680 = safediv(sin_5681, mul_5683);
			t_sample switch_5679 = (eq_5678 ? ((int)1) : div_5680);
			int add_5685 = (int_5684 + ((int)1));
			t_sample mul_5682 = (scale_6564 * add_5685);
			int eq_5674 = (mul_5682 == ((int)0));
			t_sample sin_5677 = sin(mul_5682);
			t_sample div_5676 = safediv(sin_5677, mul_5682);
			t_sample switch_5675 = (eq_5674 ? ((int)1) : div_5676);
			t_sample mix_6568 = (switch_5679 + (fract_5686 * (switch_5675 - switch_5679)));
			t_sample mul_5667 = (cos_5662 * mix_6568);
			t_sample history_5660_next_5687 = fixdenorm(switch_5661);
			t_sample history_5668_next_5688 = fixdenorm(div_5672);
			t_sample add_5692 = (m_history_2 + ((int)1));
			int gt_5697 = (m_history_1 > ((int)1));
			int mul_5702 = (gate_5817 * gt_5697);
			t_sample noise_5691 = noise();
			t_sample abs_5690 = fabs(noise_5691);
			t_sample switch_5694 = (mul_5702 ? abs_5690 : add_5692);
			__m_latch_56 = ((mul_5702 != 0) ? mul_5823 : __m_latch_56);
			t_sample latch_5699 = __m_latch_56;
			t_sample div_5705 = safediv(switch_5694, latch_5699);
			t_sample min_5698 = ((((int)1) < div_5705) ? ((int)1) : div_5705);
			t_sample sub_6572 = (min_5698 - ((int)0));
			t_sample scale_6569 = ((safepow((sub_6572 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample mul_5696 = (scale_6569 * ((t_sample)1.5707963267949));
			t_sample cos_5695 = cos(mul_5696);
			__m_latch_57 = ((mul_5702 != 0) ? max_5825 : __m_latch_57);
			t_sample latch_5703 = __m_latch_57;
			t_sample fract_5719 = fract(latch_5703);
			int int_5717 = int(latch_5703);
			t_sample mul_5716 = (scale_6569 * int_5717);
			int eq_5711 = (mul_5716 == ((int)0));
			t_sample sin_5714 = sin(mul_5716);
			t_sample div_5713 = safediv(sin_5714, mul_5716);
			t_sample switch_5712 = (eq_5711 ? ((int)1) : div_5713);
			int add_5718 = (int_5717 + ((int)1));
			t_sample mul_5715 = (scale_6569 * add_5718);
			int eq_5707 = (mul_5715 == ((int)0));
			t_sample sin_5710 = sin(mul_5715);
			t_sample div_5709 = safediv(sin_5710, mul_5715);
			t_sample switch_5708 = (eq_5707 ? ((int)1) : div_5709);
			t_sample mix_6573 = (switch_5712 + (fract_5719 * (switch_5708 - switch_5712)));
			t_sample mul_5700 = (cos_5695 * mix_6573);
			t_sample history_5693_next_5720 = fixdenorm(switch_5694);
			t_sample history_5701_next_5721 = fixdenorm(div_5705);
			t_sample mul_5837 = ((((mul_5700 + mul_5667) + mul_5733) + mul_5766) * ((int)1));
			t_sample dcblock_5813 = __m_dcblock_58(mul_5837);
			t_sample mul_5835 = (dcblock_5813 * gen_5833);
			t_sample out1 = mul_5835;
			m_history_26 = history_5796_next_5798;
			m_history_24 = history_5792_next_5800;
			m_history_25 = history_5794_next_5799;
			m_history_20 = history_5827_next_5829;
			m_history_19 = history_5796_next_6477;
			m_history_17 = history_5792_next_6473;
			m_history_18 = history_5794_next_6476;
			m_history_16 = history_5528_next_5555;
			m_history_15 = history_5536_next_5556;
			m_history_14 = history_5561_next_5588;
			m_history_13 = history_5569_next_5589;
			m_history_12 = history_5594_next_5621;
			m_history_11 = history_5602_next_5622;
			m_history_10 = history_5627_next_5654;
			m_history_9 = history_5635_next_5655;
			m_history_8 = history_5759_next_5786;
			m_history_7 = history_5767_next_5787;
			m_history_6 = history_5726_next_5753;
			m_history_5 = history_5734_next_5754;
			m_history_4 = history_5660_next_5687;
			m_history_3 = history_5668_next_5688;
			m_history_2 = history_5693_next_5720;
			m_history_1 = history_5701_next_5721;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = 0;
			(*(__out4++)) = 0;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			
		};
		return __exception;
		
	};
	inline void set_cv5(t_param _value) {
		m_cv_21 = (_value < 0.001 ? 0.001 : (_value > 4 ? 4 : _value));
	};
	inline void set_cv6(t_param _value) {
		m_cv_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cv7(t_param _value) {
		m_cv_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 6;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 3; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4", "cv1", "cv2" };

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
		case 0: self->set_cv5(value); break;
		case 1: self->set_cv6(value); break;
		case 2: self->set_cv7(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_cv_21; break;
		case 1: *value = self->m_cv_22; break;
		case 2: *value = self->m_cv_23; break;
		
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
	// initialize parameter 0 ("m_cv_21")
	pi = self->__commonstate.params + 0;
	pi->name = "cv5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_cv_22")
	pi = self->__commonstate.params + 1;
	pi->name = "cv6";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_cv_23")
	pi = self->__commonstate.params + 2;
	pi->name = "cv7";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cv_23;
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


} // pulsar_2ddemo::
