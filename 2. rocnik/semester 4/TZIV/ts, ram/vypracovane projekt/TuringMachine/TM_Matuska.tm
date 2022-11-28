<?xml version="1.0" encoding="UTF-8"?>
<turingmachine>
	<meta>
		<author />
		<title />
		<description />
		<created>5/8/2022 5:53:28 PM</created>
		<modified>5/8/2022 5:53:29 PM</modified>
	</meta>
	<machine type="TM">
		<tapes>
			<tape id="0">
				<head id="0" position="-1" />
				<cell position="-1">$</cell>
				<cell position="0">1</cell>
				<cell position="1">1</cell>
				<cell position="2">1</cell>
				<cell position="3">1</cell>
				<cell position="4">1</cell>
				<cell position="5">1</cell>
				<cell position="6">1</cell>
				<cell position="7">1</cell>
				<cell position="8">1</cell>
				<cell position="9">1</cell>
				<cell position="10">1</cell>
				<cell position="11">1</cell>
				<cell position="12">1</cell>
				<cell position="13">1</cell>
				<cell position="14">1</cell>
				<cell position="15">1</cell>
				<cell position="16">1</cell>
				<cell position="17">1</cell>
				<cell position="18">1</cell>
				<cell position="19">1</cell>
				<cell position="20">1</cell>
			</tape>
		</tapes>
		<states>
			<state id="q1">
				<name>q1</name>
				<comment />
				<x>376</x>
				<y>137</y>
			</state>
			<state id="q0">
				<name>q0</name>
				<comment />
				<x>132</x>
				<y>145</y>
				<initial />
			</state>
			<state id="qf">
				<name>qf</name>
				<comment />
				<x>67</x>
				<y>233</y>
				<final />
			</state>
			<state id="q2">
				<name>q2</name>
				<comment />
				<x>40</x>
				<y>40</y>
			</state>
			<state id="q3">
				<name>q3</name>
				<comment />
				<x>40</x>
				<y>40</y>
			</state>
			<state id="q4">
				<name>q4</name>
				<comment />
				<x>40</x>
				<y>40</y>
			</state>
			<state id="q5">
				<name>q5</name>
				<comment />
				<x>190</x>
				<y>40</y>
			</state>
			<state id="inc1">
				<name>inc1</name>
				<comment />
				<x>340</x>
				<y>40</y>
			</state>
			<state id="inc2">
				<name>inc2</name>
				<comment />
				<x>490</x>
				<y>40</y>
			</state>
		</states>
		<transitions>
			<transition>
				<from>q0</from>
				<to>q1</to>
				<read>1</read>
				<write>X</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q0</from>
				<to>q0</to>
				<read>X</read>
				<write>X</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q0</from>
				<to>q0</to>
				<read>$</read>
				<write>$</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q0</from>
				<to>q0</to>
				<read>0</read>
				<write>0</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q1</from>
				<to>q1</to>
				<read>X</read>
				<write>X</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q1</from>
				<to>q1</to>
				<read>$</read>
				<write>$</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q1</from>
				<to>q1</to>
				<read>1</read>
				<write>0</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q1</from>
				<to>q0</to>
				<read>Blank</read>
				<write>1</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q1</from>
				<to>q0</to>
				<read>0</read>
				<write>1</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q0</from>
				<to>q4</to>
				<read>Blank</read>
				<write>Blank</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q2</from>
				<to>q3</to>
				<read>X</read>
				<write>1</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q2</from>
				<to>q2</to>
				<read>$</read>
				<write>$</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q2</from>
				<to>qf</to>
				<read>Blank</read>
				<write>0</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q3</from>
				<to>q3</to>
				<read>X</read>
				<write>1</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q3</from>
				<to>qf</to>
				<read>$</read>
				<write>$</write>
				<move>NoMove</move>
				<comment />
			</transition>
			<transition>
				<from>q4</from>
				<to>q4</to>
				<read>K</read>
				<write>K</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q4</from>
				<to>q5</to>
				<read>Blank</read>
				<write>#</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q4</from>
				<to>inc1</to>
				<read>#</read>
				<write>#</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q5</from>
				<to>q5</to>
				<read>J</read>
				<write>J</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q5</from>
				<to>q4</to>
				<read>X</read>
				<write>1</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q5</from>
				<to>q5</to>
				<read>#</read>
				<write>#</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q5</from>
				<to>qf</to>
				<read>Blank</read>
				<write>Blank</write>
				<move>NoMove</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>Blank</read>
				<write>1</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>0</read>
				<write>1</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>1</read>
				<write>2</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>2</read>
				<write>3</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>3</read>
				<write>4</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>4</read>
				<write>5</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>5</read>
				<write>6</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>6</read>
				<write>7</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>7</read>
				<write>8</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>q5</to>
				<read>8</read>
				<write>9</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc1</from>
				<to>inc2</to>
				<read>9</read>
				<write>0</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>Blank</read>
				<write>1</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>1</read>
				<write>2</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>2</read>
				<write>3</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>3</read>
				<write>4</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>4</read>
				<write>5</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>5</read>
				<write>6</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>6</read>
				<write>7</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>7</read>
				<write>8</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>inc2</from>
				<to>q5</to>
				<read>8</read>
				<write>9</write>
				<move>Right</move>
				<comment />
			</transition>
		</transitions>
		<code>K = {0, 1, $, X}
J = {0, 1, $}

f(q0, 1) = (q1, X, L)
f(q0, X) = (q0, X, R)
f(q0, $) = (q0, $, R)
f(q0, 0) = (q0, 0, R)
f(q1, X) = (q1, X, L)
f(q1, $) = (q1, $, L)

f(q1, 1) = (q1, 0, L)
f(q1, Blank) = (q0, 1, R)
f(q1, 0) = (q0, 1, R)
f(q0, Blank) = (q4, Blank, L)

f(q2, X) = (q3, 1, L)
f(q2, $) = (q2, $, L)
f(q2, Blank) = (qf, 0, R)
f(q3, X) = (q3, 1, L)
f(q3, $) = (qf, $, 0)

f(q4, K) = (q4, K, L)
f(q4, Blank) = (q5, #, R)
f(q4, #) = (inc1, #, L)

f(q5, J) = (q5, J, R)
f(q5, X) = (q4, 1, L)
f(q5, #) = (q5, #, R)
f(q5, Blank) = (qf, Blank, 0)

f(inc1, Blank) = (q5, 1, R)
f(inc1, 0) = (q5, 1, R)
f(inc1, 1) = (q5, 2, R)
f(inc1, 2) = (q5, 3, R)
f(inc1, 3) = (q5, 4, R)
f(inc1, 4) = (q5, 5, R)
f(inc1, 5) = (q5, 6, R)
f(inc1, 6) = (q5, 7, R)
f(inc1, 7) = (q5, 8, R)
f(inc1, 8) = (q5, 9, R)
f(inc1, 9) = (inc2, 0, L)

f(inc2, Blank) = (q5, 1, R)
f(inc2, 1) = (q5, 2, R)
f(inc2, 2) = (q5, 3, R)
f(inc2, 3) = (q5, 4, R)
f(inc2, 4) = (q5, 5, R)
f(inc2, 5) = (q5, 6, R)
f(inc2, 6) = (q5, 7, R)
f(inc2, 7) = (q5, 8, R)
f(inc2, 8) = (q5, 9, R)</code>
	</machine>
</turingmachine>