<?xml version="1.0" encoding="UTF-8"?>
<turingmachine>
	<meta>
		<author />
		<title />
		<description />
		<created>10/05/2021 21:50:45</created>
		<modified>10/05/2021 21:54:55</modified>
	</meta>
	<machine type="TM">
		<tapes>
			<tape id="0">
				<head id="0" position="0" />
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
				<to>q2</to>
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
		</transitions>
		<code>f(q0, 1) = (q1, X, L)
f(q0, X) = (q0, X, R)
f(q0, $) = (q0, $, R)
f(q0, 0) = (q0, 0, R)
f(q1, X) = (q1, X, L)
f(q1, $) = (q1, $, L)

f(q1, 1) = (q1, 0, L)
f(q1, Blank) = (q0, 1, R)
f(q1, 0) = (q0, 1, R)
f(q0, Blank) = (q2, Blank, L)
f(q2, X) = (q3, 1, L)
f(q2, $) = (q2, $, L)
f(q2, Blank) = (qf, 0, R)
f(q3, X) = (q3, 1, L)
f(q3, $) = (qf, $, 0)</code>
	</machine>
</turingmachine>